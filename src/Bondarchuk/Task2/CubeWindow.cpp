#include "CubeWindow.hpp"
#include <QApplication>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_0_Core>
#include <QRgb>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <array>
#include <chrono>
#include <ctime>

namespace {

constexpr std::array<QVector3D, 194u> vertices = {
    QVector3D(1.000000f, 1.000000f, -1.000000f),
    QVector3D(1.000000f, -1.000000f, -1.000000f),
    QVector3D(1.000000f, 1.000000f, 1.000000f),
    QVector3D(1.000000f, -1.000000f, 1.000000f),
    QVector3D(-1.000000f, 1.000000f, -1.000000f),
    QVector3D(-1.000000f, -1.000000f, -1.000000f),
    QVector3D(-1.000000f, 1.000000f, 1.000000f),
    QVector3D(-1.000000f, -1.000000f, 1.000000f),
    QVector3D(-1.000000f, -1.000000f, -0.666667f),
    QVector3D(-1.000000f, -1.000000f, -0.333333f),
    QVector3D(-1.000000f, -1.000000f, 0.000000f),
    QVector3D(-1.000000f, -1.000000f, 0.333333f),
    QVector3D(-1.000000f, -1.000000f, 0.666667f),
    QVector3D(1.000000f, 1.000000f, -0.666667f),
    QVector3D(1.000000f, 1.000000f, -0.333333f),
    QVector3D(1.000000f, 1.000000f, 0.000000f),
    QVector3D(1.000000f, 1.000000f, 0.333333f),
    QVector3D(1.000000f, 1.000000f, 0.666667f),
    QVector3D(-1.000000f, 1.000000f, 0.666667f),
    QVector3D(-1.000000f, 1.000000f, 0.333333f),
    QVector3D(-1.000000f, 1.000000f, -0.000000f),
    QVector3D(-1.000000f, 1.000000f, -0.333333f),
    QVector3D(-1.000000f, 1.000000f, -0.666667f),
    QVector3D(1.000000f, -1.000000f, 0.666667f),
    QVector3D(1.000000f, -1.000000f, 0.333333f),
    QVector3D(1.000000f, -1.000000f, -0.000000f),
    QVector3D(1.000000f, -1.000000f, -0.333333f),
    QVector3D(1.000000f, -1.000000f, -0.666667f),
    QVector3D(0.600000f, -1.000000f, -1.000000f),
    QVector3D(0.200000f, -1.000000f, -1.000000f),
    QVector3D(-0.200000f, -1.000000f, -1.000000f),
    QVector3D(-0.600000f, -1.000000f, -1.000000f),
    QVector3D(0.600000f, 1.000000f, 1.000000f),
    QVector3D(0.200000f, 1.000000f, 1.000000f),
    QVector3D(-0.200000f, 1.000000f, 1.000000f),
    QVector3D(-0.600000f, 1.000000f, 1.000000f),
    QVector3D(-0.600000f, -1.000000f, 1.000000f),
    QVector3D(-0.200000f, -1.000000f, 1.000000f),
    QVector3D(0.200000f, -1.000000f, 1.000000f),
    QVector3D(0.600000f, -1.000000f, 1.000000f),
    QVector3D(-0.600000f, 1.000000f, -1.000000f),
    QVector3D(-0.200000f, 1.000000f, -1.000000f),
    QVector3D(0.200000f, 1.000000f, -1.000000f),
    QVector3D(0.600000f, 1.000000f, -1.000000f),
    QVector3D(0.600000f, -1.000000f, -0.666667f),
    QVector3D(0.200000f, -1.000000f, -0.666667f),
    QVector3D(-0.200000f, -1.000000f, -0.666667f),
    QVector3D(-0.600000f, -1.000000f, -0.666667f),
    QVector3D(0.600000f, -1.000000f, -0.333333f),
    QVector3D(0.200000f, -1.000000f, -0.333333f),
    QVector3D(-0.200000f, -1.000000f, -0.333333f),
    QVector3D(-0.600000f, -1.000000f, -0.333333f),
    QVector3D(0.600000f, -1.000000f, -0.000000f),
    QVector3D(0.200000f, -1.000000f, -0.000000f),
    QVector3D(-0.200000f, -1.000000f, 0.000000f),
    QVector3D(-0.600000f, -1.000000f, 0.000000f),
    QVector3D(0.600000f, -1.000000f, 0.333333f),
    QVector3D(0.200000f, -1.000000f, 0.333333f),
    QVector3D(-0.200000f, -1.000000f, 0.333333f),
    QVector3D(-0.600000f, -1.000000f, 0.333333f),
    QVector3D(0.600000f, -1.000000f, 0.666667f),
    QVector3D(0.200000f, -1.000000f, 0.666667f),
    QVector3D(-0.200000f, -1.000000f, 0.666667f),
    QVector3D(-0.600000f, -1.000000f, 0.666667f),
    QVector3D(-0.600000f, 1.000000f, -0.666667f),
    QVector3D(-0.200000f, 1.000000f, -0.666667f),
    QVector3D(0.200000f, 1.000000f, -0.666667f),
    QVector3D(0.600000f, 1.000000f, -0.666667f),
    QVector3D(-0.600000f, 1.000000f, -0.333333f),
    QVector3D(-0.200000f, 1.000000f, -0.333333f),
    QVector3D(0.200000f, 1.000000f, -0.333333f),
    QVector3D(0.600000f, 1.000000f, -0.333333f),
    QVector3D(-0.600000f, 1.000000f, -0.000000f),
    QVector3D(-0.200000f, 1.000000f, -0.000000f),
    QVector3D(0.200000f, 1.000000f, 0.000000f),
    QVector3D(0.600000f, 1.000000f, 0.000000f),
    QVector3D(-0.600000f, 1.000000f, 0.333333f),
    QVector3D(-0.200000f, 1.000000f, 0.333333f),
    QVector3D(0.200000f, 1.000000f, 0.333333f),
    QVector3D(0.600000f, 1.000000f, 0.333333f),
    QVector3D(-0.600000f, 1.000000f, 0.666667f),
    QVector3D(-0.200000f, 1.000000f, 0.666667f),
    QVector3D(0.200000f, 1.000000f, 0.666667f),
    QVector3D(0.600000f, 1.000000f, 0.666667f),
    QVector3D(1.000000f, 0.666667f, -1.000000f),
    QVector3D(1.000000f, 0.333333f, -1.000000f),
    QVector3D(1.000000f, -0.000000f, -1.000000f),
    QVector3D(1.000000f, -0.333333f, -1.000000f),
    QVector3D(1.000000f, -0.666667f, -1.000000f),
    QVector3D(-1.000000f, -0.666667f, 1.000000f),
    QVector3D(-1.000000f, -0.333333f, 1.000000f),
    QVector3D(-1.000000f, 0.000000f, 1.000000f),
    QVector3D(-1.000000f, 0.333333f, 1.000000f),
    QVector3D(-1.000000f, 0.666667f, 1.000000f),
    QVector3D(1.000000f, 0.666667f, 1.000000f),
    QVector3D(1.000000f, 0.333333f, 1.000000f),
    QVector3D(1.000000f, -0.000000f, 1.000000f),
    QVector3D(1.000000f, -0.333333f, 1.000000f),
    QVector3D(1.000000f, -0.666667f, 1.000000f),
    QVector3D(-1.000000f, 0.666667f, -1.000000f),
    QVector3D(-1.000000f, 0.333333f, -1.000000f),
    QVector3D(-1.000000f, -0.000000f, -1.000000f),
    QVector3D(-1.000000f, -0.333333f, -1.000000f),
    QVector3D(-1.000000f, -0.666667f, -1.000000f),
    QVector3D(1.000000f, 0.666667f, -0.666667f),
    QVector3D(1.000000f, 0.333333f, -0.666667f),
    QVector3D(1.000000f, -0.000000f, -0.666667f),
    QVector3D(1.000000f, -0.333333f, -0.666667f),
    QVector3D(1.000000f, -0.666667f, -0.666667f),
    QVector3D(1.000000f, 0.666667f, -0.333333f),
    QVector3D(1.000000f, 0.333333f, -0.333333f),
    QVector3D(1.000000f, -0.000000f, -0.333333f),
    QVector3D(1.000000f, -0.333333f, -0.333333f),
    QVector3D(1.000000f, -0.666667f, -0.333333f),
    QVector3D(1.000000f, 0.666667f, 0.000000f),
    QVector3D(1.000000f, 0.333333f, 0.000000f),
    QVector3D(1.000000f, -0.000000f, -0.000000f),
    QVector3D(1.000000f, -0.333333f, -0.000000f),
    QVector3D(1.000000f, -0.666667f, -0.000000f),
    QVector3D(1.000000f, 0.666667f, 0.333333f),
    QVector3D(1.000000f, 0.333333f, 0.333333f),
    QVector3D(1.000000f, -0.000000f, 0.333333f),
    QVector3D(1.000000f, -0.333333f, 0.333333f),
    QVector3D(1.000000f, -0.666667f, 0.333333f),
    QVector3D(1.000000f, 0.666667f, 0.666667f),
    QVector3D(1.000000f, 0.333333f, 0.666667f),
    QVector3D(1.000000f, -0.000000f, 0.666667f),
    QVector3D(1.000000f, -0.333333f, 0.666667f),
    QVector3D(1.000000f, -0.666667f, 0.666667f),
    QVector3D(-1.000000f, 0.666667f, 0.666667f),
    QVector3D(-1.000000f, 0.333333f, 0.666667f),
    QVector3D(-1.000000f, -0.000000f, 0.666667f),
    QVector3D(-1.000000f, -0.333333f, 0.666667f),
    QVector3D(-1.000000f, -0.666667f, 0.666667f),
    QVector3D(-1.000000f, 0.666667f, 0.333333f),
    QVector3D(-1.000000f, 0.333333f, 0.333333f),
    QVector3D(-1.000000f, -0.000000f, 0.333333f),
    QVector3D(-1.000000f, -0.333333f, 0.333333f),
    QVector3D(-1.000000f, -0.666667f, 0.333333f),
    QVector3D(-1.000000f, 0.666667f, -0.000000f),
    QVector3D(-1.000000f, 0.333333f, -0.000000f),
    QVector3D(-1.000000f, -0.000000f, 0.000000f),
    QVector3D(-1.000000f, -0.333333f, 0.000000f),
    QVector3D(-1.000000f, -0.666667f, 0.000000f),
    QVector3D(-1.000000f, 0.666667f, -0.333333f),
    QVector3D(-1.000000f, 0.333333f, -0.333333f),
    QVector3D(-1.000000f, -0.000000f, -0.333333f),
    QVector3D(-1.000000f, -0.333333f, -0.333333f),
    QVector3D(-1.000000f, -0.666667f, -0.333333f),
    QVector3D(-1.000000f, 0.666667f, -0.666667f),
    QVector3D(-1.000000f, 0.333333f, -0.666667f),
    QVector3D(-1.000000f, -0.000000f, -0.666667f),
    QVector3D(-1.000000f, -0.333333f, -0.666667f),
    QVector3D(-1.000000f, -0.666667f, -0.666667f),
    QVector3D(-0.600000f, 0.666667f, -1.000000f),
    QVector3D(-0.600000f, 0.333333f, -1.000000f),
    QVector3D(-0.600000f, -0.000000f, -1.000000f),
    QVector3D(-0.600000f, -0.333333f, -1.000000f),
    QVector3D(-0.600000f, -0.666667f, -1.000000f),
    QVector3D(-0.200000f, 0.666667f, -1.000000f),
    QVector3D(-0.200000f, 0.333333f, -1.000000f),
    QVector3D(-0.200000f, -0.000000f, -1.000000f),
    QVector3D(-0.200000f, -0.333333f, -1.000000f),
    QVector3D(-0.200000f, -0.666667f, -1.000000f),
    QVector3D(0.200000f, 0.666667f, -1.000000f),
    QVector3D(0.200000f, 0.333333f, -1.000000f),
    QVector3D(0.200000f, -0.000000f, -1.000000f),
    QVector3D(0.200000f, -0.333333f, -1.000000f),
    QVector3D(0.200000f, -0.666667f, -1.000000f),
    QVector3D(0.600000f, 0.666667f, -1.000000f),
    QVector3D(0.600000f, 0.333333f, -1.000000f),
    QVector3D(0.600000f, -0.000000f, -1.000000f),
    QVector3D(0.600000f, -0.333333f, -1.000000f),
    QVector3D(0.600000f, -0.666667f, -1.000000f),
    QVector3D(0.600000f, 0.666667f, 1.000000f),
    QVector3D(0.600000f, 0.333333f, 1.000000f),
    QVector3D(0.600000f, -0.000000f, 1.000000f),
    QVector3D(0.600000f, -0.333333f, 1.000000f),
    QVector3D(0.600000f, -0.666667f, 1.000000f),
    QVector3D(0.200000f, 0.666667f, 1.000000f),
    QVector3D(0.200000f, 0.333333f, 1.000000f),
    QVector3D(0.200000f, -0.000000f, 1.000000f),
    QVector3D(0.200000f, -0.333333f, 1.000000f),
    QVector3D(0.200000f, -0.666667f, 1.000000f),
    QVector3D(-0.200000f, 0.666667f, 1.000000f),
    QVector3D(-0.200000f, 0.333333f, 1.000000f),
    QVector3D(-0.200000f, -0.000000f, 1.000000f),
    QVector3D(-0.200000f, -0.333333f, 1.000000f),
    QVector3D(-0.200000f, -0.666667f, 1.000000f),
    QVector3D(-0.600000f, 0.666667f, 1.000000f),
    QVector3D(-0.600000f, 0.333333f, 1.000000f),
    QVector3D(-0.600000f, -0.000000f, 1.000000f),
    QVector3D(-0.600000f, -0.333333f, 1.000000f),
    QVector3D(-0.600000f, -0.666667f, 1.000000f),
};
constexpr std::array<GLuint, 768u> indexes = {
    80,  18,  6,   35,  189, 35,  6,   93,  149, 22,  4,   99,  60,  23,  3,
     39,  124, 17,  2,   94,  169, 43,  0,   84,  84,  0,   13,  104, 104, 13,
     14,  109, 109, 14,  15,  114, 114, 15,  16,  119, 119, 16,  17,  124, 28,
     1,   27,  44,  44,  27,  26,  48,  48,  26,  25,  52,  52,  25,  24,  56,
     56,  24,  23,  60,  93,  6,   18,  129, 129, 18,  19,  134, 134, 19,  20,
     139, 139, 20,  21,  144, 144, 21,  22,  149, 40,  4,   22,  64,  64,  22,
     21,  68,  68,  21,  20,  72,  72,  20,  19,  76,  76,  19,  18,  80,  16,
     79,  83,  17,  79,  78,  82,  83,  78,  77,  81,  82,  77,  76,  80,  81,
     15,  75,  79,  16,  75,  74,  78,  79,  74,  73,  77,  78,  73,  72,  76,
     77,  14,  71,  75,  15,  71,  70,  74,  75,  70,  69,  73,  74,  69,  68,
     72,  73,  13,  67,  71,  14,  67,  66,  70,  71,  66,  65,  69,  70,  65,
     64,  68,  69,  0,   43,  67,  13,  43,  42,  66,  67,  42,  41,  65,  66,
     41,  40,  64,  65,  11,  59,  63,  12,  59,  58,  62,  63,  58,  57,  61,
     62,  57,  56,  60,  61,  10,  55,  59,  11,  55,  54,  58,  59,  54,  53,
     57,  58,  53,  52,  56,  57,  9,   51,  55,  10,  51,  50,  54,  55,  50,
     49,  53,  54,  49,  48,  52,  53,  8,   47,  51,  9,   47,  46,  50,  51,
     46,  45,  49,  50,  45,  44,  48,  49,  5,   31,  47,  8,   31,  30,  46,
     47,  30,  29,  45,  46,  29,  28,  44,  45,  99,  4,   40,  154, 154, 40,
     41,  159, 159, 41,  42,  164, 164, 42,  43,  169, 12,  63,  36,  7,   63,
     62,  37,  36,  62,  61,  38,  37,  61,  60,  39,  38,  94,  2,   32,  174,
     174, 32,  33,  179, 179, 33,  34,  184, 184, 34,  35,  189, 17,  83,  32,
     2,   83,  82,  33,  32,  82,  81,  34,  33,  81,  80,  35,  34,  37,  188,
     193, 36,  188, 187, 192, 193, 187, 186, 191, 192, 186, 185, 190, 191, 185,
     184, 189, 190, 38,  183, 188, 37,  183, 182, 187, 188, 182, 181, 186, 187,
     181, 180, 185, 186, 180, 179, 184, 185, 39,  178, 183, 38,  178, 177, 182,
     183, 177, 176, 181, 182, 176, 175, 180, 181, 175, 174, 179, 180, 3,   98,
     178, 39,  98,  97,  177, 178, 97,  96,  176, 177, 96,  95,  175, 176, 95,
     94,  174, 175, 29,  168, 173, 28,  168, 167, 172, 173, 167, 166, 171, 172,
     166, 165, 170, 171, 165, 164, 169, 170, 30,  163, 168, 29,  163, 162, 167,
     168, 162, 161, 166, 167, 161, 160, 165, 166, 160, 159, 164, 165, 31,  158,
     163, 30,  158, 157, 162, 163, 157, 156, 161, 162, 156, 155, 160, 161, 155,
     154, 159, 160, 5,   103, 158, 31,  103, 102, 157, 158, 102, 101, 156, 157,
     101, 100, 155, 156, 100, 99,  154, 155, 9,   148, 153, 8,   148, 147, 152,
     153, 147, 146, 151, 152, 146, 145, 150, 151, 145, 144, 149, 150, 10,  143,
     148, 9,   143, 142, 147, 148, 142, 141, 146, 147, 141, 140, 145, 146, 140,
     139, 144, 145, 11,  138, 143, 10,  138, 137, 142, 143, 137, 136, 141, 142,
     136, 135, 140, 141, 135, 134, 139, 140, 12,  133, 138, 11,  133, 132, 137,
     138, 132, 131, 136, 137, 131, 130, 135, 136, 130, 129, 134, 135, 7,   89,
     133, 12,  89,  90,  132, 133, 90,  91,  131, 132, 91,  92,  130, 131, 92,
     93,  129, 130, 24,  123, 128, 23,  123, 122, 127, 128, 122, 121, 126, 127,
     121, 120, 125, 126, 120, 119, 124, 125, 25,  118, 123, 24,  118, 117, 122,
     123, 117, 116, 121, 122, 116, 115, 120, 121, 115, 114, 119, 120, 26,  113,
     118, 25,  113, 112, 117, 118, 112, 111, 116, 117, 111, 110, 115, 116, 110,
     109, 114, 115, 27,  108, 113, 26,  108, 107, 112, 113, 107, 106, 111, 112,
     106, 105, 110, 111, 105, 104, 109, 110, 1,   88,  108, 27,  88,  87,  107,
     108, 87,  86,  106, 107, 86,  85,  105, 106, 85,  84,  104, 105, 28,  173,
     88,  1,   173, 172, 87,  88,  172, 171, 86,  87,  171, 170, 85,  86,  170,
     169, 84,  85,  23,  128, 98,  3,   128, 127, 97,  98,  127, 126, 96,  97,
     126, 125, 95,  96,  125, 124, 94,  95,  8,   153, 103, 5,   153, 152, 102,
     103, 152, 151, 101, 102, 151, 150, 100, 101, 150, 149, 99,  100, 36,  193,
     89,  7,   193, 192, 90,  89,  192, 191, 91,  90,  191, 190, 92,  91,  190,
     189, 93,  92
};

/*
constexpr std::array<QVector3D, 8u> vertices = {

    QVector3D(-0.5f, -0.5f, 0.5f),  // v0
    QVector3D(0.5f, -0.5f, 0.5f),   // v1
    QVector3D(-0.5f, 0.5f, 0.5f),   // v2
    QVector3D(0.5f, 0.5f, 0.5f),    // v3
    QVector3D(0.5f, -0.5f, -0.5f),  // v4
    QVector3D(0.5f, 0.5f, -0.5f),   // v5
    QVector3D(-0.5f, -0.5f, -0.5f), // v6
    QVector3D(-0.5f, 0.5f, -0.5f)   // v7
};
// 0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4, 4, 6, 5, 7, 7, 6, 6, 0, 7, 2, 2, 0
constexpr std::array<GLuint, 34u> indexes = {0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4,
                                             4, 6, 5, 7, 7, 6, 6, 0, 7, 2, 2, 6,
                                             6, 4, 0, 1, 1, 2, 2, 3, 7, 5};
*/


} // namespace

namespace fgl {

void CubeWindow::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  start = std::chrono::system_clock::now();

  vbo.create();
  ibo.create();

  vbo.bind();
  vbo.allocate(vertices.data(),
               static_cast<std::int32_t>(vertices.size() * sizeof(QVector3D)));

  ibo.bind();
  ibo.allocate(indexes.data(),
               static_cast<std::int32_t>(indexes.size() * sizeof(GLuint)));

  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/cube.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/cube.fs");
  program_->link();

  posAttr_ = program_->attributeLocation("posAttr");
  matrixUniform_ = program_->uniformLocation("matrix");
  colAttr_ = program_->uniformLocation("colAttr");
}

void CubeWindow::render() {

  auto end = std::chrono::system_clock::now();
  time_ = end - start;

  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis);
  matrix.scale(0.5, 0.5, 0.5);

  program_->bind();
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", cube_color);
  program_->setUniformValue("time", time_.count());

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));

  program_->enableAttributeArray(posAttr_);
  program_->enableAttributeArray(colAttr_);

  program_->setUniformValue("flag", 1);

  vbo.bind();
  ibo.bind();
  glDrawElements(GL_QUADS, static_cast<GLsizei>(indexes.size()),
                 GL_UNSIGNED_INT, nullptr);

  program_->setUniformValue("flag", 0);
  glDrawElements(GL_LINES, static_cast<GLsizei>(indexes.size()),
                 GL_UNSIGNED_INT, nullptr);

  program_->disableAttributeArray(posAttr_);
  program_->disableAttributeArray(colAttr_);

  program_->release();
  ++frame_;
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    const auto color = QColorDialog::getColor();
    cube_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                           color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  mousePressPosition = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  const auto diff = QVector2D(event->localPos()) - mousePressPosition;
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}

} // namespace fgl