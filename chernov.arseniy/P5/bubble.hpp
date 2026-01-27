#ifndef BUBBLE_HPP
#define BUBBLE_HPP

#include "geom.hpp"
#include "shape.hpp"

namespace chernov {
  struct Bubble: Shape {
    Bubble(double r, point_t o, point_t a);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
  protected:
    void doScale(double k) override;
  private:
    double radius;
    point_t center, anchor;
  };
}

#endif
