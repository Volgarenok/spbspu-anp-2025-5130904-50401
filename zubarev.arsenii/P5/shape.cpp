#include "shape.hpp"
#include <stdexcept>

void zubarev::Shape::scale(double k)
{
  if (k <= 0.0) {
    throw std::invalid_argument("Scale factor must be positive");
  }
  doScale(k);
}
