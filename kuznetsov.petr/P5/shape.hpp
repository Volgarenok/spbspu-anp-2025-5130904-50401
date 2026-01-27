#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "geom.hpp"
#include <stdexcept>
namespace kuznetsov {

  struct Shape {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double positiveK) = 0;
    virtual ~Shape() = default;
    void scaleSafe(double positiveK)
    {
      if (positiveK <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
      }
      scale(positiveK);
    }
  };

}

#endif

