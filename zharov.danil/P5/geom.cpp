#include "geom.hpp"
#include <algorithm>

double zharov::getAreaUni(const point_t * points, size_t size)
{
  double area = 0.0;
  for (size_t i = 0; i < size; ++i) {
    size_t j = (i + 1) % size;
    area += points[i].x * points[j].y - points[j].x * points[i].y;
  }
  return std::abs(area) / 2.0;
}

zharov::rectangle_t zharov::getFrameRectUni(const point_t * points, size_t size)
{
  double min_x = points[0].x;
  double max_x = points[0].x;
  double min_y = points[0].y;
  double max_y = points[0].y;
  for (size_t i = 1; i < size; ++i) {
    min_x = std::min(min_x, points[i].x);
    max_x = std::max(max_x, points[i].x);
    min_y = std::min(min_y, points[i].y);
    max_y = std::max(max_y, points[i].y);
  }
  double width = max_x - min_x;
  double height = max_y - min_y;
  point_t pos = {min_x + width / 2, min_y + height / 2};
  return {width, height, pos};
}

zharov::point_t zharov::getCentroid(const point_t * points, size_t size)
{
  double area = 0.0, cx = 0.0, cy = 0.0;
  for (size_t i = 0; i < size; ++i) {
    size_t j = (i + 1) % size;
    double cross = points[i].x * points[j].y - points[j].x * points[i].y;
    area += cross;
    cx += (points[i].x + points[j].x) * cross;
    cy += (points[i].y + points[j].y) * cross;
  }
  area /= 2.0;
  return {cx / (std::abs(area) * 6.0), cy / (std::abs(area) * 6.0)};
}
