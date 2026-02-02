#include "composite_figure.hpp"
#include "composite_figure_utils.hpp"
#include <headers/figures.hpp>
#include <iostream>

int main()
{
  using namespace khasnulin;

  CompositeFigure figures;

  size_t code = 0;
  try
  {
    figures.append(new Rectangle({1, 1}, 5, 3));
    const point_t poly_points[] = {{1, 1}, {3, 2}, {4, 2}, {4, 5}, {1, 5}};
    figures.append(new Polygon(poly_points, 5));
    figures.append(new Xquare({-5, -5}, 10));

    std::cout << "before figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, figures);

    double scale;
    point_t scale_pt;
    readScaleInfo(std::cin, scale_pt, scale);

    for (size_t i = 0, size = figures.size(); i < size; ++i)
    {
      isotropicScaling(figures.get(i), scale_pt, scale);
    }
    std::cout << "\nafter figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, figures);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    code = 1;
  }

  return code;
}
