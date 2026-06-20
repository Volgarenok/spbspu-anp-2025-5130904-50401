#include "polygon.hpp"
#include <cstddef>
#include "general_funcs.hpp"

namespace malashenko {
    Polygon::Polygon(point_t * tops, size_t length):
    length_(length),
    tops_(length_ ? new point_t[length_] : nullptr)
  {
    if (length_ < 3) {
      delete[] tops_;
      throw std::invalid_argument("polygon must have at least 3 points");
    }

    for (size_t i = 0; i < length_; ++i) {
      tops_[i] = tops[i];
    }

    double area2 = 0.0, cx = 0.0, cy = 0.0;

    for (size_t i = 0; i < length_; ++i) {
      size_t j = (i + 1) % length_;

      double cross = tops_[i].x * tops_[j].y - tops_[j].x * tops_[i].y;
      area2 += cross;

      cx += (tops_[i].x + tops_[j].x) * cross;
      cy += (tops_[i].y + tops_[j].y) * cross;
    }

    if (area2 == 0.0) {
      delete[] tops_;
      throw std::invalid_argument("polygon area must be positive");
    }

    cx /= (3.0 * area2);
    cy /= (3.0 * area2);
    pos_.x = cx;
    pos_.y = cy;
  }

  double Polygon::getArea() const
  {
    return generalGetArea(tops_, length_);
  }

  rectangle_t Polygon::getFrameRect() const
  {
    return generalGetFrameRect(tops_, length_);
  }

  void Polygon::move(point_t p)
  {
    double dx = p.x - pos_.x;
    double dy = p.y - pos_.y;

    for (size_t i = 0; i < length_; ++i) {
      tops_[i].x += dx;
      tops_[i].y += dy;
    }

    pos_ = p;
  }

  void Polygon::move(double dx, double dy)
  {
    for (size_t i = 0; i < length_; ++i) {
      tops_[i].x += dx;
      tops_[i].y += dy;
    }

    pos_.x += dx;
    pos_.y += dy;
  }

  void Polygon::scale(double k)
  {
    if (k < 0) {
      throw std::invalid_argument("scale coefficient of polygon must be positive");
    }

    for (size_t i = 0; i < length_; ++i) {
      tops_[i].x = pos_.x + (tops_[i].x - pos_.x) * k;
      tops_[i].y = pos_.y + (tops_[i].y - pos_.y) * k;
    }
  }
}
