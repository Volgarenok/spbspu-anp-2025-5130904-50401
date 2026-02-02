#include "utils.hpp"
#include <istream>

void khasnulin::readScaleInfo(std::istream &in, point_t &scale_pt, double &scaleK)
{
  in >> scale_pt.x >> scale_pt.y;
  in >> scaleK;
  if (in.fail())
  {
    throw std::runtime_error("incorrect input: fail to read arguments, must be 3 double");
  }
  if (scaleK <= 0)
  {
    throw std::runtime_error("incorrect input: scale coefficient must be more than zero");
  }
}
