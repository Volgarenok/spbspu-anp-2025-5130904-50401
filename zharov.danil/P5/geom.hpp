#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>

namespace zharov
{
  struct point_t {
    double x, y;
  };

  struct rectangle_t {
    double width, height;
    point_t pos;
  };

  double getAreaUni(const point_t * points, size_t size);
  rectangle_t getFrameRectUni(const point_t * points, size_t size);
  point_t getCentroid(const point_t * points, size_t size);
}
#endif
