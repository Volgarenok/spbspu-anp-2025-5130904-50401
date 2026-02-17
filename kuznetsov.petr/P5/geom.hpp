#ifndef GEOM_HPP
#define GEOM_HPP

namespace kuznetsov {
  struct point_t {
    double x, y;
  };
  bool operator==(const point_t& a, const point_t& b);
  bool operator!=(const point_t& a, const point_t& b);

  struct rectangle_t {
    double width, height;
    point_t pos;
  };
}

#endif

