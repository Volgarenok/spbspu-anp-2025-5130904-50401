#include "triangle.hpp"
#include <stdexcept>
#include <algorithm>

kuznetsov::Triangle::Triangle(point_t a, point_t b, point_t c):
  a_(a),
  b_(b),
  c_(c),
  center_{}
{
  bool incorrect = a_ == b_;
  incorrect = incorrect || a_ == c_;
  incorrect = incorrect || c_ == b_;
  bool oneLine = (b_.y - a_.y) * (c_.x - a_.x) == (c_.y - a_.y) * (b_.x - a_.x);
  incorrect = incorrect || oneLine;
  if (incorrect) {
    throw std::invalid_argument("Invalid vertexes, it's line");
  }
  double x = (a_.x + b_.x + c_.x) / 3;
  double y = (a_.y + b_.y + c_.y) / 3;
  center_ = {x, y};
}

double kuznetsov::Triangle::getArea() const
{
  double s = a_.x * (b_.y - c_.y);
  s = b_.x * (c_.y - a_.y) + s;
  s = c_.x * (a_.y - b_.y) + s;
  s = 0.5 * std::abs(s);
  return s;
}

kuznetsov::rectangle_t kuznetsov::Triangle::getFrameRect() const
{
  double maxX = std::max(a_.x, std::max(b_.x, c_.x));
  double minX = std::min(a_.x, std::min(b_.x, c_.x));
  double maxY = std::max(a_.y, std::max(b_.y, c_.y));
  double minY = std::min(a_.y, std::min(b_.y, c_.y));
  double cx = (maxX + minX) / 2;
  double cy = (maxY + minY) / 2;
  return {maxX - minX, maxY - minY, {cx, cy}};
}

void kuznetsov::Triangle::move(point_t p)
{
  double dx = p.x - center_.x;
  double dy = p.y - center_.y;
  move(dx, dy);
}

void kuznetsov::Triangle::move(double dx, double dy)
{
  a_.x += dx;
  a_.y += dy;

  b_.x += dx;
  b_.y += dy;

  c_.x += dx;
  c_.y += dy;

  center_.x += dx;
  center_.y += dy;
}

void kuznetsov::Triangle::scale(double positiveK)
{
  point_t dpa {a_.x - center_.x , a_.y - center_.y};
  point_t dpb {b_.x - center_.x , b_.y - center_.y};
  point_t dpc {c_.x - center_.x , c_.y - center_.y};

  a_.x = center_.x + dpa.x * positiveK;
  a_.y = center_.y + dpa.y * positiveK;

  b_.x = center_.x + dpb.x * positiveK;
  b_.y = center_.y + dpb.y * positiveK;

  c_.x = center_.x + dpc.x * positiveK;
  c_.y = center_.y + dpc.y * positiveK;
}

