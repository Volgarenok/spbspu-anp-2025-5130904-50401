#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "shape.hpp"
namespace kuznetsov {

  class Square: public Shape {
  public:
    Square(double len, point_t c);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double positiveK) override;
  private:
    point_t center_;
    double len_;
  };

}

#endif

