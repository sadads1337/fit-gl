#include "GeometryEngine.h"

#include <QtGui/QColor>

GeometryEngine::GeometryEngine()
    : arrayBuf(QOpenGLBuffer::VertexBuffer),
      indexBuf(QOpenGLBuffer::IndexBuffer) {
  initializeOpenGLFunctions();

  arrayBuf.create();
  indexBuf.create();

  initCubeGeometry(1.0f, 1);
}

GeometryEngine::~GeometryEngine() {
  arrayBuf.destroy();
  indexBuf.destroy();
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

  for (auto face = 0U; face < 6; ++face) {
    // Add vertices
    const auto constCoord = face % 3;
    const auto coord1 = (face + 1) % 3;
    const auto coord2 = (face + 2) % 3;

    for (auto y = 0U; y < factor + 1; ++y) {
      for (auto x = 0U; x < factor + 1; ++x) {
        auto position = QVector3D{0, 0, 0};
        auto normal = QVector3D{0, 0, 0};

        normal[constCoord] = int(face / 3 * 2) - 1;

        position[constCoord] = normal[constCoord] * half_width;
        position[coord1] = (x * 2.0F / factor - 1.0F) * half_width;
        position[coord2] =
            (y * 2.0F / factor - 1.0F) * half_width * normal[constCoord];

        auto color = QColor{};
        color.setRedF((x + y + face) % 4 / 3.0F);
        color.setGreenF((x + y + face + 3) % 4 / 3.0F);
        color.setBlueF((x + y + face + 6) % 4 / 3.0F);

        vertexes.append(
            VertexData(QVector3D(position.x(), position.y(), position.z()),
                       QVector3D(normal.x(), normal.y(), normal.z()),
                       QVector3D(color.redF(), color.greenF(), color.blueF())));
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

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program) {
  // Draw cube faces
  arrayBuf.bind();
  indexBuf.bind();

  program->setUniformValue("offset_from_face", 0.0f);
  program->setUniformValue("frag_color_factor", 1.0f);

  quintptr offset = 0;

  int vertexLocation = program->attributeLocation("vertex_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  offset += sizeof(QVector3D);

  int vertexNormal = program->attributeLocation("vertex_normal");
  program->enableAttributeArray(vertexNormal);
  program->setAttributeBuffer(vertexNormal, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  offset += sizeof(QVector3D);

  int vertexColor = program->attributeLocation("vertex_color");
  program->enableAttributeArray(vertexColor);
  program->setAttributeBuffer(vertexColor, GL_FLOAT, offset, 3,
                              sizeof(VertexData));

  glDrawElements(GL_QUAD_STRIP, indexBuf.size(), GL_UNSIGNED_INT, nullptr);

  // Draw cube edges
  arrayBuf.bind();
  indexBuf.bind();

  program->setUniformValue("offset_from_face", 1.0e-3f);
  program->setUniformValue("frag_color_factor", 0.0f);

  glDrawElements(GL_LINE_STRIP, indexBuf.size(), GL_UNSIGNED_INT, nullptr);

  program->disableAttributeArray("vertex_position");
  program->disableAttributeArray("vertex_normal");
  program->disableAttributeArray("vertex_color");

  arrayBuf.release();
  indexBuf.release();
}