#ifndef CONCAVE_HPP
#define CONCAVE_HPP
#include "shape.hpp"

namespace zharov
{
  struct Concave: Shape {
    Concave(const point_t * points, point_t pos);
    Concave(point_t p1, point_t p2, point_t p3, point_t pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double positive_k) override;
  private:
    point_t points_[4];
    point_t pos_;
  };
}

#endif
