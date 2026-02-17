#include "shape_comp.hpp"
#include <all.hpp>
#include <iostream>

int main()
{
  namespace zub = zubarev;

  zub::point_t scaleCenter = {};
  double k = 0;
  std::cout << "Input coordinate: ";
  std::cin >> scaleCenter.x >> scaleCenter.y;
  if (std::cin.fail()) {
    std::cerr << "Wrong input" << '\n';
    return 1;
  }

  std::cout << "Input coefficient: ";
  std::cin >> k;
  if (k < 0 || std::cin.fail()) {
    std::cerr << "Wrong input" << '\n';
    return 1;
  }

  zub::ShapeComp shapes = zub::ShapeComp();

  try {
    shapes.append(new zub::Rectangle(2, 2, {-7, -7}));
    shapes.append(new zub::Ring(3, 1, {5, -10}));

    zub::point_t polyA[3] = {{0, 0}, {4, 0}, {2, 4}};
    shapes.preappend(new zub::Polygon(3, polyA));

    std::cout << "--- BEFORE SCALING ---" << '\n';
    zub::printInfo(shapes.shapes(), shapes.size());

    zub::scaleAtCertainPnt(shapes.shapes(), shapes.size(), scaleCenter, k);

    std::cout << "--- AFTER SCALING (k=" << k << " relative to " << scaleCenter.x << ", " << scaleCenter.y << ") ---" << '\n';

    zub::printInfo(shapes.shapes(), shapes.size());

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
