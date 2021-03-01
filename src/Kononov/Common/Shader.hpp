#pragma once

#include <memory>
#include <type_traits>

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "Camera.hpp"
#include "Vertex.hpp"

namespace Kononov {

class Shader {
public:
  virtual void bind() = 0;
  virtual void release() = 0;
  virtual void prepare(const Camera &camera, QMatrix4x4 model_matrix) = 0;
  virtual void cleanup() = 0;
};

template <typename VertexInterface> class TypedShader : public Shader {
public:
  virtual void initVertexArray(const VertexInterface &mapper) = 0;
};

class BaseShader {
public:
  using VertexInterface = BaseVertexInterface;
  class Data {};
  class Parameters {};

  // NOLINTNEXTLINE(hicpp-named-parameter, readability-named-parameter)
  static void initDataImpl(const QOpenGLShaderProgram &, Data &) {}

  // NOLINTNEXTLINE(hicpp-named-parameter, readability-named-parameter)
  static void initVertexArrayImpl(QOpenGLShaderProgram &, const Data &,
                                  const VertexInterface &) {}

  // NOLINTNEXTLINE(hicpp-named-parameter, readability-named-parameter)
  static void prepareImpl(const Camera &, const QMatrix4x4 &,
                          QOpenGLShaderProgram &, const Data &,
                          const Parameters &) {}

  // NOLINTNEXTLINE(hicpp-named-parameter, readability-named-parameter)
  static void cleanupImpl(QOpenGLShaderProgram &, const Data &,
                          const Parameters &) {}
};

template <template <typename> typename Meta, typename Base = BaseShader>
class MakeShader {
public:
  using VertexInterface = typename Meta<Base>::VertexInterface;
  using Data = typename Meta<Base>::Data;
  using Parameters = typename Meta<Base>::Parameters;

private:
  // Check initVertexArray signature
  template <typename T, typename = void>
  struct HasInitVertexArray : std::false_type {};
  template <typename T>
  struct HasInitVertexArray<T, decltype((void)T::initVertexArray, void())>
      : std::true_type {};

  // Check cleanup signature
  template <typename T, typename = void> struct HasCleanup : std::false_type {};
  template <typename T>
  struct HasCleanup<T, decltype((void)T::cleanup, void())> : std::true_type {};

  // Check simple prepare method signature
  template <typename T, typename>
  struct CheckSimplePrepareSignature : std::false_type {};
  template <typename T>
  struct CheckSimplePrepareSignature<
      T, void (*)(QOpenGLShaderProgram &, const Data &, const Parameters &)>
      : std::true_type {};
  template <typename T>
  struct HasSimplePrepare
      : CheckSimplePrepareSignature<T, decltype(&T::prepare)> {};

  // Private fields
  std::shared_ptr<QOpenGLShaderProgram> m_program;
  std::shared_ptr<Data> m_data;

public:
  static void initDataImpl(const QOpenGLShaderProgram &program, Data &data) {
    Base::initDataImpl(program, data);
    Meta<Base>::initData(program, data);
  }

  static void initVertexArrayImpl(QOpenGLShaderProgram &program,
                                  const Data &data,
                                  const VertexInterface &mapper) {
    Base::initVertexArrayImpl(program, data, mapper);
    if constexpr (HasInitVertexArray<Meta<Base>>::value) {
      Meta<Base>::initVertexArray(program, data, mapper);
    }
  }

  static void prepareImpl(const Camera &camera, const QMatrix4x4 &model_matrix,
                          QOpenGLShaderProgram &program, const Data &data,
                          const Parameters &params) {
    Base::prepareImpl(camera, model_matrix, program, data, params);
    if constexpr (HasSimplePrepare<Meta<Base>>::value) {
      Meta<Base>::prepare(program, data, params);
    } else {
      Meta<Base>::prepare(camera, model_matrix, program, data, params);
    }
  }

  static void cleanupImpl(QOpenGLShaderProgram &program, const Data &data,
                          const Parameters &params) {
    // Cleanup in reverse order
    if constexpr (HasCleanup<Meta<Base>>::value) {
      Meta<Base>::cleanup(program, data, params);
    }
    Base::cleanupImpl(program, data, params);
  }

  explicit MakeShader(std::shared_ptr<QOpenGLShaderProgram> program)
      : m_program(std::move(program)), m_data(std::make_shared<Data>()) {
    initDataImpl(*m_program, *m_data);
  }

  class Shader : public TypedShader<VertexInterface> {
  private:
    std::shared_ptr<QOpenGLShaderProgram> m_program;
    std::shared_ptr<const Data> m_data;
    Parameters m_params;

  public:
    Shader(std::shared_ptr<QOpenGLShaderProgram> program,
           std::shared_ptr<const Data> data)
        : m_program(std::move(program)), m_data(std::move(data)), m_params() {}

    Parameters &getParameters() { return m_params; }
    void setParameters(const Parameters &params) { m_params = params; }

    void bind() override { m_program->bind(); };
    void release() override { m_program->release(); };

    void initVertexArray(const VertexInterface &mapper) override {
      initVertexArrayImpl(*m_program, *m_data, mapper);
    }

    void prepare(const Camera &camera, QMatrix4x4 model_matrix) override {
      prepareImpl(camera, model_matrix, *m_program, *m_data, m_params);
    }

    void cleanup() override { cleanupImpl(*m_program, *m_data, m_params); }
  };

  std::unique_ptr<Shader> create() {
    return std::make_unique<Shader>(m_program, m_data);
  }
};

template <typename Base> struct FirstShaderMeta {
  using VertexInterface = RegularVertex::Interface;

  struct Data : Base::Data {
    GLint vertex_position_attr;
    GLint vertex_normal_attr;
    GLint vertex_uv_attr;

    GLint model_view_matrix;
    GLint model_matrix;
    GLint normal_matrix;

    GLint diffuse_map;
    GLint ambient_strength;
    GLint specular_strength;
    GLint specular_pow;
    GLint light_color;
    GLint light_pos;
    GLint view_pos;
  };

  static void initData(const QOpenGLShaderProgram &p, Data &d) {
    d.vertex_position_attr = p.attributeLocation("vertex_position");
    d.vertex_normal_attr = p.attributeLocation("vertex_normal");
    d.vertex_uv_attr = p.attributeLocation("vertex_uv");

    d.model_view_matrix = p.uniformLocation("model_view_matrix");
    d.model_matrix = p.uniformLocation("model_matrix");
    d.normal_matrix = p.uniformLocation("normal_matrix");

    d.diffuse_map = p.uniformLocation("diffuse_map");
    d.ambient_strength = p.uniformLocation("ambient_strength");
    d.specular_strength = p.uniformLocation("specular_strength");
    d.specular_pow = p.uniformLocation("specular_pow");
    d.light_color = p.uniformLocation("light_color");
    d.light_pos = p.uniformLocation("light_pos");
    d.view_pos = p.uniformLocation("view_pos");
  }

  class Parameters : public Base::Parameters {
  private:
    std::shared_ptr<QOpenGLTexture> m_diffuse_texture;
    GLfloat m_ambient_strength;
    GLfloat m_specular_strength;
    GLfloat m_specular_pow;
    QVector3D m_light_color;
    QVector3D m_light_pos;

  public:
    void setSpecular(GLfloat strength, GLfloat pow) {
      m_specular_strength = strength;
      m_specular_pow = pow;
    }
    void setLightSource(QVector3D pos, QVector3D color) {
      m_light_pos = pos;
      m_light_color = color;
    }

    [[nodiscard]] std::shared_ptr<QOpenGLTexture> getDiffuseTexture() const {
      return m_diffuse_texture;
    }
    void setDiffuseTexture(std::shared_ptr<QOpenGLTexture> diffuse_texture) {
      m_diffuse_texture = std::move(diffuse_texture);
    }
    [[nodiscard]] GLfloat getAmbientStrength() const {
      return m_ambient_strength;
    }
    void setAmbientStrength(GLfloat ambient_strength) {
      m_ambient_strength = ambient_strength;
    }
    [[nodiscard]] GLfloat getSpecularStrength() const {
      return m_specular_strength;
    }
    void setSpecularStrength(GLfloat specular_strength) {
      m_specular_strength = specular_strength;
    }
    [[nodiscard]] GLfloat getSpecularPow() const { return m_specular_pow; }
    void setSpecularPow(GLfloat specular_pow) { m_specular_pow = specular_pow; }
    [[nodiscard]] const QVector3D &getLightColor() const {
      return m_light_color;
    }
    void setLightColor(const QVector3D &light_color) {
      m_light_color = light_color;
    }
    [[nodiscard]] const QVector3D &getLightPos() const { return m_light_pos; }
    void setLightPos(const QVector3D &light_pos) { m_light_pos = light_pos; }
  };

  static void initVertexArray(QOpenGLShaderProgram &program, const Data &data,
                              const VertexInterface &mapper) {
    auto stride = mapper.getStride();

    program.enableAttributeArray(data.vertex_position_attr);
    program.setAttributeBuffer(data.vertex_position_attr, GL_FLOAT,
                               mapper.getPositionOffset(), 3, stride);

    program.enableAttributeArray(data.vertex_normal_attr);
    program.setAttributeBuffer(data.vertex_normal_attr, GL_FLOAT,
                               mapper.getNormalOffset(), 3, stride);

    program.enableAttributeArray(data.vertex_uv_attr);
    program.setAttributeBuffer(data.vertex_uv_attr, GL_FLOAT,
                               mapper.getUVOffset(), 2, stride);
  }

  static void prepare(const Camera &camera, const QMatrix4x4 &model_matrix,
                      QOpenGLShaderProgram &program, const Data &data,
                      const Parameters &params) {
    // Set camera parameters
    program.setUniformValue(data.view_pos, camera.getAbsolutePosition());
    program.setUniformValue(data.model_view_matrix,
                            camera.getProjectionViewMatrix() * model_matrix);
    program.setUniformValue(data.model_matrix, model_matrix);
    program.setUniformValue(data.normal_matrix, model_matrix.normalMatrix());

    // Set other parameters
    params.getDiffuseTexture()->bind(0);
    program.setUniformValue(data.diffuse_map, 0);
    program.setUniformValue(data.ambient_strength, params.getAmbientStrength());
    program.setUniformValue(data.specular_strength,
                            params.getSpecularStrength());
    program.setUniformValue(data.specular_pow, params.getSpecularPow());
    program.setUniformValue(data.light_pos, params.getLightPos());
    program.setUniformValue(data.light_color, params.getLightColor());
  }

  // NOLINTNEXTLINE(hicpp-named-parameter, readability-named-parameter)
  static void cleanup(QOpenGLShaderProgram &, const Data &,
                      const Parameters &params) {
    params.getDiffuseTexture()->release();
  }
};

template <typename Base> struct SecondShaderMeta {
  using VertexInterface = RegularVertex::Interface;

  struct Data : Base::Data {
    GLint skewness;
  };

  static void initData(const QOpenGLShaderProgram &p, Data &d) {
    d.skewness = p.uniformLocation("skewness");
  }

  class Parameters : public Base::Parameters {
  private:
    GLfloat m_skewness;

  public:
    [[nodiscard]] GLfloat getSkewness() const { return m_skewness; };
    void setSkewness(GLfloat skewness) { m_skewness = skewness; };
  };

  static void prepare(QOpenGLShaderProgram &program, const Data &data,
                      const Parameters &params) {
    program.setUniformValue(data.skewness, params.getSkewness());
  }
};

using FirstShaderNew = MakeShader<FirstShaderMeta>;
using SecondShaderNew = MakeShader<SecondShaderMeta, FirstShaderNew>;

} // namespace Kononov
