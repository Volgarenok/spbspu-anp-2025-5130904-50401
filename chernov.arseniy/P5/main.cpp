#include <iostream>
#include "bubble.hpp"
#include "geom.hpp"
#include "polygon.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

namespace chernov {
  std::ostream & printShapeInfo(std::ostream & out, double area, rectangle_t frame, const char * name);
  std::ostream & printShapesInfo(std::ostream & out, const Shape * const * shapes, const char * const * names, size_t count);
}

int main()
{
  using namespace chernov;

  std::ostream & output = std::cout;
  int result = 0;

  const size_t count = 5;
  Shape * shapes[count]{};
  const char * names[count];

  try {
    shapes[0] = new Rectangle(5, 6, {1, 2});
    names[0] = "Rectangle 1";

    shapes[1] = new Rectangle(10, 2, {-10, 3});
    names[1] = "Rectangle 2";

    point_t points1[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    size_t points_count = 4;
    shapes[2] = new Polygon(points1, points_count);
    names[2] = "Polygon 1";

    point_t points2[] = {{0, 0}, {4, 1}, {5, 4}, {5, 8}, {4, 10}, {3, 8}, {2, 5}, {-1, 1}};
    points_count = 8;
    shapes[3] = new Polygon(points2, points_count);
    names[3] = "Polygon 2";

    shapes[4] = new Bubble(10, {0, 0}, {2, 2});
    names[4] = "Bubble";

    printShapesInfo(output, shapes, names, count);

    output << "\n\nEnter x, y and k: ";

    double x = 0, y = 0, k = 0;
    while (std::cin >> x >> y >> k) {
      try {
        scaleByPoint(shapes, count, k, {x, y});
      } catch (const std::invalid_argument & e) {
        std::cerr << e.what() << "\n";
        result = 1;
        break;
      }
      output << "\n\n";
      printShapesInfo(output, shapes, names, count);
      output << "\n\nEnter x, y and k: ";
    }

    if (std::cin.fail() && (!std::cin.eof() || k == 0)) {
      std::cerr << "bad input\n";
      result = 1;
    }

  } catch (const std::bad_alloc & e) {
    std::cerr << "bad alloc\n";
    result = 2;
  }

  for (size_t i = 0; i < count; ++i) {
    delete shapes[i];
  }
  return result;
}

std::ostream & chernov::printShapeInfo(std::ostream & out, double area, rectangle_t frame, const char * name)
{
  out << name << ":\n";
  out << "  area: " << area << "\n";
  out << "  frame rectangle:\n";
  out << "    width: " << frame.width << "\n";
  out << "    height: " << frame.height << "\n";
  out << "    position: (" << frame.pos.x << "; " << frame.pos.y << ")\n";
  return out;
}

std::ostream & chernov::printShapesInfo(std::ostream & out, const Shape * const * shapes, const char * const * names, size_t count)
{
  double total_area = 0;
  for (size_t i = 0; i < count; ++i) {
    double area = shapes[i]->getArea();
    rectangle_t frame = shapes[i]->getFrameRect();
    printShapeInfo(out, area, frame, names[i]) << "\n";
    total_area += area;
  }
  rectangle_t total_frame = getBoundingRect(shapes, count);
  printShapeInfo(out, total_area, total_frame, "Total");
  return out;
}
