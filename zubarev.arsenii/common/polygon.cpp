#include "polygon.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
zubarev::Polygon::Polygon(const size_t size, const point_t* peaks):
  size_(size)
{
  peaks_ = new point_t[size_];
  for (size_t i = 0; i < size_; ++i) {
    peaks_[i] = peaks[i];
  }
  pos_ = getCentroid();
}

zubarev::Polygon::~Polygon()
{
  delete[] peaks_;
}
zubarev::Polygon::Polygon(const Polygon& w):
  size_(w.size_),
  peaks_(w.size_ ? new point_t[w.size_] : nullptr),
  pos_(w.pos_)

{
  for (size_t i = 0; i < size_; ++i) {
    peaks_[i] = w.peaks_[i];
  }
}
zubarev::Polygon& zubarev::Polygon::operator=(const Polygon& w)
{
  point_t* r = nullptr;
  if (w.size_) {
    r = new point_t[w.size_];
    for (size_t i = 0; i < w.size_; ++i) {
      r[i] = w.peaks_[i];
    }
  }
  delete[] peaks_;
  peaks_ = r;
  size_ = w.size_;
  return *this;
}
zubarev::Polygon::Polygon(Polygon&& w):
  size_(w.size_),
  peaks_(w.peaks_),
  pos_(w.pos_)
{
  w.peaks_ = nullptr;
}
zubarev::Polygon& zubarev::Polygon::operator=(zubarev::Polygon&& w)
{
  if (this == &w) {
    return *this;
  }
  delete[] peaks_;
  peaks_ = w.peaks_;
  size_ = w.size_;
  w.peaks_ = nullptr;
  return *this;
}
double zubarev::Polygon::getArea() const
{
  double res = 0;
  for (size_t i = 0; i < size_ - 1; ++i) {
    res += (peaks_[i].x * peaks_[i + 1].y - peaks_[i + 1].x * peaks_[i].y);
  }
  res += (peaks_[size_ - 1].x * peaks_[0].y - peaks_[0].x * peaks_[size_ - 1].y);
  return 0.5 * std::abs(res);
}

zubarev::point_t zubarev::Polygon::getCentroid() const
{
  double A = getArea();
  double Cx = 0, Cy = 0;
  double temp = 0;

  for (size_t i = 0; i < size_ - 1; ++i) {
    temp = peaks_[i].x * peaks_[i + 1].y - peaks_[i + 1].x * peaks_[i].y;
    Cx += (peaks_[i].x + peaks_[i + 1].x) * temp;
    Cy += (peaks_[i].y + peaks_[i + 1].y) * temp;
  }

  temp = peaks_[size_ - 1].x * peaks_[0].y - peaks_[0].x * peaks_[size_ - 1].y;
  Cx += (peaks_[size_ - 1].x + peaks_[0].x) * temp;
  Cy += (peaks_[size_ - 1].y + peaks_[0].y) * temp;

  Cx /= (6 * A);
  Cy /= (6 * A);

  return {Cx, Cy};
}

zubarev::rectangle_t zubarev::Polygon::getFrameRect() const
{
  point_t leftExPt = peaks_[0];
  point_t rightExPt = peaks_[0];

  for (size_t i = 1; i < size_; ++i) {
    leftExPt.x  = std::min(leftExPt.x,  peaks_[i].x);
    rightExPt.x = std::max(rightExPt.x, peaks_[i].x);

    leftExPt.y  = std::max(leftExPt.y,  peaks_[i].y);
    rightExPt.y = std::min(rightExPt.y, peaks_[i].y);
  }

  rectangle_t allFrame = {};
  allFrame.height = leftExPt.y - rightExPt.y;
  allFrame.width = rightExPt.x - leftExPt.x;
  allFrame.pos = {leftExPt.x + allFrame.width / 2, leftExPt.y - allFrame.height / 2};
  return allFrame;
}

void zubarev::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i) {
    peaks_[i].x += dx;
    peaks_[i].y += dy;
  }
  pos_.x += dx;
  pos_.y += dy;
}

void zubarev::Polygon::move(const point_t& p)
{
  double dx = p.x - pos_.x;
  double dy = p.y - pos_.y;
  move(dx, dy);
}

void zubarev::Polygon::doScale(double k)
{
  point_t c = getCentroid();

  for (size_t i = 0; i < size_; ++i) {
    peaks_[i].x = c.x + (peaks_[i].x - c.x) * k;
    peaks_[i].y = c.y + (peaks_[i].y - c.y) * k;
  }
}
