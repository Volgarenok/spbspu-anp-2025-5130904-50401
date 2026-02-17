#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.hpp"

namespace zubarev
{
  struct Rectangle : Shape
  {
    Rectangle(double width, double height, const point_t& pos);
    virtual ~Rectangle() = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;

  protected:
    void doScale(double k) override;
  private:
    double width_, height_;
    point_t pos_;
  };
}

#endif
