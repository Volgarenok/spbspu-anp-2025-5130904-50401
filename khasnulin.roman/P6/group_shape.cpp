#include "group_shape.hpp"

#include "composite_figure_utils.hpp"
#include <headers/isotropical_scaling.hpp>

double khasnulin::GroupShape::getArea() const
{
  double area = 0;
  for (size_t i = 0, end = size(); i < end; ++i)
  {
    area += get(i).getArea();
  }
  return area;
}

khasnulin::rectangle_t khasnulin::GroupShape::getFrameRect() const
{
  return calculateFiguresGeneralRectangleFrame(*this);
}

void khasnulin::GroupShape::move(point_t to)
{
  point_t delta = to - getFrameRect().pos;

  for (size_t i = 0, end = size(); i < end; ++i)
  {
    get(i).move(delta.x, delta.y);
  }
}

void khasnulin::GroupShape::move(double dx, double dy)
{
  for (size_t i = 0, end = size(); i < end; ++i)
  {
    get(i).move(dx, dy);
  }
}

khasnulin::IShape *khasnulin::GroupShape::clone() const
{
  return new GroupShape(*this);
}

const char *khasnulin::GroupShape::getShapeName() const
{
  return "shapes group";
}

void khasnulin::GroupShape::doScale(double k)
{
  point_t center = getFrameRect().pos;

  for (size_t i = 0, end = size(); i < end; ++i)
  {
    isotropicScaling(get(i), center, k);
  }
}
