#include <cstddef>
#include <headers/point.hpp>

khasnulin::point_t khasnulin::operator-(point_t p_t1, point_t p_t2)
{
  return {p_t1.x - p_t2.x, p_t1.y - p_t2.y};
}

khasnulin::point_t khasnulin::operator+(point_t p_t1, point_t p_t2)
{
  return {p_t1.x + p_t2.x, p_t1.y + p_t2.y};
}

khasnulin::point_t khasnulin::operator*(point_t p_t1, double k)
{
  return {p_t1.x * k, p_t1.y * k};
}

khasnulin::point_t khasnulin::operator/(point_t p_t1, double k)
{
  return {p_t1.x / k, p_t1.y / k};
}

khasnulin::point_t *khasnulin::copy(const point_t *from, point_t *to, size_t k)
{
  for (size_t i = 0; i < k; i++)
  {
    to[i] = from[i];
  }
  return to + k;
}
