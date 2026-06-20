#include "general_funcs.hpp"

namespace malashenko {
  rectangle_t generalGetFrameRect(const point_t * tops, size_t len)
  {
    rectangle_t resRect;

    double minX = tops[0].x, minY = tops[0].y;
    double maxX = tops[0].x, maxY = tops[0].y;

    for (size_t i = 1; i < len; ++i) {
      point_t p = tops[i];
      minX = std::min(minX, p.x);
      minY = std::min(minY, p.y);
      maxX = std::max(maxX, p.x);
      maxY = std::max(maxY, p.y);
    }

    resRect.width = maxX - minX;
    resRect.height = maxY - minY;
    resRect.pos = {minX + resRect.width / 2, minY + resRect.height / 2};

    return resRect;
  }

  double generalGetArea(const point_t * tops, size_t len)
  {
    double area = 0;

    for (size_t i = 0; i < len; ++i) {
      size_t j = (i + 1) % len;
      double tmp_area = (tops[i].x * tops[j].y) - (tops[j].x * tops[i].y);
      area += tmp_area;
    }

    return (area > 0 ? area : -area) / 2.0;
  }
}
