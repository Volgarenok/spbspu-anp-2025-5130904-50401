#include "bubble.hpp"
#include <cmath>
#include <stdexcept>

chernov::Bubble::Bubble(double r, point_t o, point_t a):
  radius(r),
  center(o),
  anchor(a)
{
  if ((o.x - a.x) * (o.x - a.x) + (o.y - a.y) * (o.y - a.y) > r * r) {
    throw std::invalid_argument("the anchor must be inside the circle");
  }
  if (o.x == a.x && o.y == a.y) {
    throw std::invalid_argument("the anchor must not be equal to the center");
  }
  if (r <= 0) {
    throw std::invalid_argument("the radius must be greater than 0");
  }
}

double chernov::Bubble::getArea() const
{
  const double PI = acos(-1.0);
  double area = PI * radius * radius;
  return area;
}

chernov::rectangle_t chernov::Bubble::getFrameRect() const
{
  double size = 2 * radius;
  return {size, size, center};
}

void chernov::Bubble::move(point_t p)
{
  double dx = p.x - anchor.x;
  double dy = p.y - anchor.y;
  move(dx, dy);
}

void chernov::Bubble::move(double dx, double dy)
{
  anchor.x += dx;
  anchor.y += dy;
  center.x += dx;
  center.y += dy;
}

void chernov::Bubble::doScale(double k)
{
  radius *= k;
  double dx = center.x - anchor.x;
  double dy = center.y - anchor.y;
  center.x = anchor.x + k * dx;
  center.y = anchor.y + k * dy;
}
