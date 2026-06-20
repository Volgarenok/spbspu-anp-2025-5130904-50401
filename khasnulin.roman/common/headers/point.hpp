#ifndef POINT_HPP
#define POINT_HPP

#include <cstddef>

namespace khasnulin
{
  struct point_t
  {
    double x, y;
  };

  point_t operator-(point_t p_t1, point_t p_t2);
  point_t operator+(point_t p_t1, point_t p_t2);
  point_t operator*(point_t p_t1, double k);
  point_t operator/(point_t p_t1, double k);

  point_t *copy(const point_t *from, point_t *to, size_t k);

}

#endif
