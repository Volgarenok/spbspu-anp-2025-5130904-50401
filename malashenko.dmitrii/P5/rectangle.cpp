#include "rectangle.hpp"

namespace malashenko {
  Rectangle::Rectangle(double width, double height, point_t pos):
    pos_(pos)
  {
    if (width > 0) {
      width_ = width;
    } else {
      throw std::invalid_argument("width of rectangle must be positive");
    }

    if (height > 0) {
      height_ = height;
    } else {
      throw std::invalid_argument("height of rectangle must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return { width_, height_, pos_ };
  }

  void Rectangle::move(point_t p)
  {
    pos_ = p;
  }

  void Rectangle::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k < 0) {
      throw std::invalid_argument("Scale coefficient of rectangle must be positive");
    }

    width_ *= k;
    height_ *= k;
  }
}
