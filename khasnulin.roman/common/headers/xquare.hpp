#ifndef XQUARE_HPP
#define XQUARE_HPP

#include "ishape.hpp"

namespace khasnulin
{
  class Xquare: public IShape
  {
  public:
    Xquare(point_t cent, double d);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

  private:
    const char *getShapeName() const override;
    void doScale(double k) override;
    double diag;
    point_t center;
  };
}

#endif
