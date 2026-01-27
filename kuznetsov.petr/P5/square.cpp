#include "square.hpp"
#include <stdexcept>

kuznetsov::Square::Square(double len, point_t c):
  center_(c),
  len_(len)
{
  if (len <= 0) {
    throw std::invalid_argument("Invalid size");
  }
}

double kuznetsov::Square::getArea() const
{
  return len_ * len_;
}

kuznetsov::rectangle_t kuznetsov::Square::getFrameRect() const
{
  return {len_, len_, center_};
}

void kuznetsov::Square::move(point_t p)
{
  center_ = p;
}

void kuznetsov::Square::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void kuznetsov::Square::scale(double positiveK)
{
  len_ *= positiveK;
}

