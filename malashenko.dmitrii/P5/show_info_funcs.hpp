#ifndef SHOWINFOFUNCS
#define SHOWINFOFUNCS
#include "pod.hpp"
#include "shape.hpp"
#include "iostream"
namespace malashenko {
  point_t * getCordsOfFrame(const rectangle_t & frame);
  void extend(point_t ** oldTops, const point_t * topsToAdd, size_t & l, size_t k);
  void showInfo(const Shape * const * figures, size_t len);
}
#endif
