#ifndef SHAPE_H
#define SHAPE_H
#include "geom.hpp"
#include <cstddef>

namespace zubarev
{
  struct Shape
  {
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& p) = 0;
    virtual void move(double dx, double dy) = 0;
    void scale(double k);

    protected:
      virtual void doScale(double k) = 0;
  };
}

#endif
