#include "geom.hpp"
#include <algorithm>
#include <cstddef>

chernov::rectangle_t chernov::getFrameRectByVerts(const point_t * verts, size_t count)
{
  double min_x = verts[0].x, min_y = verts[0].y;
  double max_x = min_x, max_y = min_y;
  for (size_t i = 0; i < count; ++i) {
    min_x = std::min(min_x, verts[i].x);
    min_y = std::min(min_y, verts[i].y);
    max_x = std::max(max_x, verts[i].x);
    max_y = std::max(max_y, verts[i].y);
  }
  double width = max_x - min_x;
  double height = max_y - min_y;
  point_t pos = {min_x + width / 2, min_y + height / 2};
  return {width, height, pos};
}
