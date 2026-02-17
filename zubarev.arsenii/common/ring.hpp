#ifndef RING_H
#define RING_H
#include "shape.hpp"

namespace zubarev
{
  struct Ring : Shape
  {
    Ring(double r1, double r2, const point_t& pos);
    virtual ~Ring() = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
  protected:
    void doScale(double k) override;

  private:
    double r1_, r2_;
    point_t pos_;
  };
}

#endif
