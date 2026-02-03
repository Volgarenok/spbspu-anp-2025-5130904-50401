#ifndef COMPOSITE_FIGURES_UTILS_HPP
#define COMPOSITE_FIGURES_UTILS_HPP

#include "composite_figure.hpp"
#include <iosfwd>

namespace khasnulin
{
  void calculateAndPrintFiguresInfo(std::ostream &out, CompositeFigure &figures);
  rectangle_t calculateFiguresGeneralRectangleFrame(const CompositeFigure &figures);
}

#endif
