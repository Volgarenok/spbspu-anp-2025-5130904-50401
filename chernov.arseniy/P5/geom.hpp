#ifndef GEOM_HPP
#define GEOM_HPP

#include <cstddef>

namespace chernov {
  struct point_t {
    double x, y;
  };

  struct rectangle_t {
    double width, height;
    point_t pos;
  };

  rectangle_t getFrameRectByVerts(const point_t * verts, size_t count);
}

#endif
