#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <stdexcept>
#include "geom.hpp"

namespace zharov
{
  struct Shape {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t p) = 0;
    virtual void move(double dx, double dy) = 0;
    void safeScale(double positive_k)
    {
      if (positive_k <= 0.0) {
        throw std::invalid_argument("Scale factor must be positive");
      }
      scale(positive_k);
    }
  protected:
    virtual void scale(double positive_k) = 0;
  public:
    virtual ~Shape() = default;
  };

  void scaleByPoint(Shape * const shapes[], size_t size, point_t p, double positive_k);
  double getAreaAll(const Shape * const shapes[], size_t size);
  rectangle_t getFrameRectAll(const Shape * const shapes[], size_t size);
}
#endif
