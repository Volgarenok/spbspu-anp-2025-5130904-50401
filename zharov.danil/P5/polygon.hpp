#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "shape.hpp"

namespace zharov
{
  struct Polygon: Shape {
    Polygon(const point_t * points, size_t size);
    ~Polygon();
    Polygon(const Polygon & polygon);
    Polygon & operator=(const Polygon & polygon);
    Polygon(Polygon && polygon);
    Polygon & operator=(Polygon && polygon);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double positive_k) override;
  private:
    size_t size_;
    point_t * points_;
    point_t pos_;
  };
}
#endif
