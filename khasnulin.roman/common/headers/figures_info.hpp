#ifndef FIGURES_INFO_HPP
#define FIGURES_INFO_HPP

#include "ishape.hpp"
#include <iosfwd>

namespace khasnulin
{
  void printRectInfo(std::ostream &out, rectangle_t rect);
  void printSingleShapeInfo(std::ostream &out, IShape *shape, size_t index);
  void printGeneralInfo(std::ostream &out, rectangle_t gen_frame, double gen_area);

  void calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size);

  rectangle_t getCommonRectangleFrame(rectangle_t r1, rectangle_t r2);
  rectangle_t calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size);
}

#endif
