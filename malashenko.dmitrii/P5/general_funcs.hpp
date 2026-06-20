#ifndef GENERALFUNCS
#define GENERALFUNCS
#include "pod.hpp"
#include <iostream>
namespace malashenko {
  rectangle_t generalGetFrameRect(const point_t * tops, size_t len);
  double generalGetArea(const point_t * tops, size_t len);
}
#endif
