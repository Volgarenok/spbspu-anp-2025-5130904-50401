#include "shape.hpp"

void zharov::scaleByPoint(Shape * const shapes[], size_t size, point_t p, double positive_k)
{
  for (size_t i = 0; i < size; ++i) {
    point_t pos = shapes[i]->getFrameRect().pos;
    shapes[i]->move(p);
    double dx = positive_k * (pos.x - shapes[i]->getFrameRect().pos.x);
    double dy = positive_k * (pos.y - shapes[i]->getFrameRect().pos.y);
    shapes[i]->safeScale(positive_k);
    shapes[i]->move(dx, dy);
  }
}

double zharov::getAreaAll(const Shape * const shapes[], size_t size)
{
  double sum = 0;
  for (size_t i = 0; i < size; ++i) {
    sum += shapes[i]->getArea();
  }
  return sum;
}

zharov::rectangle_t zharov::getFrameRectAll(const Shape * const shapes[], size_t size)
{
  point_t * points = new point_t[size * 2];
  for (size_t i = 0; i < size; ++i) {
    rectangle_t frame = shapes[i]->getFrameRect();
    points[i * 2] = {frame.pos.x - frame.width / 2, frame.pos.y - frame.height / 2};
    points[i * 2 + 1] = {frame.pos.x + frame.width / 2, frame.pos.y + frame.height / 2};
  }
  rectangle_t frame = getFrameRectUni(points, size * 2);
  delete[] points;
  return frame;
}
