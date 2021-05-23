#include "cube.hpp"


void geometry::Cube::init(GLfloat width, GLuint N)
{
    this->vBuf.create();
    this->indBuf.create();

    this->num_of_vertixes = N;
    this->width = width / 2.0f;

    //initialize block
   {
        for (auto side = 0U; side < 6; ++side) {
          const auto coord = side % 3;
          const auto coord1 = (side + 1) % 3;
          const auto coord2 = (side + 2) % 3;

          for (auto y = 0U; y < N + 1; ++y) {
            for (auto x = 0U; x < N + 1; ++x) {
              auto position = QVector3D{0, 0, 0};
              auto normal = QVector3D{0, 0, 0};

              normal[coord] = int(side / 3 * 2) - 1;

              position[coord] = normal[coord] * this->width ;
              position[coord1] = (x * 2.0f / N - 1.0f) * this->width;
              position[coord2] = (y * 2.0f / N - 1.0f) * this->width  * normal[coord];

              this->gVertexes.append(QVector3D{position.x(), position.y(), position.z()});
            }
          }
          const auto sideIndexOffset = side * (N + 1) * (N + 1);
          for (auto y = 0U; y < N; ++y) {
            const auto indexOffset = (N + 1) * y;
            this->gIndexes.append(sideIndexOffset + indexOffset);
            for (auto x = 0U; x < N + 1; ++x) {
              this->gIndexes.append(sideIndexOffset + indexOffset + x);
              this->gIndexes.append(sideIndexOffset + indexOffset + x + (N + 1));
            }
            this->gIndexes.append(sideIndexOffset + indexOffset + N + (N + 1));
          }
        }
    }
}

