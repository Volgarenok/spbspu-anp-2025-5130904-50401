#include <iostream>
#include <cstddef>

namespace sedov
{
  const double PI = 3.14;

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
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
  };

  struct Rectangle: Shape
  {
    Rectangle(double w, double h, point_t p);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  private:
    double width_, height_;
    point_t center_;
  };

  struct Polygon: Shape
  {
    ~Polygon();
    Polygon(point_t * ps, size_t s);
    Polygon(const Polygon & poly);
    Polygon & operator=(const Polygon & poly);
    Polygon(Polygon && poly);
    Polygon & operator=(Polygon && poly);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  private:
    point_t center_;
    point_t * ps_;
    size_t size_;
  };

  struct Ellipse: Shape
  {
    Ellipse(double radHor, double radVer, point_t p);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  private:
    double radiusHor_, radiusVer_;
    point_t center_;
  };

  point_t getCenterOfPolygon(const point_t * ps, size_t s);
  void scaleByPoint(Shape ** fs, size_t s, point_t p, double k);
  double getAllArea(Shape ** p, size_t s);
  rectangle_t getAllFrameRect(Shape ** p, size_t s);
  void output(Shape ** fs, size_t s);
}

int main()
{
  sedov::Shape * figures[3] = {nullptr, nullptr, nullptr};
  size_t size = 3;
  double k = 0.0;
  sedov::point_t p = {0.0, 0.0};

  std::cout << "x, y, scale: ";
  std::cin >> p.x >> p.y >> k;
  if (!std::cin || k <= 0.0)
  {
    std::cerr << "Bad input\n";
    return 1;
  }

  sedov::point_t * points = new sedov::point_t[4] {{0.0, 0.0}, {4.0, 0.0}, {4.0, 6.0}, {0.0, 3.0}};
  try
  {
    figures[0] = new sedov::Rectangle(2.0, 8.0, {10.0, 0.0});
    figures[1] = new sedov::Polygon(points, 4);
    figures[2] = new sedov::Ellipse(3.0, 2.0, {-2.0, 0.0});
    sedov::output(figures, size);
    sedov::scaleByPoint(figures, size, p, k);
    sedov::output(figures, size);
    delete figures[0];
    delete figures[1];
    delete figures[2];
    delete[] points;
    return 0;
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << e.what() << "\n";
    delete figures[0];
    delete figures[1];
    delete figures[2];
    delete[] points;
    return 2;
  }
  catch (const std::invalid_argument & e)
  {
    std::cerr << e.what() << "\n";
    delete figures[0];
    delete figures[1];
    delete figures[2];
    delete[] points;
    return 3;
  }
}

sedov::Rectangle::Rectangle(double w, double h, point_t p):
  Shape(),
  width_(w),
  height_(h),
  center_(p)
{
  if (w <= 0 || h <= 0)
  {
    throw std::invalid_argument("Invalid size");
  }
}

double sedov::Rectangle::getArea() const
{
  return width_ * height_;
}

sedov::rectangle_t sedov::Rectangle::getFrameRect() const
{
  rectangle_t frameRect;
  frameRect.width = width_;
  frameRect.height = height_;
  frameRect.pos = center_;
  return frameRect;
}

void sedov::Rectangle::move(point_t p)
{
  center_ = p;
}

void sedov::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void sedov::Rectangle::scale(double k)
{
  width_ *= k;
  height_ *= k;
}

sedov::Polygon::Polygon(point_t * ps, size_t s):
  Shape(),
  center_(getCenterOfPolygon(ps, s)),
  ps_(new point_t[s]),
  size_(s)
{
  if (s < 3)
  {
    delete[] ps_;
    throw std::invalid_argument("Not enough args for polygon");
  }
  for (size_t i = 0; i < s; ++i)
  {
    ps_[i] = ps[i];
  }
}

sedov::Polygon::~Polygon()
{
  delete[] ps_;
}

sedov::Polygon::Polygon(const Polygon & poly):
  Shape(),
  center_(poly.center_),
  ps_(new point_t[poly.size_]),
  size_(poly.size_)
{
  for (size_t i = 0; i < size_; ++i)
  {
    ps_[i] = poly.ps_[i];
  }
}

sedov::Polygon & sedov::Polygon::operator=(const Polygon & poly)
{
  if (this != & poly)
  {
    delete[] ps_;
  }
  center_ = poly.center_;
  size_ = poly.size_;
  ps_ = new point_t[size_];
  for (size_t i = 0; i < size_; ++i)
  {
    ps_[i] = poly.ps_[i];
  }
  return * this;
}

sedov::Polygon::Polygon(Polygon && poly):
  Shape(),
  center_(poly.center_),
  ps_(poly.ps_),
  size_(poly.size_)
{
  poly.ps_ = nullptr;
}

sedov::Polygon & sedov::Polygon::operator=(Polygon && poly)
{
  if (this != & poly)
  {
    delete[] ps_;
  }
  center_ = poly.center_;
  size_ = poly.size_;
  ps_ = poly.ps_;
  poly.ps_ = nullptr;
  return * this;
}

double sedov::Polygon::getArea() const
{
  double area = 0.0;
  for (size_t i = 0; i < size_; ++i)
  {
    size_t j = (i + 1) % size_;
    area += ps_[i].x * ps_[j].y - ps_[j].x * ps_[i].y;
  }
  area *= 0.5;
  return std::abs(area);
}

sedov::rectangle_t sedov::Polygon::getFrameRect() const
{
  rectangle_t frameRect;
  double minX = ps_[0].x;
  double maxX = ps_[0].x;
  double minY = ps_[0].y;
  double maxY = ps_[0].y;
  for (size_t i = 1; i < size_; ++i)
  {
    minX = std::min(minX, ps_[i].x);
    maxX = std::max(maxX, ps_[i].x);
    minY = std::min(minY, ps_[i].y);
    maxY = std::max(maxY, ps_[i].y);
  }
  frameRect.width = maxX - minX;
  frameRect.height = maxY - minY;
  frameRect.pos = {(minX + maxX) / 2, (minY + maxY) / 2};
  return frameRect;
}

void sedov::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i)
  {
    ps_[i].x += dx;
    ps_[i].y += dy;
  }
  center_.x += dx;
  center_.y += dy;
}

void sedov::Polygon::move(point_t p)
{
  move(p.x - center_.x, p.y - center_.y);
}

void sedov::Polygon::scale(double k)
{
  for (size_t i = 0; i < size_; ++i)
  {
    ps_[i].x = center_.x + (ps_[i].x - center_.x) * k;
    ps_[i].y = center_.y + (ps_[i].y - center_.y) * k;
  }
}

sedov::point_t sedov::getCenterOfPolygon(const point_t * ps, size_t s)
{
  point_t c = {0.0, 0.0};
  double area = 0.0, t = 0.0;
  for (size_t i = 0; i < s; ++i)
  {
    size_t j = (i + 1) % s;
    t = ps[i].x * ps[j].y - ps[j].x * ps[i].y;
    area += t;
    c.x += (ps[i].x + ps[j].x) * t;
    c.y += (ps[i].y + ps[j].y) * t;
  }
  area *= 0.5;
  c.x /= 6.0 * std::abs(area);
  c.y /= 6.0 * std::abs(area);
  return c;
}

sedov::Ellipse::Ellipse(double radHor, double radVer, point_t p):
  Shape(),
  radiusHor_(radHor),
  radiusVer_(radVer),
  center_(p)
{
  if (radHor <= 0.0 || radVer <= 0.0)
  {
    throw std::invalid_argument("Invalid radius");
  }
}

double sedov::Ellipse::getArea() const
{
  return PI * radiusHor_ * radiusVer_;
}

sedov::rectangle_t sedov::Ellipse::getFrameRect() const
{
  rectangle_t frameRect;
  frameRect.width = radiusHor_ * 2;
  frameRect.height = radiusVer_ * 2;
  frameRect.pos = center_;
  return frameRect;
}

void sedov::Ellipse::move(point_t p)
{
  center_ = p;
}

void sedov::Ellipse::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void sedov::Ellipse::scale(double k)
{
  radiusHor_ *= k;
  radiusVer_ *= k;
}

void sedov::scaleByPoint(Shape ** fs, size_t s, point_t p, double k)
{
  if (!s || fs == nullptr)
  {
    throw std::invalid_argument("Empty array of figures");
  }
  for (size_t i = 0; i < s; ++i)
  {
    point_t a = fs[i]->getFrameRect().pos;
    double dx = (a.x - p.x) * (k - 1);
    double dy = (a.y - p.y) * (k - 1);
    fs[i]->move(dx, dy);
    fs[i]->scale(k);
  }
}

double sedov::getAllArea(Shape ** p, size_t s)
{
  if (!s || p == nullptr)
  {
    throw std::invalid_argument("Empty array of figures");
  }
  double area = 0.0;
  for (size_t i = 0; i < s; ++i)
  {
    area += p[i]->getArea();
  }
  return area;
}

sedov::rectangle_t sedov::getAllFrameRect(Shape ** p, size_t s)
{
  if (!s || p == nullptr)
  {
    throw std::invalid_argument("Empty array of figures");
  }
  rectangle_t allFrameRect;
  rectangle_t f = p[0]->getFrameRect();
  double minX = f.pos.x - f.width / 2;
  double maxX = f.pos.x + f.width / 2;
  double minY = f.pos.y - f.height / 2;
  double maxY = f.pos.y + f.height / 2;
  for (size_t i = 1; i < s; ++i)
  {
    f = p[i]->getFrameRect();
    minX = std::min(minX, f.pos.x - f.width / 2);
    maxX = std::max(maxX, f.pos.x + f.width / 2);
    minY = std::min(minY, f.pos.y - f.height / 2);
    maxY = std::max(maxY, f.pos.y + f.height / 2);
  }
  allFrameRect.width = maxX - minX;
  allFrameRect.height = maxY - minY;
  allFrameRect.pos = {(minX + maxX) / 2, (minY + maxY) / 2};
  return allFrameRect;
}

void sedov::output(Shape ** fs, size_t s)
{
  for (size_t i = 0; i < s; ++i) {
    rectangle_t a = fs[i]->getFrameRect();
    std::cout << "Figure " << i << ":\n";
    std::cout << "\tArea: " << fs[i]->getArea() << "\n";
    std::cout << "\tFrame rectangle:\n";
    std::cout << "\t\tWidth: " << a.width << "\n";
    std::cout << "\t\tHeight: " << a.height << "\n";
    std::cout << "\t\tCenter: x = " << a.pos.x << " y = " << a.pos.y << "\n";
  }
  std::cout << "SumArea: " << getAllArea(fs, s) << "\n";
  rectangle_t b = getAllFrameRect(fs, s);
  std::cout << "Generic frame:\n";
  std::cout << "\tWidth: " << b.width << "\n";
  std::cout << "\tHeight: " << b.height << "\n";
  std::cout << "\tCenter: x = " << b.pos.x << " y = " << b.pos.y << "\n";
}
