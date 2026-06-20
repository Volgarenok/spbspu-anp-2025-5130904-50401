#include "composite_figure_utils.hpp"

#include <fstream>
#include <headers/figures_info.hpp>

void khasnulin::calculateAndPrintFiguresInfo(std::ostream &out, CompositeFigure &figures)
{
  double sum_area = 0;
  for (size_t i = 0, end = figures.size(); i < end; ++i)
  {
    printSingleShapeInfo(out, &figures.get(i), i);
    double area = figures.get(i).getArea();
    sum_area += area;
  }
  rectangle_t general_frame = calculateFiguresGeneralRectangleFrame(figures);
  printGeneralInfo(out, general_frame, sum_area);
}

khasnulin::rectangle_t khasnulin::calculateFiguresGeneralRectangleFrame(const CompositeFigure &figures)
{
  size_t size = figures.size();
  if (!size)
  {
    throw std::runtime_error("figures general frame: empty shapes array error");
  }
  rectangle_t general_frame = figures.get(0).getFrameRect();
  for (size_t i = 1; i < size; i++)
  {
    general_frame = getCommonRectangleFrame(general_frame, figures.get(i).getFrameRect());
  }
  return general_frame;
}
