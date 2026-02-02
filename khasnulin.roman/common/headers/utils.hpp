#ifndef UTILS_HPP
#define UTILS_HPP

#include <headers/point.hpp>
#include <iosfwd>

namespace khasnulin
{
  void readScaleInfo(std::istream &in, point_t &scale_pt, double &scaleK);
}

#endif
