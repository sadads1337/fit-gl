#include "GeometryEngine.h"

GeometryEngine::GeometryEngine()
    : arrayBuf(QOpenGLBuffer::VertexBuffer),
      indexBuf(QOpenGLBuffer::IndexBuffer) {

  arrayBuf.create();
  indexBuf.create();

  initCubeGeometry(1.0f, 1);
}

void GeometryEngine::initCubeGeometry(float width, unsigned int factor) {
  if (arrayBuf.isCreated())
    arrayBuf.destroy();

  if (indexBuf.isCreated())
    indexBuf.destroy();

  arrayBuf.create();
  indexBuf.create();

  auto half_width = width / 2.0f;
  QVector<VertexData> vertexes;
  QVector<GLuint> indexes;

  for (auto face = 0U; face < 6U; ++face) {
    // Add vertices
    const auto constCoord = face % 3;
    const auto coord1 = (face + 1) % 3;
    const auto coord2 = (face + 2) % 3;

    for (auto y = 0U; y < factor + 1; ++y) {
      for (auto x = 0U; x < factor + 1; ++x) {
        QVector3D position{0, 0, 0};
        QVector3D normal{0, 0, 0};
        QVector2D texture{0, 0};
        QVector3D tangent;
        QVector3D bitangent;

        normal[constCoord] = (static_cast<int>(face) / 3 * 2) - 1;

        position[constCoord] = normal[constCoord] * half_width;
        position[coord1] = (x * 2.0F / factor - 1.0F) * half_width;
        position[coord2] =
            (y * 2.0F / factor - 1.0F) * half_width * normal[constCoord];

        /* side Faces */
        if (face == 0) {
          texture[0] = 0.77f + static_cast<float>(x) / factor * 0.23f;
          texture[1] = 0.35f + static_cast<float>(y) / factor * 0.31f;
          tangent = QVector3D(0, 0, -1);
          bitangent = QVector3D(0, 1, 0);
        } else if (face == 2) {
          texture[0] = static_cast<float>(x) / factor * 0.23f;
          texture[1] = 0.35f + static_cast<float>(y) / factor * 0.31f;
          tangent = QVector3D(-1, 0, 0);
          bitangent = QVector3D(0, 1, 0);
        } else if (face == 3) {
          texture[0] = 0.77f + static_cast<float>(x) / factor * 0.23f;
          texture[1] = 0.35f + static_cast<float>(y) / factor * 0.31f;
          tangent = QVector3D(0, 0, 1);
          bitangent = QVector3D(0, 1, 0);
        } else if (face == 5) {
          texture[0] = 0.27f + static_cast<float>(x) / factor * 0.21f;
          texture[1] = 0.35f + static_cast<float>(y) / factor * 0.31f;
          tangent = QVector3D(1, 0, 0);
          bitangent = QVector3D(0, 1, 0);
        }
        /* Bottom Face */
        else if (face == 1) {
          texture[0] = 0.27f + static_cast<float>(x) / factor * 0.23f;
          texture[1] = static_cast<float>(y) / factor * 0.31f;
          tangent = QVector3D(1, 0, 0);
          bitangent = QVector3D(0, 0, -1);
        }
        /* Top Face */
        else if (face == 4) {
          texture[0] = 0.27f + static_cast<float>(x) / factor * 0.23f;
          texture[1] = 0.68f + static_cast<float>(y) / factor * 0.31f;
          tangent = QVector3D(1, 0, 0);
          bitangent = QVector3D(0, 0, 1);
        }
        vertexes.append({
            QVector3D(position.x(), position.y(), position.z()),
            QVector3D(normal.x(), normal.y(), normal.z()),
            QVector2D(texture.x(), texture.y()),
            QVector3D(tangent.x(), tangent.y(), tangent.z()),
            QVector3D(bitangent.x(), bitangent.y(), bitangent.z()),
        });
      }
    }

    // Add indices
    const auto faceIndexOffset = face * (factor + 1) * (factor + 1);
    for (auto y = 0U; y < factor; ++y) {
      const auto rowIndexOffset = (factor + 1) * y;

      indexes.append(faceIndexOffset + rowIndexOffset);
      for (auto x = 0U; x < factor + 1; ++x) {
        indexes.append(faceIndexOffset + rowIndexOffset + x);
        indexes.append(faceIndexOffset + rowIndexOffset + x + (factor + 1));
      }
      indexes.append(faceIndexOffset + rowIndexOffset + factor + (factor + 1));
    }
  }

  arrayBuf.bind();
  arrayBuf.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));

  indexBuf.bind();
  indexBuf.allocate(indexes.constData(),
                    indexes.size() *
                        sizeof(GLuint)); // Transfer vertex data to VBO 0
}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program,
                                      QOpenGLFunctions *functions) {

  QMatrix4x4 modelMatrix;
  modelMatrix.translate(m_translate);
  modelMatrix.rotate(m_rotate);

  program->setUniformValue("model_matrix", modelMatrix);

  // Draw cube faces
  arrayBuf.bind();
  indexBuf.bind();

  program->setUniformValue("offset_from_face", 0.0f);
  program->setUniformValue("frag_color_factor", 1.0f);

  std::ptrdiff_t offset = 0;

  auto vertexLocation = program->attributeLocation("vertex_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  offset += sizeof(QVector3D);

  auto vertexNormal = program->attributeLocation("vertex_normal");
  program->enableAttributeArray(vertexNormal);
  program->setAttributeBuffer(vertexNormal, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  offset += sizeof(QVector3D);

  auto vertexTexture = program->attributeLocation("vertex_texture");
  program->enableAttributeArray(vertexTexture);
  program->setAttributeBuffer(vertexTexture, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  offset += sizeof(QVector3D);

  auto tg = program->attributeLocation("tangent");
  program->enableAttributeArray(tg);
  program->setAttributeBuffer(tg, GL_FLOAT, offset, 3, sizeof(VertexData));

  offset += sizeof(QVector3D);

  auto btg = program->attributeLocation("bitangent");
  program->enableAttributeArray(btg);
  program->setAttributeBuffer(btg, GL_FLOAT, offset, 3, sizeof(VertexData));

  functions->glDrawElements(GL_QUAD_STRIP, indexBuf.size(), GL_UNSIGNED_INT,
                            nullptr);
}

void GeometryEngine::rotate(const QQuaternion &r) { m_rotate = r * m_rotate; }

void GeometryEngine::translate(const QVector3D &t) { m_translate += t; }