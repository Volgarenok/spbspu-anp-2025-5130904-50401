#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "geom.hpp"
#include "shape.hpp"

namespace chernov {
  struct Rectangle: Shape {
    Rectangle(double a, double b, point_t o);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
  protected:
    void doScale(double k) override;
  private:
    double side_x, side_y;
    point_t center;
  };
}

#endif
