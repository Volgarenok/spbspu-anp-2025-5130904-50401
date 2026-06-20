#ifndef TRIANGLE
#define TRIANGLE
#include "pod.hpp"
#include "shape.hpp"
#include <iostream>
namespace malashenko {
  struct Triangle : Shape {
    Triangle(point_t * tops);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    ~Triangle() override
    {
      delete[] tops_;
    }

  private:
    point_t * tops_;
    point_t pos_;
  };
}
#endif
