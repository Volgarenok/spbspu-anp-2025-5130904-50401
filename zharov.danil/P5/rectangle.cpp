#include "rectangle.hpp"

zharov::Rectangle::Rectangle(double width, double height, point_t pos):
  Shape(),
  width_(width),
  height_(height),
  pos_(pos)
{}

double zharov::Rectangle::getArea() const
{
  return width_ * height_;
}

zharov::rectangle_t zharov::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void zharov::Rectangle::move(point_t p)
{
  pos_ = p;
}

void zharov::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void zharov::Rectangle::scale(double positive_k)
{
  width_ *= positive_k;
  height_ *= positive_k;
}
