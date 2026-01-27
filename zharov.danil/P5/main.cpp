#include <iostream>
#include "geom.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "polygon.hpp"
#include "concave.hpp"

namespace zharov {
  void printInfo(const Shape * const shapes[], size_t size);
  void printInfoHelp(double area, rectangle_t frame);
}

int main()
{
  zharov::Shape * shapes[3] = {nullptr, nullptr, nullptr};
  zharov::point_t points_polygon[3] = {{0, 0}, {4, 0}, {0, 3}};
  int code = 0;
  try {
    shapes[0] = new zharov::Rectangle(5, 7, {0,0});
    shapes[1] = new zharov::Concave({0, 2}, {-2, -3}, {2, 0}, {0, 0});
    shapes[2] = new zharov::Polygon(points_polygon, 3);
    zharov::printInfo(shapes, 3);

    double positive_k = 0.0;
    zharov::point_t p;
    std::cout << "Enter p.x, p.y, positive k: ";
    std::cin >> p.x >> p.y >> positive_k;
    if (!std::cin) {
      std::cerr << "Bad enter\n";
      code = 1;
    } else {
      zharov::scaleByPoint(shapes, 3, {p.x, p.y}, positive_k);
      std::cout << "\n";
      zharov::printInfo(shapes, 3);
    }
  } catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    code = 1;
  }

  delete shapes[0];
  delete shapes[1];
  delete shapes[2];
  return code;
}

void zharov::printInfo(const Shape * const shapes[], size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    std::cout << "Shape #"<< i + 1 << "\n";
    printInfoHelp(shapes[i]->getArea(), shapes[i]->getFrameRect());
  }
  std::cout << "All shapes:\n";
  printInfoHelp(getAreaAll(shapes, size), getFrameRectAll(shapes, size));
}

void zharov::printInfoHelp(double area, rectangle_t frame)
{
  std::cout << "  Area: " << area << "\n";
  std::cout << "  Frame:\n";
  std::cout << "    Width: " << frame.width << "\n";
  std::cout << "    Hight: " << frame.height << "\n";
  std::cout << "    Center: (" << frame.pos.x << ", " << frame.pos.y << ")\n";
}
