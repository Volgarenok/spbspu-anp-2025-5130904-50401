#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <cstddef>
#include "geom.hpp"

namespace chernov {
  struct Shape {
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t p) = 0;
    virtual void move(double dx, double dy) = 0;
    void scale(double positive_k);
  protected:
    virtual void doScale(double positive_k) = 0;
  };

  void scaleByPoint(Shape ** shapes, size_t count, double k, point_t p);
  rectangle_t getBoundingRect(const Shape * const * shapes, size_t count);
}

#endif
