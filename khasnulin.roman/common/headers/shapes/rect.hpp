#ifndef RECT_HPP
#define RECT_HPP

#include <headers/shapes/ishape.hpp>

namespace khasnulin
{
  class Rectangle: public IShape
  {
  public:
    Rectangle(const Rectangle &) = default;
    Rectangle(point_t pos, double w, double h);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

    IShape *clone() const override;

  private:
    const char *getShapeName() const override;
    void doScale(double k) override;
    rectangle_t rect;
  };

}

#endif
