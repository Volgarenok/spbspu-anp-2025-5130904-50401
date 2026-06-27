#ifndef GEOM_H
#define GEOM_H
namespace zubarev
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
}
#endif
