#include "rectangle.hpp"
#include <stdexcept>

chernov::Rectangle::Rectangle(double a, double b, point_t o):
  Shape(),
  side_x(a),
  side_y(b),
  center(o)
{
  if (side_x <= 0 || side_y <= 0) {
    throw std::invalid_argument("the side must be greater than 0");
  }
}

double chernov::Rectangle::getArea() const
{
  return side_x * side_y;
}

chernov::rectangle_t chernov::Rectangle::getFrameRect() const
{
  return {side_x, side_y, center};
}

void chernov::Rectangle::move(point_t p)
{
  center = p;
}

void chernov::Rectangle::move(double dx, double dy)
{
  move({center.x + dx, center.y + dy});
}

void chernov::Rectangle::doScale(double k)
{
  side_x *= k;
  side_y *= k;
}
