#include <iostream>
#include "geom.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

namespace kuznetsov {
  void scaleByPnt(Shape** fs, size_t size, point_t p, double m);
  double getSumArea(const Shape* const* array, size_t size);
  rectangle_t getFrame(const Shape* const* array, size_t size);
  void printFrame(const rectangle_t& r);
  void printShape(const Shape* shape, size_t index);
  void print(const Shape* const* fs, size_t s);
}

int main()
{
  namespace kuz = kuznetsov;
  kuz::Shape* figs[3]{nullptr, nullptr, nullptr};
  size_t size = 3;
  int statusCode = 0;

  double m = 0.0;
  kuz::point_t p {};
  std::cout << "x, y, scale: ";
  std::cin >> p.x >> p.y >> m;
  if (!std::cin || m <= 0) {
    std::cerr << "Incorrect enter\n";
    return 1;
  }

  try {
    figs[0] = new kuz::Rectangle(3.0, 5.0, {10, 3});
    figs[1] = new kuz::Triangle({10, 1}, {12, 5}, {8, 3});
    figs[2] = new kuz::Square(5, {10, 3});
  } catch (const std::bad_alloc& e) {
    std::cerr << e.what() << '\n';
    statusCode = 1;
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << '\n';
    statusCode = 1;
  }

  if (statusCode == 0) {
    std::cout << "Before:\n";
    kuz::print(figs, size);
    try {
      figs[2]->scaleSafe(m);
      kuz::scaleByPnt(figs, size, p, m);
      std::cout << "After:\n";
      kuz::print(figs, size);
    } catch (...) {
      statusCode = 1;
    }
  }

  delete figs[0];
  delete figs[1];
  delete figs[2];
  return statusCode;
}

void kuznetsov::scaleByPnt(Shape** fs, size_t size, point_t p, double m)
{
  if (!size || fs == nullptr) {
    throw std::invalid_argument("Empty array of shapes");
  }
  for (size_t i = 0; i < size; ++i) {
    point_t c = fs[i]->getFrameRect().pos;
    double dx = (c.x - p.x) * (m - 1);
    double dy = (c.y - p.y) * (m - 1);
    fs[i]->move(dx, dy);
    fs[i]->scale(m);
  }
}

double kuznetsov::getSumArea(const Shape* const* array, size_t size)
{
  if (!size || array == nullptr) {
    throw std::invalid_argument("Empty array of shapes");
  }
  double finalArea = 0.0;
  for (size_t i = 0; i < size; ++i) {
    finalArea += array[i]->getArea();
  }
  return finalArea;
}

kuznetsov::rectangle_t kuznetsov::getFrame(const Shape* const* array, size_t size)
{
  if (!size || array == nullptr) {
    throw std::invalid_argument("Empty array of shapes");
  }
  rectangle_t fr = array[0]->getFrameRect();
  double maxY = fr.pos.y + fr.height / 2;
  double minY = fr.pos.y - fr.height / 2;
  double maxX = fr.pos.x + fr.width / 2;
  double minX = fr.pos.x - fr.width / 2;

  for (size_t i = 1; i < size; ++i) {
    const Shape* f = array[i];
    fr = f->getFrameRect();
    maxY = std::max(maxY, fr.pos.y + fr.height / 2);
    maxX = std::max(maxX, fr.pos.x + fr.width / 2);
    minY = std::min(minY, fr.pos.y - fr.height / 2);
    minX = std::min(minX, fr.pos.x - fr.width / 2);
  }

  double cx = (maxX + minX) / 2;
  double cy = (maxY + minY) / 2;
  return {maxX - minX, maxY - minY, {cx, cy}};
}

void kuznetsov::printFrame(const rectangle_t& r)
{
  std::cout << "\t\t" << "Width: " << r.width;
  std::cout << "\n" << "\t\t" << "Height: " << r.height;
  std::cout << "\n" << "\t\t" << "Center: x = " << r.pos.x;
  std::cout << " y = " << r.pos.y << '\n';
}

void kuznetsov::printShape(const Shape* shape, size_t index)
{
  std::cout << "Figure " << index << ":\n";
  std::cout << "\tArea: " << shape->getArea();
  std::cout << "\n\tFrame rectangle:\n";
  printFrame(shape->getFrameRect());
}

void kuznetsov::print(const Shape* const* fs, size_t s)
{
  for (size_t i = 0; i < s; ++i) {
    printShape(fs[i], i);
  }

  std::cout << "SumArea: " << getSumArea(fs, s) << '\n';
  std::cout << "Generic frame:\n";
  printFrame(getFrame(fs, s));
}
