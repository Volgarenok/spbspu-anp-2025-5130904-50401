#include "geom.hpp"

bool kuznetsov::operator==(const point_t& a, const point_t& b)
{
  return a.x == b.x && a.y == b.y;
}

bool kuznetsov::operator!=(const point_t& a, const point_t& b)
{
  return !(a == b);
}

