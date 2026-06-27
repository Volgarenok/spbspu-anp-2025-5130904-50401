#include "rectangle.hpp"
#include <stdexcept>
zubarev::Rectangle::Rectangle(double width, double height, const point_t& pos):
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width <= 0.0 || height <= 0.0) {
    throw std::invalid_argument("Width and height must be positive");
  }
}

double zubarev::Rectangle::getArea() const
{
  return width_ * height_;
}

zubarev::rectangle_t zubarev::Rectangle::getFrameRect() const
{
  rectangle_t frame = {width_, height_, pos_};
  return frame;
}

void zubarev::Rectangle::move(const point_t& p)
{
  pos_ = p;
}

void zubarev::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void zubarev::Rectangle::doScale(double k)
{
  width_ *= k;
  height_ *= k;
}
