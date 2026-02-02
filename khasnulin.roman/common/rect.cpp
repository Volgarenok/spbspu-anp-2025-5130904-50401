#include <headers/shapes/rect.hpp>
#include <stdexcept>

khasnulin::Rectangle::Rectangle(point_t pos, double w, double h):
    rect({w, h, pos})
{
  if (w <= 0.0 || h <= 0.0)
  {
    throw std::invalid_argument("incorrect rectangle creation: width and height must be positive");
  }
}

double khasnulin::Rectangle::getArea() const
{
  return rect.width * rect.height;
}

khasnulin::rectangle_t khasnulin::Rectangle::getFrameRect() const
{
  return rect;
}

void khasnulin::Rectangle::move(double dx, double dy)
{
  rect.pos.x += dx;
  rect.pos.y += dy;
}

void khasnulin::Rectangle::move(point_t to)
{
  rect.pos = to;
}

const char *khasnulin::Rectangle::getShapeName() const
{
  return "rectangle";
}

void khasnulin::Rectangle::doScale(double k)
{
  rect.width *= k;
  rect.height *= k;
}
