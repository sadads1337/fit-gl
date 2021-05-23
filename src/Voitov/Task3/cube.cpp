#include "cube.hpp"

void geometry::Cube::init(GLfloat width, QVector3D center)
{
    this->vBuf.create();
    this->indBuf.create();

    this->width = width / 2.0f;
    this->center = center;
    //initialize block
    {
        gVertexes.append(VertexData({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}));
        gVertexes.append(VertexData({0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}));
        gVertexes.append(VertexData({0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}));

        gVertexes.append(VertexData({-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}));
        gVertexes.append(VertexData({-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}));
        gVertexes.append(VertexData({-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}));

        gVertexes.append(VertexData({0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}));
        gVertexes.append(VertexData({0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}));
        gVertexes.append(VertexData({0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}));

        gVertexes.append(VertexData({-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}));
        gVertexes.append(VertexData({-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}));
        gVertexes.append(VertexData({-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}));

        gVertexes.append(VertexData({0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}));
        gVertexes.append(VertexData({0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}));
        gVertexes.append(VertexData({0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}));

        gVertexes.append(VertexData({-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}));
        gVertexes.append(VertexData({-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}));
        gVertexes.append(VertexData({-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}));

        gVertexes.append(VertexData({-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}));
        gVertexes.append(VertexData({-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}));
        gVertexes.append(VertexData({-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}));

        gVertexes.append(VertexData({0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}));
        gVertexes.append(VertexData({0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}));
        gVertexes.append(VertexData({0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}));



        gIndexes.append(0);
        gIndexes.append(3);
        gIndexes.append(6);
        gIndexes.append(6);
        gIndexes.append(3);
        gIndexes.append(9);
        gIndexes.append(2);
        gIndexes.append(7);
        gIndexes.append(13);
        gIndexes.append(13);
        gIndexes.append(7);
        gIndexes.append(23);
        gIndexes.append(4);
        gIndexes.append(1);
        gIndexes.append(17);
        gIndexes.append(17);
        gIndexes.append(1);
        gIndexes.append(14);
        gIndexes.append(19);
        gIndexes.append(10);
        gIndexes.append(16);
        gIndexes.append(16);
        gIndexes.append(10);
        gIndexes.append(5);
        gIndexes.append(18);
        gIndexes.append(15);
        gIndexes.append(21);
        gIndexes.append(21);
        gIndexes.append(15);
        gIndexes.append(12);
        gIndexes.append(11);
        gIndexes.append(20);
        gIndexes.append(8);
        gIndexes.append(8);
        gIndexes.append(20);
        gIndexes.append(22);
    }

}

