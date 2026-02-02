#include <headers/xquare.hpp>
#include <stdexcept>

khasnulin::Xquare::Xquare(point_t cent, double d):
    diag(d),
    center(cent)
{
  if (d <= 0)
  {
    throw std::invalid_argument("fail Xquare creation: diagonal must be positive number");
  }
}

double khasnulin::Xquare::getArea() const
{
  return diag * diag / 2;
}
khasnulin::rectangle_t khasnulin::Xquare::getFrameRect() const
{
  return {diag, diag, center};
}
void khasnulin::Xquare::move(point_t to)
{
  center = to;
}
void khasnulin::Xquare::move(double dx, double dy)
{
  center.x += dx;
  center.y += dy;
}

const char *khasnulin::Xquare::getShapeName() const
{
  return "xquare";
}

void khasnulin::Xquare::doScale(double k)
{
  diag *= k;
}
