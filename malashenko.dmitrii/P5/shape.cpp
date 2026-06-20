#include "shape.hpp"

namespace malashenko {
  void scaleByPoint(Shape ** figure, size_t len, point_t scalePoint, double k)
  {
    for (size_t i = 0; i < len; ++i) {
      point_t firstCord = figure[i]->getFrameRect().pos;
      figure[i]->move(scalePoint);
      point_t secondcord = figure[i]->getFrameRect().pos;
      figure[i]->scale(k);

      double xdist = (firstCord.x - secondcord.x) * k;
      double ydist = (firstCord.y - secondcord.y) * k;

      figure[i]->move(xdist, ydist);
    }
  }
}
