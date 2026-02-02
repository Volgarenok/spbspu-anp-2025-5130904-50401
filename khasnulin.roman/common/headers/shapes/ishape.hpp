#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include <headers/frame_rect.hpp>
#include <headers/point.hpp>

namespace khasnulin
{
  class IShape
  {
  public:
    virtual ~IShape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t to) = 0;
    virtual void move(double dx, double dy) = 0;

    virtual IShape *clone() const = 0;

    void scale(double k);

  private:
    const virtual char *getShapeName() const = 0;
    virtual void doScale(double k) = 0;
  };
}

#endif
