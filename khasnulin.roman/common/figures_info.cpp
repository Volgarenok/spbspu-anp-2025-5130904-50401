#include <headers/figures_info.hpp>
#include <iostream>

void khasnulin::printRectInfo(std::ostream &out, rectangle_t rect)
{
  out << "rectangle center x:" << rect.pos.x << ", y: " << rect.pos.y << ", width: " << rect.width
      << ", height: " << rect.height << "\n";
}

khasnulin::rectangle_t khasnulin::getCommonRectangleFrame(rectangle_t r1, rectangle_t r2)
{
  double left = std::min(r1.pos.x - r1.width / 2, r2.pos.x - r2.width / 2);
  double right = std::max(r1.pos.x + r1.width / 2, r2.pos.x + r2.width / 2);
  double bottom = std::min(r1.pos.y - r1.height / 2, r2.pos.y - r2.height / 2);
  double top = std::max(r1.pos.y + r1.height / 2, r2.pos.y + r2.height / 2);
  return rectangle_t{right - left, top - bottom, {(right + left) / 2, (top + bottom) / 2}};
}

void khasnulin::calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size)
{
  double sum_area = 0;
  for (size_t i = 0; i < size; i++)
  {
    printSingleShapeInfo(out, shapes[i], i);
    double area = shapes[i]->getArea();
    sum_area += area;
  }
  rectangle_t general_frame = calculateFiguresGeneralRectangleFrame(shapes, size);
  printGeneralInfo(out, general_frame, sum_area);
}

void khasnulin::printSingleShapeInfo(std::ostream &out, IShape *shape, size_t index)
{
  out << "figure " << index << " area: " << shape->getArea() << "\n";
  rectangle_t rect = shape->getFrameRect();
  out << "figure " << index << " frame ";
  printRectInfo(out, rect);
}

void khasnulin::printGeneralInfo(std::ostream &out, rectangle_t gen_frame, double gen_area)
{
  out << "area sum: " << gen_area << "\n";
  out << "general figures frame ";
  printRectInfo(out, gen_frame);
}

khasnulin::rectangle_t khasnulin::calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size)
{
  if (!size)
  {
    throw std::runtime_error("figures general frame: empty shapes array error");
  }
  rectangle_t general_frame = shapes[0]->getFrameRect();
  for (size_t i = 1; i < size; i++)
  {
    general_frame = getCommonRectangleFrame(general_frame, shapes[i]->getFrameRect());
  }
  return general_frame;
}
