#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cstddef>
#include "geom.hpp"
#include "shape.hpp"

namespace chernov {
  struct Polygon: Shape {
    Polygon(point_t * points, size_t size);
    ~Polygon() override;
    Polygon(const Polygon & p);
    Polygon & operator=(const Polygon & p);
    Polygon(Polygon && p);
    Polygon & operator=(Polygon && p);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    double getSignedArea() const;
    point_t getCentroid() const;
  protected:
    void doScale(double k) override;
  private:
    point_t * verts;
    size_t count;
    point_t center;
  };
}

#endif
