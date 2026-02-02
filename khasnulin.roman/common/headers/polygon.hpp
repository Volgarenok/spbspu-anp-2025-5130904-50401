#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "ishape.hpp"
#include <iosfwd>

namespace khasnulin
{
  class Polygon: public IShape
  {
  public:
    Polygon(const point_t *points, size_t k);

    Polygon(const Polygon &pol);
    Polygon(Polygon &&pol);

    ~Polygon();

    Polygon &operator=(const Polygon &pol);
    Polygon &operator=(Polygon &&pol);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

  private:
    const char *getShapeName() const override;
    void doScale(double k) override;
    point_t *vertex;
    size_t size;
    point_t center;
  };

}

#endif
