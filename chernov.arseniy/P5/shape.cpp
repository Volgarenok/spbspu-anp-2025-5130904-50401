#include "shape.hpp"
#include <cstddef>
#include <stdexcept>

void chernov::Shape::scale(double k)
{
  if (k <= 0.0) {
    throw std::invalid_argument("scale factor must be positive");
  }
  doScale(k);
}

void chernov::scaleByPoint(Shape ** shapes, size_t count, double k, point_t p)
{
  for (size_t i = 0; i < count; ++i) {
    Shape * shape = shapes[i];
    point_t first_pos = shape->getFrameRect().pos;
    shape->move(p);
    point_t second_pos = shape->getFrameRect().pos;
    double dx = k * (first_pos.x - second_pos.x);
    double dy = k * (first_pos.y - second_pos.y);
    shape->move(dx, dy);
    shape->scale(k);
  }
}

chernov::rectangle_t chernov::getBoundingRect(const Shape * const * shapes, size_t count)
{
  point_t * verts = new point_t[count * 2];
  for (size_t i = 0; i < count; ++i) {
    rectangle_t frame = shapes[i]->getFrameRect();
    verts[2 * i] = {frame.pos.x - frame.width / 2, frame.pos.y - frame.height / 2};
    verts[2 * i + 1] = {frame.pos.x + frame.width / 2, frame.pos.y + frame.height / 2};
  }
  rectangle_t frame_rect = getFrameRectByVerts(verts, count);
  delete [] verts;
  return frame_rect;
}
