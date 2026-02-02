#ifndef ISOTROPICAL_SCALING_HPP
#define ISOTROPICAL_SCALING_HPP

#include "ishape.hpp"

namespace khasnulin
{
  void isotropicScaling(IShape &shape, point_t scale_pt, double scale);

  point_t getRightTop(rectangle_t frame);
}

#endif
