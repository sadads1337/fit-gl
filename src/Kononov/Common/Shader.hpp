#pragma once

#include <memory>
#include <type_traits>

#include <QOpenGLShaderProgram>

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

  std::shared_ptr<Shader> createShared() { return create(); }
};

} // namespace Kononov
