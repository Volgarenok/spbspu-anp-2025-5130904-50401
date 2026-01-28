#include <iostream>
#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace vasyakin
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };

  struct Shape
  {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
    virtual void scaleUnchecked(double k) = 0;
    virtual ~Shape() = default;
  };

  struct Rectangle: Shape
  {
    Rectangle(double width, double height, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    void scaleUnchecked(double k) override;
  private:
    double width_, height_;
    point_t pos_;
  };

  struct Triangle: Shape
  {
    Triangle(const point_t& a, const point_t& b, const point_t& c);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    void scaleUnchecked(double k) override;
    point_t getCenter() const;
  private:
    point_t a_, b_, c_;
  };

  struct Concave: Shape
  {
    Concave(const point_t& a, const point_t& b, const point_t& c, const point_t& d);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    void scaleUnchecked(double k) override;
    point_t getCenter() const;
  private:
    point_t a_, b_, c_, d_;
    double triangleArea(const point_t& p1, const point_t& p2, const point_t& p3) const;
  };
  void scaleByPnt(Shape** figures, size_t size, const point_t& k, double a);
  double getSumArea(const Shape* const* arr, size_t k);
  rectangle_t getAllFrame(const Shape* const* arr, size_t k);
  void printFrame(const rectangle_t& r);
  void printShape(const Shape* arr, size_t i);
  void print(const Shape* const* figures, size_t k);
}

void vasyakin::scaleByPnt(Shape** figures, size_t size, const point_t& k, double a)
{
  if (!size || figures == nullptr)
  {
    throw std::invalid_argument("Empty size or array");
  }
  if (a <= 0)
  {
    throw std::invalid_argument("scale coefficient must be positive");
  }
  for (size_t i = 0; i < size; ++i)
  {
    const point_t g = figures[i]->getFrameRect().pos;
    const double dx = (k.x - g.x) * (a - 1);
    const double dy = (k.y - g.y) * (a - 1);
    figures[i]->move(dx, dy);
    figures[i]->scaleUnchecked(a);
  }
}

double vasyakin::getSumArea(const Shape* const* arr, size_t k)
{
  if (!k || arr == nullptr)
  {
    throw std::invalid_argument("Invalid size or array");
  }
  double final_area = 0.0;
  for (size_t i = 0; i < k; ++i)
  {
    final_area += arr[i]->getArea();
  }
  return final_area;
}

vasyakin::rectangle_t vasyakin::getAllFrame(const Shape* const* arr, size_t k)
{
  if (!k || arr == nullptr)
  {
    throw std::invalid_argument("Invalid size or array");
  }
  if (arr[0] == nullptr)
  {
    throw std::invalid_argument("First element is nullptr");
  }
  rectangle_t fr = arr[0]->getFrameRect();
  double min_x = fr.pos.x - fr.width / 2;
  double max_x = fr.pos.x + fr.width / 2;
  double min_y = fr.pos.y - fr.height / 2;
  double max_y = fr.pos.y + fr.height / 2;
  for (size_t i = 1; i < k; ++i)
  {
    if (arr[i] == nullptr)
    {
      throw std::invalid_argument("Array contains nullptr");
    }
    fr = arr[i]->getFrameRect();
    min_x = std::min(min_x, fr.pos.x - fr.width / 2);
    max_x = std::max(max_x, fr.pos.x + fr.width / 2);
    min_y = std::min(min_y, fr.pos.y - fr.height / 2);
    max_y = std::max(max_y, fr.pos.y + fr.height / 2);
  }
  rectangle_t allFrame{
    max_x - min_x,
    max_y - min_y,
    {(min_x + max_x) / 2, (min_y + max_y) / 2}
  };
  return allFrame;
}

void vasyakin::printFrame(const rectangle_t& r)
{
  std::cout << "\t\t" << "Width: " << r.width << "\n";
  std::cout << "\t\t" << "Height: " << r.height << "\n";
  std::cout << "\t\t" << "Center: x = " << r.pos.x;
  std::cout << " y = " << r.pos.y << '\n';
}

void vasyakin::printShape(const Shape* shape, size_t i)
{
  std::cout << "Figure " << i + 1 << ":\n";
  std::cout << "\tArea: " << shape->getArea();
  std::cout << "\n\tFrame rectangle:\n";
  printFrame(shape->getFrameRect());
}

void vasyakin::print(const Shape* const* figures, size_t k)
{
  if (figures == nullptr)
  {
    throw std::invalid_argument("Invalid arr");
  }
  for (size_t i = 0; i < k; ++i)
  {
    printShape(figures[i], i);
  }
  std::cout << "SumArea: " << getSumArea(figures, k) << '\n';
  std::cout << "Generic frame:\n";
  printFrame(getAllFrame(figures, k));
}

vasyakin::Rectangle::Rectangle(const double width, const double height, const point_t& pos):
  Shape(),
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("Invalid size");
  }
}

double vasyakin::Rectangle::getArea() const
{
  return width_ * height_;
}

vasyakin::rectangle_t vasyakin::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void vasyakin::Rectangle::move(const point_t& p)
{
  pos_ = p;
}

void vasyakin::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void vasyakin::Rectangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("incorrect coefficient");
  }
  scaleUnchecked(k);
}

void vasyakin::Rectangle::scaleUnchecked(double k)
{
  width_ *= k;
  height_ *= k;
}

vasyakin::Triangle::Triangle(const point_t& a, const point_t& b, const point_t& c):
  Shape(),
  a_(a),
  b_(b),
  c_(c)
{}

vasyakin::point_t vasyakin::Triangle::getCenter() const
{
  return {(a_.x + b_.x + c_.x) / 3.0, (a_.y + b_.y + c_.y) / 3.0};
}

double vasyakin::Triangle::getArea() const
{
  return 0.5 * std::abs((b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y));
}

vasyakin::rectangle_t vasyakin::Triangle::getFrameRect() const
{
  double min_x = std::min({a_.x, b_.x, c_.x});
  double max_x = std::max({a_.x, b_.x, c_.x});
  double min_y = std::min({a_.y, b_.y, c_.y});
  double max_y = std::max({a_.y, b_.y, c_.y});
  return {max_x - min_x, max_y - min_y, {(min_x + max_x) / 2.0, (min_y + max_y) / 2.0}};
}

void vasyakin::Triangle::move(const point_t& p)
{
  point_t center = getCenter();
  double dx = p.x - center.x;
  double dy = p.y - center.y;
  move(dx, dy);
}

void vasyakin::Triangle::move(double dx, double dy)
{
  a_.x += dx;
  a_.y += dy;
  b_.x += dx;
  b_.y += dy;
  c_.x += dx;
  c_.y += dy;
}

void vasyakin::Triangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("incorrect coefficient");
  }
  scaleUnchecked(k);
}

void vasyakin::Triangle::scaleUnchecked(double k)
{
  point_t center = getCenter();
  a_.x = center.x + (a_.x - center.x) * k;
  a_.y = center.y + (a_.y - center.y) * k;
  b_.x = center.x + (b_.x - center.x) * k;
  b_.y = center.y + (b_.y - center.y) * k;
  c_.x = center.x + (c_.x - center.x) * k;
  c_.y = center.y + (c_.y - center.y) * k;
}

vasyakin::point_t vasyakin::Concave::getCenter() const
{
  return d_;
}

vasyakin::Concave::Concave(const point_t& a, const point_t& b, const point_t& c, const point_t& d):
  Shape(),
  a_(a),
  b_(b),
  c_(c),
  d_(d)
{}

double vasyakin::Concave::getArea() const
{
  double area1 = triangleArea(a_, b_, d_);
  double area2 = triangleArea(b_, c_, d_);
  return area1 + area2;
}

vasyakin::rectangle_t vasyakin::Concave::getFrameRect() const
{
  double min_x = std::min({a_.x, b_.x, c_.x, d_.x});
  double max_x = std::max({a_.x, b_.x, c_.x, d_.x});
  double min_y = std::min({a_.y, b_.y, c_.y, d_.y});
  double max_y = std::max({a_.y, b_.y, c_.y, d_.y});
  return {max_x - min_x, max_y - min_y, {(min_x + max_x) / 2.0, (min_y + max_y) / 2.0}};
}

void vasyakin::Concave::move(const point_t& p)
{
  double dx = p.x - d_.x;
  double dy = p.y - d_.y;
  move(dx, dy);
}

void vasyakin::Concave::move(double dx, double dy)
{
  a_.x += dx;
  a_.y += dy;
  b_.x += dx;
  b_.y += dy;
  c_.x += dx;
  c_.y += dy;
  d_.x += dx;
  d_.y += dy;
}

void vasyakin::Concave::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("incorrect coefficient");
  }
  scaleUnchecked(k);
}

void vasyakin::Concave::scaleUnchecked(double k)
{
  point_t center = getCenter();
  a_.x = center.x + (a_.x - center.x) * k;
  a_.y = center.y + (a_.y - center.y) * k;
  b_.x = center.x + (b_.x - center.x) * k;
  b_.y = center.y + (b_.y - center.y) * k;
  c_.x = center.x + (c_.x - center.x) * k;
  c_.y = center.y + (c_.y - center.y) * k;
}

double vasyakin::Concave::triangleArea(const point_t& p1, const point_t& p2, const point_t& p3) const
{
  return 0.5 * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
}

int main()
{
  vasyakin::Shape** figures = new vasyakin::Shape*[3]{nullptr, nullptr, nullptr};
  size_t k = 3;
  double l = 0.0;
  vasyakin::point_t a = {0.0, 0.0};
  std::cout << "x, y, scale: ";
  std::cin >> a.x >> a.y >> l;
  if (!std::cin || l <= 0.0)
  {
    std::cerr << "Bad input\n";
    delete[] figures;
    return 1;
  }
  try
  {
    figures[0] = new vasyakin::Rectangle{3.0, 6.0, {6.0, 4.0}};
    figures[1] = new vasyakin::Triangle{{10, 3}, {12, 4}, {8, 9}};
    figures[2] = new vasyakin::Concave{{11, 9}, {4, 7}, {10, 4}, {6, 5}};
    vasyakin::print(figures, k);
    vasyakin::scaleByPnt(figures, k, a, l);
    vasyakin::print(figures, k);
    for (size_t i = 0; i < k; ++i)
    {
      delete figures[i];
    }
    delete[] figures;
    return 0;
  }
  catch(const std::bad_alloc& e)
  {
    std::cerr << e.what() << '\n';
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << e.what() << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  for (size_t i = 0; i < k; ++i)
  {
    delete figures[i];
  }
  delete[] figures;
  return 1;
}
