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

  const size_t size = 3;
  zub::Shape* shapes[size] = {};

  zub::point_t polyA[3] = {{0, 0}, {4, 0}, {2, 4}};
  try {
    shapes[0] = new zub::Polygon(3, polyA);
  } catch (...) {
    std::cerr << "Memory allocation" << '\n';
    return 1;
  }

  shapes[1] = new zub::Rectangle(2, 2, {-7, -7});
  shapes[2] = new zub::Ring(3, 1, {5, -10});

  std::cout << "--- BEFORE SCALING ---" << '\n';
  zub::printInfo(shapes, size);

  zub::scaleAtCertainPnt(shapes, size, scaleCenter, k);

  std::cout << "--- AFTER SCALING (k=" << k << " relative to " << scaleCenter.x << ", " << scaleCenter.y << ") ---" << '\n';

  zub::printInfo(shapes, size);

  for (size_t i = 0; i < size; i++) {
    delete shapes[i];
  }
}
