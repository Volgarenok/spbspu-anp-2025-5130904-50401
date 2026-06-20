#include "libs.hpp"
int main()
{
  namespace mal = malashenko;
  double k = 0.0;

  mal::point_t scalePoint= {0.0, 0.0};
  std::cout << "ENTER SCALE POINT (CORD X AND Y) AND SCALE COEFFICIENT : ";

  if (!(std::cin >> scalePoint.x >> scalePoint.y >> k)){
    std::cerr << "INPUT PROBLEMS\n";
    return 1;
  } else if (k < 0) {
    std::cerr << "SCALE COEFFICIENT MUST BE POSITIVE\n";
    return 1;
  }

  mal::Shape * figures[3] = {nullptr, nullptr, nullptr};
  mal::point_t triangleTops[3] = {{0, 0}, {3, 3}, {0, 3}};
  mal::point_t * tops = nullptr;

  try {
    figures[0] = new mal::Rectangle(4, 6, {10, 10});
    figures[1] = new mal::Triangle(triangleTops);
    tops = new mal::point_t[3]{{0, 0}, {3, 3}, {1, 2}};
    figures[2] = new mal::Polygon(tops, 3);
  } catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  mal::showInfo(figures, 3);
  mal::scaleByPoint(figures, 3, {10, 10}, 2);
  mal::showInfo(figures, 3);

  delete figures[0];
  delete figures[1];
  delete figures[2];
  delete[] tops;
}
