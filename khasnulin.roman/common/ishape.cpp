#include <cstring>
#include <headers/ishape.hpp>
#include <stdexcept>

void khasnulin::IShape::scale(double k)
{
  if (k <= 0.0)
  {
    char message[256] = {};
    strcat(message, getShapeName());
    throw std::invalid_argument(
        std::strcat(message, " incorrect scaling: scale coefficient must be positive"));
  }
  doScale(k);
}
