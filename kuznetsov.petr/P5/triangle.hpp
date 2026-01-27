#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"
namespace kuznetsov {

  class Triangle: public Shape {
  public:
    Triangle(point_t a, point_t b, point_t c);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double positiveK) override;
  private:
    point_t a_, b_, c_;
    point_t center_;
  };

}

#endif

