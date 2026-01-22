#include <iostream>
#include "geometry.hpp"

void goltsov::totalPrint(size_t count, Shape** mas2, std::ostream& outp)
{
  double total_area = 0;
  outp << "Areas:\n";
  for (size_t i = 0; i < count; ++i)
  {
    outp << mas2[i]->getArea() << '\n';
    total_area += mas2[i]->getArea();
  }
  outp << "Total area:\n";
  outp << total_area << '\n' << '\n';

  rectangle_t total_rec = mas2[0]->getFrameRect();
  double left_x = total_rec.pos.x - total_rec.width/2;
  double right_x = total_rec.pos.x + total_rec.width/2;
  double down_y = total_rec.pos.y - total_rec.height/2;
  double up_y = total_rec.pos.y + total_rec.height/2;
  outp << "Frame rectangles:\n";
  for (size_t i = 0; i < count; ++i)
  {
    rectangle_t a = mas2[i]->getFrameRect();
    outp << a.width << ' ' << a.height << ' ' << a.pos.x << " - " << a.pos.y << '\n';

    double left_xi = a.pos.x - a.width/2;
    double right_xi = a.pos.x + a.width/2;
    double down_yi = a.pos.y - a.height/2;
    double up_yi = a.pos.y + a.height/2;
    left_x = left_xi < left_x ? left_xi : left_x;
    right_x = right_xi > right_x ? right_xi : right_x;
    down_y = down_yi < down_y ? down_yi : down_y;
    up_y = up_yi > up_y ? up_yi : up_y;

    total_rec = {right_x - left_x, up_y - down_y, {(left_x + right_x)/2, (up_y + down_y)/2}};
  }
  outp << "Total frame rectangle:\n";
  outp << total_rec.width << ' ' << total_rec.height << ' ' << total_rec.pos.x << " - " << total_rec.pos.y << '\n';
}

int main()
{
  using namespace goltsov;
  Rectangle a = {1, 5, {2, 3}};

  Rubber b = {4.4, {1, 1}, 1.1, {1.1, 1.1}};

  point_t mas[5] = {{0, 0}, {1, 0}, {2, 2}, {2, 3}, {1, 4}};
  Polygon c = {mas, 5};

  size_t count = 3;
  Shape* mas2[count] = {&a, &b, &c};
  point_t point_a;
  double k;

  std::cout << "Before changes:\n";
  totalPrint(count, mas2, std::cout);

  std::cout << "\n\n";

  bool f = 0;

  std::cout << "Enter x, y, k:\n";
  while(std::cin >> point_a.x >> point_a.y >> k)
  {
    if (std::cin.fail() || std::cin.bad())
    {
      std::cerr << "Bad input\n";
      return 1;
    }
    if (k <= 0)
    {
      std::cerr << "The zoom level must be greater than 0\n";
      return 1;
    }

    f = 1;

    std::cout << "For x = " << point_a.x << "; y = " << point_a.y << "; k = " << k << '\n';

    for (size_t i = 0; i < count; ++i)
    {
      scaleRelativePoint(mas2[i], point_a, k);
    }

    totalPrint(count, mas2, std::cout);
    std::cout << "\n\n";
    std::cout << "Enter x, y, k:\n";
  }
  if ((std::cin.fail() || std::cin.bad()) && !std::cin.eof())
  {
    std::cerr << "Bad input\n";
    return 1;
  }
  if (std::cin.eof() && !f)
  {
    std::cerr << "No input\n";
    return 1;
  }
}
