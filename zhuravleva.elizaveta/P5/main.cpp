#include <iostream>
namespace zhuravleva
{
  const double pi = 3.14;

  struct point_t {
    double x, y;
  };

  struct rectangle_t {
    double width, height;
    point_t pos;
  };

  class Shape {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t point) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
  };

  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double heihg, point_t point);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t point) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;
  private:
    double width_, height_;
    point_t center_;
  };

  class Ellipse : public Shape
  {
  public:
    Ellipse(double radHor, double radVer, point_t p);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;
  private:
    double radiusHor_, radiusVer_;
    point_t center_;
  };

  class Rubber : public Shape
  {
  public:
    Rubber(double outerRadius, double innerRadius, const point_t& center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double coefficient) override;
  private:
    double outerRadius_;
    double innerRadius_;
    point_t center_;
  };
};

zhuravleva::Rectangle::Rectangle(double width, double heigh, point_t point):
  Shape(),
  width_(width),
  height_(heigh),
  center_(point)
{
  if (width <= 0 || heigh <= 0)
  {
    throw std::invalid_argument("Invalid size");
  }
}
double zhuravleva::Rectangle::getArea() const
{
  return width_ * height_;
}
zhuravleva::rectangle_t zhuravleva::Rectangle::getFrameRect() const
{
  rectangle_t frameRect;
  frameRect.width = width_;
  frameRect.height = height_;
  frameRect.pos = center_;
  return frameRect;
}
void zhuravleva::Rectangle::move(point_t point)
{
  center_ = point;
}
void zhuravleva::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
void zhuravleva::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Scale coefficient must be positive");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

zhuravleva::Ellipse::Ellipse(double radHor, double radVer, point_t p):
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
double zhuravleva::Ellipse::getArea() const
{
  return pi * radiusHor_ * radiusVer_;
}
zhuravleva::rectangle_t zhuravleva::Ellipse::getFrameRect() const
{
  rectangle_t frameRect;
  frameRect.width = radiusHor_ * 2;
  frameRect.height = radiusVer_ * 2;
  frameRect.pos = center_;
  return frameRect;
}
void zhuravleva::Ellipse::move(point_t p)
{
  center_ = p;
}
void zhuravleva::Ellipse::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
void zhuravleva::Ellipse::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Scale coefficient must be positive");
  }
  radiusHor_ *= coefficient;
  radiusVer_ *= coefficient;
}

zhuravleva::Rubber::Rubber(double outerRadius, double innerRadius, const point_t& center):
  Shape(),
  outerRadius_(outerRadius),
  innerRadius_(innerRadius),
  center_(center)
{
  if (outerRadius <= 0 || innerRadius <= 0)
  {
    throw std::invalid_argument("Radii must be positive");
  }
  if (innerRadius >= outerRadius)
  {
    throw std::invalid_argument("Inner radius must be less than outer radius");
  }
}
double zhuravleva::Rubber::getArea() const
{
  return pi * (outerRadius_ * outerRadius_ - innerRadius_ * innerRadius_);
}
zhuravleva::rectangle_t zhuravleva::Rubber::getFrameRect() const
{
  rectangle_t frameRect;
  frameRect.width = outerRadius_ * 2;
  frameRect.height = outerRadius_ * 2;
  frameRect.pos = center_;
  return frameRect;
}
void zhuravleva::Rubber::move(point_t p)
{
  center_ = p;
}
void zhuravleva::Rubber::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
void zhuravleva::Rubber::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Scale coefficient must be positive");
  }
  outerRadius_ *= coefficient;
  innerRadius_ *= coefficient;
}


void scaleByPoint(zhuravleva::Shape** shapes, size_t count,
  const zhuravleva::point_t& point, double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Scale coefficient must be positive");
  }

  for (size_t i = 0; i < count; ++i)
  {
    shapes[i]->move(-point.x, -point.y);

    shapes[i]->scale(coef);

    shapes[i]->move(point.x, point.y);
  }
}

zhuravleva::rectangle_t getAllFrame(zhuravleva::Shape** shapes, size_t count)
{
  if (count == 0)
  {
    return { 0, 0, {0, 0} };
  }
  zhuravleva::rectangle_t first = shapes[0]->getFrameRect();
  double minX = first.pos.x - first.width / 2;
  double minY = first.pos.y - first.height / 2;
  double maxX = first.pos.x + first.width / 2;
  double maxY = first.pos.y + first.height / 2;
  for (size_t i = 1; i < count; ++i)
  {
    zhuravleva::rectangle_t curFr = shapes[i]->getFrameRect();
    double curMinX = curFr.pos.x - curFr.width / 2;
    double curMinY = curFr.pos.y - curFr.height / 2;
    double curMaxX = curFr.pos.x + curFr.width / 2;
    double curMaxY = curFr.pos.y + curFr.height / 2;
    if (curMinX < minX)
    {
      minX = curMinX;
    }
    if (curMinY < minY)
    {
      minY = curMinY;
    }
    if (curMaxX > maxX)
    {
      maxX = curMaxX;
    }
    if (curMaxY > maxY)
    {
      maxY = curMaxY;
    }
  }
  zhuravleva::rectangle_t resultFrame;
  resultFrame.width = maxX - minX;
  resultFrame.height = maxY - minY;
  resultFrame.pos.x = minX + resultFrame.width / 2;
  resultFrame.pos.y = minY + resultFrame.height / 2;
  return resultFrame;
}

double allArea(zhuravleva::Shape** shapes, size_t count)
{
  if (count == 0)
  {
    return 0.0;
  }

  double totalArea = 0.0;
  for (size_t i = 0; i < count; ++i)
  {
    totalArea += shapes[i]->getArea();
  }
  return totalArea;
}

void output(zhuravleva::Shape** figures, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    zhuravleva::rectangle_t frame = figures[i]->getFrameRect();
    std::cout << "Figure " << i << ":\n";
    std::cout << "\tArea: " << figures[i]->getArea() << "\n";
    std::cout << "\tFrame rectangle:\n";
    std::cout << "\t\tWidth: " << frame.width << "\n";
    std::cout << "\t\tHeight: " << frame.height << "\n";
    std::cout << "\t\tCenter: x = " << frame.pos.x << " y = " << frame.pos.y << "\n";
  }
  std::cout << "SumArea: " << allArea(figures, size) << "\n";
  zhuravleva::rectangle_t allFrame = getAllFrame(figures, size);
  std::cout << "Generic frame:\n";
  std::cout << "\tWidth: " << allFrame.width << "\n";
  std::cout << "\tHeight: " << allFrame.height << "\n";
  std::cout << "\tCenter: x = " << allFrame.pos.x << " y = " << allFrame.pos.y << "\n";
}

int main()
{
  zhuravleva::Shape* figures[3] = { nullptr, nullptr, nullptr };
  size_t size = 3;
  double k = 0.0;
  zhuravleva::point_t p = { 0.0, 0.0 };

  std::cout << "x, y, scale: ";
  std::cin >> p.x >> p.y >> k;
  if (!std::cin || k <= 0.0)
  {
    std::cerr << "Bad input\n";
    return 1;
  }

  try
  {
    figures[0] = new zhuravleva::Rectangle(4.0, 3.0, { 2.0, 2.0 });
    figures[1] = new zhuravleva::Ellipse(4.0, 2.0, { 8.0, 8.0 });
    figures[2] = new zhuravleva::Rubber(5.0, 2.0, { 15.0, 5.0 });

    output(figures, size);
    scaleByPoint(figures, size, p, k);
    output(figures, size);

    delete figures[0];
    delete figures[1];
    delete figures[2];

    return 0;
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << e.what() << "\n";
    delete figures[0];
    delete figures[1];
    delete figures[2];

    return 2;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    delete figures[0];
    delete figures[1];
    delete figures[2];
    return 3;
  }
}
