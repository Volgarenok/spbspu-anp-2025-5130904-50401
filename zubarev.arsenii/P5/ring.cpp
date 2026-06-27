#include "ring.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>
zubarev::Ring::Ring(double r1, double r2, const point_t& pos):
  r1_(r1),
  r2_(r2),
  pos_(pos)
{
  if (r1 <= 0.0 || r2 <= 0.0) {
    throw std::invalid_argument("Width and height must be positive");
  }
}

double zubarev::Ring::getArea() const
{
  return M_PI * std::abs(r1_ * r1_ - r2_ * r2_);
}

zubarev::rectangle_t zubarev::Ring::getFrameRect() const
{
  rectangle_t frame;
  double r = std::max(r1_, r2_);
  frame.pos = pos_;
  frame.width = 2 * r;
  frame.height = 2 * r;
  return frame;
}

void zubarev::Ring::move(const point_t& p)
{
  pos_ = p;
}

void zubarev::Ring::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void zubarev::Ring::doScale(double k)
{
  r1_ *= k;
  r2_ *= k;
}
