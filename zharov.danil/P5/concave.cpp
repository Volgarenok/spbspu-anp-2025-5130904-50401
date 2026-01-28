#include "concave.hpp"

zharov::Concave::Concave(const point_t * points, point_t pos):
  Shape(),
  points_{points[0], points[1], points[2], points[3]},
  pos_(pos)
{}

zharov::Concave::Concave(point_t p1, point_t p2, point_t p3, point_t pos):
  Shape(),
  points_{p1, p2, p3, pos},
  pos_(pos)
{}

double zharov::Concave::getArea() const
{
  return getAreaUni(points_, 4);
}

zharov::rectangle_t zharov::Concave::getFrameRect() const
{
  return getFrameRectUni(points_, 4);
}

void zharov::Concave::move(point_t p)
{
  move(p.x - pos_.x, p.y - pos_.y);
}

void zharov::Concave::move(double dx, double dy)
{
  for (size_t i = 0; i < 4; ++i) {
    points_[i].x += dx;
    points_[i].y += dy;
  }
  pos_.x += dx;
  pos_.y += dy;
}

void zharov::Concave::scale(double positive_k)
{
  for (size_t i = 0; i < 4; ++i) {
    points_[i].x = pos_.x + (points_[i].x - pos_.x) * positive_k;
    points_[i].y = pos_.y + (points_[i].y - pos_.y) * positive_k;
  }
}
