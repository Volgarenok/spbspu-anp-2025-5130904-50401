#ifndef GROUP_SHAPE_HPP
#define GROUP_SHAPE_HPP

#include "composite_figure.hpp"
#include <headers/shapes/ishape.hpp>

namespace khasnulin
{
  class GroupShape: public CompositeFigure, public IShape
  {
  public:
    GroupShape(const GroupShape &) = default;

    ~GroupShape() override = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

    IShape *clone() const override;

  private:
    const char *getShapeName() const override;
    void doScale(double k) override;
  };
}

#endif
