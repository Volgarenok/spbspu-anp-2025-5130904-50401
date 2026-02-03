#ifndef GROUP_SHAPE_HPP
#define GROUP_SHAPE_HPP

#include "composite_figure.hpp"
#include <headers/shapes/ishape.hpp>

namespace khasnulin
{
  class GroupShape: public CompositeFigure, public IShape
  {
  public:
    GroupShape() = default;
    GroupShape(const GroupShape &cf) = default;
    GroupShape(GroupShape &&cf) = default;

    ~GroupShape() = default;

    GroupShape &operator=(const GroupShape &cf) = default;
    GroupShape &operator=(GroupShape &&cf) = default;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

    const char *getShapeName() const override;

    IShape *clone() const override;

  private:
    void doScale(double k) override;
  };
}

#endif
