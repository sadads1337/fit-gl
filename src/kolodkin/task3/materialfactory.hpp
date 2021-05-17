#pragma once

#include "material.hpp"

#include <QString>
#include <map>
#include <unordered_map>

class MaterialFactory {
public:
  inline static constexpr Material Gold{
      QVector3D(0.24725f, 0.19950f, 0.07450f),
      QVector3D(0.75164f, 0.60648f, 0.22648f),
      QVector3D(0.628281f, 0.555802f, 0.366065f), 51.2f};

  inline static constexpr Material Jade{
      QVector3D(0.135, 0.2225, 0.1575), QVector3D(0.54, 0.89, 0.63),
      QVector3D(0.316228, 0.316228, 0.316228), 12.8};

  inline static constexpr Material CyanPlastic{
      QVector3D(0.0f, 0.1f, 0.06f), QVector3D(0.0f, 0.50980392f, 0.50980392f),
      QVector3D(0.50196078f, 0.50196078f, 0.50196078f), 32.f};

  inline static constexpr Material Chrome{
      QVector3D(0.25, 0.25, 0.25), QVector3D(0.25, 0.25, 0.25),
      QVector3D(0.774597, 0.774597, 0.774597), 76.8f};

  inline static constexpr Material Copper{
      QVector3D(0.19125, 0.0735, 0.0225), QVector3D(0.7038, 0.27048, 0.0828),
      QVector3D(0.256777, 0.137622, 0.086014), 12.8};

  inline static constexpr Material YellowRubber{
      QVector3D(0.05, 0.05, 0.0), QVector3D(0.5, 0.5, 0.4),
      QVector3D(0.7, 0.7, 0.04), 100.f};
  //    inline static constexpr Material {
  //        QVector3D(),
  //        QVector3D(),
  //        QVector3D(),

  //    };
  inline static const std::unordered_map<int, Material> materialMap = {
      {0, Gold},   {1, Jade},   {2, CyanPlastic},
      {3, Chrome}, {4, Copper}, {5, YellowRubber}};

  inline static const std::map<int, QString> names = {
      {0, "Gold"},   {1, "Jade"},   {2, "Cyan Plastic"},
      {3, "Chrome"}, {4, "Copper"}, {5, "YellowRubber"}};

  inline static Material make(int index) { return materialMap.at(index); }
};
