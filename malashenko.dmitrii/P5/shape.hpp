#ifndef SHAPE
#define SHAPE
#include "pod.hpp"
#include <cstddef>

namespace malashenko {
  struct Shape {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
    virtual ~Shape() = default;
  };

  void scaleByPoint(Shape ** figure, size_t len, point_t scalePoint, double k);
}
#endif
