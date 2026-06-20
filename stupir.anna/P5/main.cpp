#include <iostream>
#include <cmath>
namespace stupir
{
  struct point_t;
  struct rectangle_t;
  struct Shape;
  struct Rectangle;
  struct Square;
  struct Xquare;
  std::ostream & operator<<(std::ostream &, const rectangle_t &);
  void scalePoint(point_t, double, Shape &);
  rectangle_t getFrameAll(rectangle_t *, size_t);
  void printFig(double *, rectangle_t *, double &, const size_t);
  void calcParamFig(Shape **, double *, rectangle_t *, double &, const size_t);
}

struct stupir::point_t
{
  double x;
  double y;
};

struct stupir::rectangle_t
{
  double width;
  double height;
  point_t pos;
};

struct stupir::Shape
{
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t) = 0;
  virtual void move(double, double) = 0;
  virtual void scale(double) = 0;
};

struct stupir::Rectangle: Shape
{
  Rectangle(point_t center, double weight, double hight);
  Rectangle(point_t leftDown, point_t rightUp);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t) override;
  void move(double x, double y) override;
  void scale(double k) override;
  private:
    point_t c_;
    double w_;
    double h_;
};

void stupir::Rectangle::scale(double k)
{
  h_ *= k, w_ *= k;
}

void stupir::Rectangle::move(double x, double y)
  {
    c_.x += x;
    c_.y += y;
  }

void stupir::Rectangle::move(point_t p)
{
  c_ = p;
}

stupir::Rectangle::Rectangle(point_t center, double weight, double hight):
  Shape(),
  c_(center),
  w_(weight),
  h_(hight)
  {
    if (w_ <= 0 || h_ <= 0)
    {
      throw std::logic_error("Not  correct size for Rectangle");
    }
  }

double stupir::Rectangle::getArea() const
{
  return w_ * h_;
}

stupir::rectangle_t stupir::Rectangle::getFrameRect() const
{
  return {w_, h_, c_};
}

stupir::Rectangle::Rectangle(point_t leftDown, point_t rightUp):
  c_({(rightUp.x + leftDown.x) / 2, (rightUp.y + leftDown.y) / 2}),
  w_(rightUp.x - leftDown.x),
  h_(rightUp.y - leftDown.y)
  {
    if (leftDown.x >= rightUp.x || leftDown.y >= rightUp.y)
    {
      throw std::logic_error("Not correct points for Rectangle");
    }
  }

struct stupir::Square: Shape
{
  Square(point_t, double);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t) override;
  void move(double, double) override;
  void scale(double) override;
  private:
    point_t cent_;
    double size_;
};

stupir::Square::Square(point_t cent, double size):
  cent_(cent),
  size_(size)
  {}

double stupir::Square::getArea() const
{
  return size_ * size_;
}

stupir::rectangle_t stupir::Square::getFrameRect() const
{
  return {size_, size_, cent_};
}

void stupir::Square::move(point_t p)
{
  cent_ = p;
}

void stupir::Square::move(double x, double y)
{
  cent_.x += x;
  cent_.y += y;
}

void stupir::Square::scale(double k)
{
  size_ *= k;
}

struct stupir::Xquare: Shape
{
  Xquare(point_t pDown, double size);
  Xquare(point_t leftPoint, point_t rightPoint);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t) override;
  void move(double x, double y) override;
  void scale(double k) override;
  double side() const;
  private:
    point_t center_;
    double dig_;
};

void stupir::Xquare::scale(double k)
{
  dig_ *= k;
}

void stupir::Xquare::move(point_t p)
{
  center_ = p;
}

void stupir::Xquare::move(double x, double y)
{
  center_.x += x;
  center_.y += y;
}

double stupir::Xquare::side() const
{
  return std::sqrt((dig_ / 2) * (dig_ / 2) * 2);
}

stupir::Xquare::Xquare(point_t center, double len):
  Shape(),
  center_(center),
  dig_(std::sqrt(len * len * 2))
  {
    if (len <= 0)
    {
      throw std::logic_error("Not correct size for Xquare");
    }
  }

stupir::Xquare::Xquare(point_t leftPoint, point_t rightPoint):
  center_({(leftPoint.x + rightPoint.x) / 2, (leftPoint.y + rightPoint.y) / 2}),
  dig_(rightPoint.x - leftPoint.x)
  {
    if (leftPoint.x >= rightPoint.x || leftPoint.y != rightPoint.y)
    {
      throw std::logic_error("Not correct point for diagonal Xquare");
    }
  }

double stupir::Xquare::getArea() const
{
  return side() * side();
}

stupir::rectangle_t stupir::Xquare::getFrameRect() const
{
  return {dig_, dig_, center_};
}

void stupir::scalePoint(point_t p, double k, Shape & f)
{
  point_t t = f.getFrameRect().pos;
  point_t change = {p.x - t.x, p.y - t.y};
  f.move(p);
  f.scale(k);
  f.move(-change.x * 2, -change.y * 2);
}

std::ostream & stupir::operator<<(std::ostream & out, const rectangle_t & rec)
{
  out << "hight = " << rec.height << ", weight = " << rec.width << ", pos = {" ;
  out << rec.pos.x << ", " << rec.pos.y << "}\n";
  return out;
}

stupir::rectangle_t stupir::getFrameAll(rectangle_t * arr, size_t len)
{
  double maxX = arr[0].pos.x + arr[0].width / 2;
  double minX = arr[0].pos.x - arr[0].width / 2;
  double maxY = arr[0].pos.y + arr[0].height / 2;
  double minY = arr[0].pos.y - arr[0].height / 2;

  for (size_t i = 1; i < len; ++i)
  {
    double xMax = arr[i].pos.x + arr[i].width / 2;
    double xMin = arr[i].pos.x - arr[i].width / 2;
    double yMax = arr[i].pos.y + arr[i].height / 2;
    double yMin = arr[i].pos.y - arr[i].height / 2;
    maxX = (xMax > maxX) ? xMax : maxX;
    minX = (xMin < minX) ? xMin : minX;
    maxY = (yMax > maxY) ? yMax : maxY;
    minY = (yMin < minY) ? yMin : minY;
  }
  point_t newPos = {(maxX + minX) / 2, (maxY + minY) / 2};
  return {maxX - minX, maxY - minY, newPos};
}

void stupir::calcParamFig(Shape ** f, double * arrAreaFigure, rectangle_t * arrRecFigure,
  double & sumArea, const size_t numFigure)
{
  for (size_t i = 0; i < numFigure; ++i)
    {
      double area = f[i]->getArea();
      sumArea += area;
      arrAreaFigure[i] = area;
      arrRecFigure[i] = f[i]->getFrameRect();
    }
}

void stupir::printFig(double * arrAreaFigure, rectangle_t * arrRecFigure,
  double & sumArea, const size_t numFigure)
{
    for (size_t i = 0; i < numFigure; ++i)
    {
      std::cout << "Area figure" << i + 1 << " = " << arrAreaFigure[i] << '\n';
      std::cout << "The bounding rectangle of figure" << i + 1 << " - " << arrRecFigure[i];
    }
    std::cout << "Summa areas all figure = " << sumArea << '\n';
    std::cout << "The bounding rectangle of all figure - ";
    std::cout << getFrameAll(arrRecFigure, numFigure) << '\n';
}



int main()
{
  namespace stu = stupir;
  int err = 0;
  stu::Shape ** f = nullptr;
  stu::rectangle_t * arrRecFigure = nullptr;
  double * arrAreaFigure = nullptr;
  const size_t numFigure = 5;
  try
  {
    stu::point_t p = {3.2, 4.5};
    f = new stu::Shape * [numFigure]();
    f[0] = new stu::Rectangle({0, 0}, 2, 3);
    f[1] = new stu::Square(p, 3);
    f[2] = new stu::Xquare({-1, 4}, 3);
    f[3] = new stu::Rectangle({2, 3}, p);
    f[4] = new stu::Xquare({1, 2}, {16, 2});
    arrAreaFigure = new double[numFigure];
    arrRecFigure = new stu::rectangle_t[numFigure];
    double sumArea = 0;
    stu::calcParamFig(f, arrAreaFigure, arrRecFigure, sumArea, numFigure);
    stu::printFig(arrAreaFigure, arrRecFigure, sumArea, numFigure);

    double k = 0;
    stu::point_t scalePoint{0, 0};
    std::cin >> scalePoint.x >> scalePoint.y >> k;
    if (std::cin.fail())
    {
      throw std::logic_error("\nNot correct data for scale");
    }
    else if (k <= 0)
    {
      throw std::logic_error("\nNot correct coefficient for scale(negative or null)");
    }

    f[2]->move({2, -6});
    f[0]->scale(4.5);
    f[1]->move(2.3, 3.7);
    stu::scalePoint(scalePoint, k, *f[3]);
    stu::scalePoint(scalePoint, k, *f[1]);
    stu::scalePoint(scalePoint, k, *f[4]);

    sumArea = 0;
    std::cout << "\nAfter scale\n";
    stu::calcParamFig(f, arrAreaFigure, arrRecFigure, sumArea, numFigure);
    stu::printFig(arrAreaFigure, arrRecFigure, sumArea, numFigure);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << '\n';
    err = 1;
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Could not allocete memory\n";
    err = 1;
    if (!f)
    {
      return err;
    }
  }
  delete [] arrAreaFigure;
  delete [] arrRecFigure;
  for (size_t i = 0; i < numFigure; ++i)
  {
    delete f[i];
  }
  delete [] f;
  return err;
}
