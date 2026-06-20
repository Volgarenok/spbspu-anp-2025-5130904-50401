#ifndef POD
#define POD
namespace malashenko {
  struct point_t {
    double x, y;
  };

  struct rectangle_t {
    double width, height;
    point_t pos;
  };
}
#endif
