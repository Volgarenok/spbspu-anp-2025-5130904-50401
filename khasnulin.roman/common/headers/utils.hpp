#ifndef UTILS_HPP
#define UTILS_HPP

#include "point.hpp"
#include <iosfwd>

namespace khasnulin
{
  void readScaleInfo(std::istream &in, point_t &scale_pt, double &scaleK);
}

#endif
