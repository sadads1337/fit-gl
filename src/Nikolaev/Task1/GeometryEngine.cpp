//
// Created by andre on 21.02.2021.
//

#include "GeometryEngine.h"

#include <QVector2D>
#include <QVector3D>
#include <array>

GeometryEngine::GeometryEngine()
        : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry()
{
    // { coordinates(x, y, z) } ,{ normal vector (x, y, z) }, { color (r, g, b) }
    std::array<GLfloat, 216u> vertices = {
            // Vertex data for face 0
            -1.0f, -1.0f, 1.0f, 0, 0, 1, 0.0f, 0.0f, 0.0f,   // v0
            1.0f, -1.0f, 1.0f, 0, 0, 1, 0.0f, 0.0f, 0.0f,    // v1
            -1.0f, 1.0f, 1.0f, 0, 0, 1, 0.0f, 0.0f, 0.0f,    // v2
            1.0f, 1.0f, 1.0f, 0, 0, 1, 0.0f, 0.0f, 0.0f,     // v3

            // Vertex data for face 1
            1.0f, -1.0f, 1.0f, 1, 0, 0, 0.0f, 0.0f, 0.0f,    // v4
            1.0f, -1.0f, -1.0f, 1, 0, 0, 0.0f, 0.0f, 0.0f,   // v5
            1.0f, 1.0f, 1.0f, 1, 0, 0, 0.0f, 0.0f,  0.0f,    // v6
            1.0f, 1.0f, -1.0f, 1, 0, 0, 0.0f, 0.0f, 0.0f,    // v7

            // Vertex data for face 2
            1.0f, -1.0f, -1.0f, 0, 0, -1, 0.0f, 0.0f, 0.0f,  // v8
            -1.0f, -1.0f, -1.0f, 0, 0, -1, 0.0f, 0.0f, 0.0f, // v9
            1.0f, 1.0f, -1.0f, 0, 0, -1, 0.0f, 0.0f, 0.0f,  // v10
            -1.0f, 1.0f, -1.0f, 0, 0, -1, 0.0f, 0.0f, 0.0f, // v11

            // Vertex data for face 3
            -1.0f, -1.0f, -1.0f, -1, 0, 0, 0.0f, 0.0f, 0.0f, // v12
            -1.0f, -1.0f, 1.0f, -1, 0, 0, 0.0f, 0.0f,  0.0f, // v13
            -1.0f, 1.0f, -1.0f, -1, 0, 0, 0.0f, 0.0f, 0.0f,  // v14
            -1.0f, 1.0f, 1.0f, -1, 0, 0, 0.0f, 0.0f,  0.0f,  // v15

            // Vertex data for face 4
            -1.0f, -1.0f, -1.0f, 0, -1, 0, 0.0f, 0.0f, 0.0f, // v16
            1.0f, -1.0f, -1.0f, 0, -1, 0, 0.0f, 0.0f, 0.0f,  // v17
            -1.0f, -1.0f, 1.0f, 0, -1, 0, 0.0f, 0.0f, 0.0f,  // v18
            1.0f, -1.0f, 1.0f, 0, -1, 0, 0.0f, 0.0f, 0.0f,   // v19

            // Vertex data for face 5
            -1.0f, 1.0f, 1.0f, 0, 1, 0, 0.0f, 0.0f, 0.0f,    // v20
            1.0f, 1.0f, 1.0f, 0, 1, 0, 0.0f, 0.0f, 0.0f,     // v21
            -1.0f, 1.0f, -1.0f, 0, 1, 0, 0.0f, 0.0f, 0.0f,   // v22
            1.0f, 1.0f, -1.0f, 0, 1, 0, 0.0f, 0.0f,  0.0f    // v23
    };

    GLushort indices[] = {
            0,  1,  2,  3,  3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
            4,  4,  5,  6,  7,  7,  // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
            8,  8,  9, 10, 11, 11,  // Face 2 - triangle strip ( v8,  v9, v10, v11)
            12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
            16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
            20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), static_cast<std::int32_t>(vertices.size() * sizeof(GLfloat)));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
}

void GeometryEngine::setColor(QVector3D RGBcolors)
{
    std::array<GLfloat, 216u> vertices = {
            // Vertex data for face 0
            -1.0f, -1.0f, 1.0f, 0, 0, 1, RGBcolors[0], RGBcolors[1], RGBcolors[2],   // v0
            1.0f, -1.0f, 1.0f, 0, 0, 1, RGBcolors[1], RGBcolors[1], RGBcolors[0],    // v1
            -1.0f, 1.0f, 1.0f, 0, 0, 1, RGBcolors[2], RGBcolors[1], RGBcolors[2],    // v2
            1.0f, 1.0f, 1.0f, 0, 0, 1, RGBcolors[0], RGBcolors[2], RGBcolors[2],     // v3

            // Vertex data for face 1
            1.0f, -1.0f, 1.0f, 1, 0, 0, RGBcolors[0], RGBcolors[1], RGBcolors[2],    // v4
            1.0f, -1.0f, -1.0f, 1, 0, 0, RGBcolors[1], RGBcolors[1], RGBcolors[2],   // v5
            1.0f, 1.0f, 1.0f, 1, 0, 0, RGBcolors[0], RGBcolors[1],  RGBcolors[2],    // v6
            1.0f, 1.0f, -1.0f, 1, 0, 0, RGBcolors[2], RGBcolors[1], RGBcolors[2],    // v7

            // Vertex data for face 2
            1.0f, -1.0f, -1.0f, 0, 0, -1, RGBcolors[0], RGBcolors[1], RGBcolors[2],  // v8
            -1.0f, -1.0f, -1.0f, 0, 0, -1, RGBcolors[0], RGBcolors[1], RGBcolors[0], // v9
            1.0f, 1.0f, -1.0f, 0, 0, -1, RGBcolors[0], RGBcolors[2], RGBcolors[2],  // v10
            -1.0f, 1.0f, -1.0f, 0, 0, -1, RGBcolors[0], RGBcolors[2], RGBcolors[2], // v11

            // Vertex data for face 3
            -1.0f, -1.0f, -1.0f, -1, 0, 0, RGBcolors[2], RGBcolors[1], RGBcolors[2], // v12
            -1.0f, -1.0f, 1.0f, -1, 0, 0, RGBcolors[0], RGBcolors[2],  RGBcolors[2], // v13
            -1.0f, 1.0f, -1.0f, -1, 0, 0, RGBcolors[0], RGBcolors[1], RGBcolors[1],  // v14
            -1.0f, 1.0f, 1.0f, -1, 0, 0, RGBcolors[0], RGBcolors[1],  RGBcolors[1],  // v15

            // Vertex data for face 4
            -1.0f, -1.0f, -1.0f, 0, -1, 0, RGBcolors[0], RGBcolors[1], RGBcolors[2], // v16
            1.0f, -1.0f, -1.0f, 0, -1, 0, RGBcolors[0], RGBcolors[1], RGBcolors[2],  // v17
            -1.0f, -1.0f, 1.0f, 0, -1, 0, RGBcolors[1], RGBcolors[1], RGBcolors[2],  // v18
            1.0f, -1.0f, 1.0f, 0, -1, 0, RGBcolors[0], RGBcolors[1], RGBcolors[2],   // v19

            // Vertex data for face 5
            -1.0f, 1.0f, 1.0f, 0, 1, 0, RGBcolors[0], RGBcolors[1], RGBcolors[0],    // v20
            1.0f, 1.0f, 1.0f, 0, 1, 0, RGBcolors[0], RGBcolors[1], RGBcolors[1],     // v21
            -1.0f, 1.0f, -1.0f, 0, 1, 0, RGBcolors[2], RGBcolors[1], RGBcolors[2],   // v22
            1.0f, 1.0f, -1.0f, 0, 1, 0, RGBcolors[0], RGBcolors[1],  RGBcolors[2]    // v23
    };

    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), static_cast<std::int32_t>(vertices.size() * sizeof(GLfloat)));
}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    const std::int32_t stride = sizeof(GLfloat) * 9;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, stride);

    int vertexColor = program->attributeLocation("vertex_color");
    program->enableAttributeArray(vertexColor);
    program->setAttributeBuffer(vertexColor, GL_FLOAT, sizeof(GLfloat)*6, 3, stride);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);
}
