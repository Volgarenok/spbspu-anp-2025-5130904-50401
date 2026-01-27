#include "polygon.hpp"
#include <stdexcept>

zharov::Polygon::Polygon(const point_t * points, size_t size):
  Shape(),
  size_(size),
  points_(new point_t[size]),
  pos_(getCentroid(points, size))
{
  if (size_ < 3) {
    delete[] points_;
    throw std::invalid_argument("Not enough points");
  }
  for (size_t i = 0; i < size; ++i) {
    points_[i] = points[i];
  }
}

zharov::Polygon::~Polygon()
{
  delete[] points_;
}

zharov::Polygon::Polygon(const Polygon & polygon):
  Shape(),
  size_(polygon.size_),
  points_(new point_t[polygon.size_]),
  pos_(polygon.pos_)
{
  for (size_t i = 0; i < size_; ++i) {
    points_[i] = polygon.points_[i];
  }
}

zharov::Polygon & zharov::Polygon::operator=(const Polygon & polygon)
{
  if (this == std::addressof(polygon)) {
    return *this;
  }
  point_t * points = new point_t[polygon.size_];
  for (size_t i = 0; i < size_; ++i) {
    points[i] = polygon.points_[i];
  }
  delete[] points_;
  pos_ = polygon.pos_;
  size_ = polygon.size_;
  points_ = points;
  return *this;
}

zharov::Polygon::Polygon(Polygon && polygon):
  Shape(),
  size_(polygon.size_),
  points_(polygon.points_),
  pos_(polygon.pos_)
{
  polygon.points_ = nullptr;
}

zharov::Polygon & zharov::Polygon::operator=(Polygon && polygon)
{
  if (this == std::addressof(polygon)) {
    return *this;
  }
  delete[] points_;
  pos_ = polygon.pos_;
  size_ = polygon.size_;
  points_ = polygon.points_;
  polygon.points_ = nullptr;
  return *this;
}

double zharov::Polygon::getArea() const
{
  return getAreaUni(points_, size_);
}

zharov::rectangle_t zharov::Polygon::getFrameRect() const
{
  return getFrameRectUni(points_, size_);
}

void zharov::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i) {
    points_[i].x += dx;
    points_[i].y += dy;
  }
  pos_.x += dx;
  pos_.y += dy;
}

void zharov::Polygon::move(point_t p)
{
  move(p.x - pos_.x, p.y - pos_.y);
}

void zharov::Polygon::scale(double positive_k)
{
  for (size_t i = 0; i < size_; ++i) {
    points_[i].x = pos_.x + (points_[i].x - pos_.x) * positive_k;
    points_[i].y = pos_.y + (points_[i].y - pos_.y) * positive_k;
  }
}
