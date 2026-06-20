#include "composite_figure.hpp"
#include "composite_figure_utils.hpp"
#include "group_shape.hpp"
#include <headers/figures.hpp>
#include <iostream>

int main()
{
  using namespace khasnulin;

  CompositeFigure figures;

  size_t code = 0;
  CompositeFigure smallComposition;
  GroupShape *groupShape;
  GroupShape *groupShape2;

  try
  {

    groupShape = new GroupShape();
    groupShape2 = new GroupShape();

    IShape *commonObj = new Xquare({1, 1}, 5);

    smallComposition.append(commonObj);
    smallComposition.append(new Rectangle({50, 50}, 23, 45));
    smallComposition.append(new Xquare({-40, -44}, 10));

    groupShape->append(new Xquare({10, 10}, 3));
    groupShape->append(new Rectangle({0, 0}, 10, 7));
    const point_t poly_points1[] = {{0, 0}, {3, 10}, {10, -10}, {4, 4}, {5, 1}};
    groupShape->append(new Polygon(poly_points1, 4));

    groupShape->printFiguresArray(std::cout);

    groupShape->append(smallComposition);
    groupShape->printFiguresArray(std::cout);

    groupShape->merge();
    groupShape->printFiguresArray(std::cout);

    groupShape2->append(new Polygon(poly_points1, 3));
    groupShape2->append(new Polygon(poly_points1, 4));
    groupShape2->append(new Rectangle({-100, -10000}, 10, 7));
    groupShape2->merge(*groupShape);

    groupShape2->printFiguresArray(std::cout);

    figures.append(groupShape);
    figures.append(new Rectangle({1, 1}, 5, 3));
    const point_t poly_points2[] = {{1, 1}, {3, 2}, {4, 2}, {4, 5}, {1, 5}};
    figures.append(new Polygon(poly_points2, 5));
    figures.append(new Xquare({-5, -5}, 10));
    figures.append(groupShape2);

    figures.printFiguresArray(std::cout);

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
