#include <headers/isotropical_scaling.hpp>

void khasnulin::isotropicScaling(IShape &shape, point_t scale_pt, double scale)
{
  rectangle_t base_frame = shape.getFrameRect();
  point_t old_right_top = getRightTop(base_frame);

  shape.move(scale_pt);

  rectangle_t new_frame = shape.getFrameRect();
  point_t new_right_top = getRightTop(new_frame);

  shape.scale(scale);

  point_t delta = (old_right_top - new_right_top) * scale;

  shape.move(delta.x, delta.y);
}

khasnulin::point_t khasnulin::getRightTop(rectangle_t frame)
{
  return frame.pos + point_t{frame.width / 2, frame.height / 2};
}
