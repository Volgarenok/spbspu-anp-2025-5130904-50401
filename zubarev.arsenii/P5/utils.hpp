#ifndef UTILS_H
#define UTILS_H

#include "shape.hpp"

namespace zubarev
{
  point_t getTopLeft(const rectangle_t& frame);
  point_t getBottomRight(const rectangle_t& frame);
  void scaleAtCertainPnt(Shape* shapes[], size_t size, point_t userPos, double k);
  rectangle_t getWholeFrame(Shape* shapes[], size_t size);
  double getWholeArea(Shape* shapes[], size_t size);
  void printInfo(Shape* shapes[], size_t size);
}

#endif
