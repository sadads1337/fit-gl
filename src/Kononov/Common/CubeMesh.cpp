#include "CubeMesh.hpp"

namespace Kononov {
const std::vector<Kononov::RegularVertex> cubeVertices = {
    {{-1.0F, -1.0F, 1.0F}, {0, 0, 1}, {0.0F, 0.0F}},  // v0
    {{1.0F, -1.0F, 1.0F}, {0, 0, 1}, {0.333F, 0.0F}}, // v1
    {{-1.0F, 1.0F, 1.0F}, {0, 0, 1}, {0.0F, 0.5F}},   // v2
    {{1.0F, 1.0F, 1.0F}, {0, 0, 1}, {0.333F, 0.5F}},  // v3

    // Vertex data for face 1
    {{1.0F, -1.0F, 1.0F}, {1, 0, 0}, {0.0F, 0.5F}},    // v4
    {{1.0F, -1.0F, -1.0F}, {1, 0, 0}, {0.333F, 0.5F}}, // v5
    {{1.0F, 1.0F, 1.0F}, {1, 0, 0}, {0.0F, 1.0F}},     // v6
    {{1.0F, 1.0F, -1.0F}, {1, 0, 0}, {0.333F, 1.0F}},  // v7

    // Vertex data for face 2
    {{1.0F, -1.0F, -1.0F}, {0, 0, -1}, {0.666F, 0.5F}}, // v8
    {{-1.0F, -1.0F, -1.0F}, {0, 0, -1}, {1.0F, 0.5F}},  // v9
    {{1.0F, 1.0F, -1.0F}, {0, 0, -1}, {0.666F, 1.0F}},  // v10
    {{-1.0F, 1.0F, -1.0F}, {0, 0, -1}, {1.0F, 1.0F}},   // v11

    // Vertex data for face 3
    {{-1.0F, -1.0F, -1.0F}, {-1, 0, 0}, {0.666F, 0.0F}}, // v12
    {{-1.0F, -1.0F, 1.0F}, {-1, 0, 0}, {1.0F, 0.0F}},    // v13
    {{-1.0F, 1.0F, -1.0F}, {-1, 0, 0}, {0.666F, 0.5F}},  // v14
    {{-1.0F, 1.0F, 1.0F}, {-1, 0, 0}, {1.0F, 0.5F}},     // v15

    // Vertex data for face 4
    {{-1.0F, -1.0F, -1.0F}, {0, -1, 0}, {0.333F, 0.0F}}, // v16
    {{1.0F, -1.0F, -1.0F}, {0, -1, 0}, {0.666F, 0.0F}},  // v17
    {{-1.0F, -1.0F, 1.0F}, {0, -1, 0}, {0.333F, 0.5F}},  // v18
    {{1.0F, -1.0F, 1.0F}, {0, -1, 0}, {0.666F, 0.5F}},   // v19

    // Vertex data for face 5
    {{-1.0F, 1.0F, 1.0F}, {0, 1, 0}, {0.333F, 0.5F}},  // v20
    {{1.0F, 1.0F, 1.0F}, {0, 1, 0}, {0.666F, 0.5F}},   // v21
    {{-1.0F, 1.0F, -1.0F}, {0, 1, 0}, {0.333F, 1.0F}}, // v22
    {{1.0F, 1.0F, -1.0F}, {0, 1, 0}, {0.666F, 1.0F}},  // v23
};

// Indices for drawing cube faces using triangle strips.
// Triangle strips can be connected by duplicating indices
// between the strips. If connecting strips have opposite
// vertex order then last index of the first strip and first
// index of the second strip needs to be duplicated. If
// connecting strips have same vertex order then only last
// index of the first strip needs to be duplicated.
const std::vector<GLuint> cubeStripeIndices = {
    0,  1,  2,  3,  3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    4,  4,  5,  6,  7,  7,  // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    8,  8,  9,  10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
};

const std::vector<GLuint> cubeTrianglesIndices = {
    0,  1,  2,  2,  1,  3,  4,  5,  6,  6,  5,  7,  8,  9,  10, 10, 9,  11,
    12, 13, 14, 14, 13, 15, 16, 17, 18, 18, 17, 19, 20, 21, 22, 22, 21, 23,
};

} // namespace Kononov