#include "rectangle.hpp"
#include <stdexcept>

kuznetsov::Rectangle::Rectangle(double w, double h, point_t c):
  center_(c),
  width_(w),
  height_(h)
{
  if (w <= 0 || h <= 0) {
    throw std::invalid_argument("Invalid size");
  }
}

double kuznetsov::Rectangle::getArea() const
{
  return width_ * height_;
}

kuznetsov::rectangle_t kuznetsov::Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void kuznetsov::Rectangle::move(point_t p)
{
  center_ = p;
}

void kuznetsov::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void kuznetsov::Rectangle::scale(double positiveK)
{
  width_ *= positiveK;
  height_ *= positiveK;
}

