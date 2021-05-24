#pragma once

#include "mesh.hpp"
#include "renderobject.hpp"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QTransform>

#include <memory>

class MeshObject : public RenderObject {
  using VaoSPtr = std::shared_ptr<QOpenGLVertexArrayObject>;

  std::shared_ptr<Mesh> pMesh_;
  VaoSPtr VAO_ = std::make_shared<QOpenGLVertexArrayObject>();
  QOpenGLBuffer VBO_{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer IBO_{QOpenGLBuffer::IndexBuffer};

  QMatrix4x4 modelMatrix_;
  QMatrix4x4 normModelMatrix_;
  bool modelChanged_ = true;
  inline static constexpr int positionLocation = 0;
  inline static constexpr int normalLocation = 1;

protected:
  std::shared_ptr<QOpenGLShaderProgram> pShaderProgram_;

public:
  using ShaderProgSPtr = std::shared_ptr<QOpenGLShaderProgram>;
  using MeshSPtr = std::shared_ptr<Mesh>;

  MeshObject(MeshSPtr mesh, QMatrix4x4 const &model_matrix);
  MeshObject(MeshObject const &other) = default;
  ~MeshObject() override = default;

  RenderObjectSPtr clone() const override;

  void initialize(ShaderProgSPtr pShaderProgram) override;
  void render(QOpenGLFunctions &functions) override;

  QMatrix4x4 &getModel();
  QMatrix4x4 const &getModel() const;

  void offsetMove(QVector3D const &offset) override;
  void moveTo(QVector3D const &position) override;
};
