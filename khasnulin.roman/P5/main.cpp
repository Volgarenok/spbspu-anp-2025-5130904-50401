#include <cstring>
#include <iostream>

#include <headers/figures.hpp>

int main()
{
  using namespace khasnulin;
  IShape *shapes[3];
  size_t size = 0;
  size_t code = 0;
  try
  {
    shapes[size++] = new Rectangle({1, 1}, 5, 3);
    const point_t poly_points[] = {{1, 1}, {3, 2}, {4, 2}, {4, 5}, {1, 5}};
    shapes[size++] = new Polygon(poly_points, 5);
    shapes[size++] = new Xquare({-5, -5}, 10);

    std::cout << "before figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);

    double scale;
    point_t scale_pt;

    readScaleInfo(std::cin, scale_pt, scale);

    for (size_t i = 0; i < size; i++)
    {
      isotropicScaling(*shapes[i], scale_pt, scale);
    }
    std::cout << "\nafter figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    code = 1;
  }

  for (size_t i = 0; i < size; i++)
  {
    delete shapes[i];
  }
  return code;
}
