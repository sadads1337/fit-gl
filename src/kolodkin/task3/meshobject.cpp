#include "meshobject.hpp"

MeshObject::MeshObject(std::shared_ptr<Mesh> mesh,
                       QMatrix4x4 const &model_matrix)
    : pMesh_(std::move(mesh)), modelMatrix_(model_matrix) {}

RenderObjectSPtr MeshObject::clone() const {
  return std::static_pointer_cast<RenderObject>(
      std::make_shared<MeshObject>(*this));
}

void MeshObject::initialize(ShaderProgSPtr pShaderProgram) {
  Q_ASSERT(pShaderProgram);
  pShaderProgram_ = std::move(pShaderProgram);

  if (VAO_->isCreated())
    return;

  QOpenGLVertexArrayObject::Binder binder(VAO_.get());

  VBO_.create();
  VBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  VBO_.bind();
  VBO_.allocate(pMesh_->vertices.data(),
                pMesh_->vertices.size() * sizeof(Mesh::vertexType));

  pShaderProgram_->bind();
  pShaderProgram_->enableAttributeArray(positionLocation);
  // Vertex position
  pShaderProgram_->setAttributeBuffer(
      positionLocation, GL_FLOAT, offsetof(Mesh::vertexType, position),
      Mesh::vertexType::positionTupleSize, sizeof(Mesh::vertexType));
  // Vertex normal
  pShaderProgram_->enableAttributeArray(normalLocation);
  pShaderProgram_->setAttributeBuffer(
      normalLocation, GL_FLOAT, offsetof(Mesh::vertexType, normal),
      Mesh::vertexType::normalTupleSize, sizeof(Mesh::vertexType));

  IBO_.create();
  IBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  IBO_.bind();
  IBO_.allocate(pMesh_->indices.data(),
                pMesh_->indices.size() * sizeof(Mesh::indexType));
}

void MeshObject::render(QOpenGLFunctions &functions) {
  Q_ASSERT(pShaderProgram_);

  if (modelChanged_) {
    normModelMatrix_ = modelMatrix_.inverted().transposed();
    modelChanged_ = false;
  }
  pShaderProgram_->bind();
  pShaderProgram_->setUniformValue("model", modelMatrix_);
  pShaderProgram_->setUniformValue("normModel", normModelMatrix_);

  QOpenGLVertexArrayObject::Binder binder(VAO_.get());
  functions.glDrawElements(GL_TRIANGLES, pMesh_->indices.size(),
                           Mesh::IndexTypeVal, nullptr);
}

QMatrix4x4 &MeshObject::getModel() {
  modelChanged_ = true;
  return modelMatrix_;
}

QMatrix4x4 const &MeshObject::getModel() const { return modelMatrix_; }

void MeshObject::offsetMove(const QVector3D &offset) {
  getModel().translate(offset);
}

void MeshObject::moveTo(const QVector3D &position) {
  getModel().setColumn(3, {position, 1.f});
}
