#include <iostream>
#include <cmath>

namespace donkeev
{
  constexpr double PI = 3.14;
  struct point_t
  {
    double x, y;
  };
  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t&) = 0;
    virtual void move(const double, const double) = 0;
    virtual void scale(double) = 0;
  };
  class Rectangle:public Shape
  {
  public:
    Rectangle(const rectangle_t&);
    ~Rectangle() override = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(double) override;
  private:
    rectangle_t body;
  };
  class Polygon:public Shape
  {
  public:
    Polygon(const point_t*, size_t size, const point_t&);
    ~Polygon() override;
    Polygon(const Polygon&);
    Polygon& operator=(const Polygon&);
    Polygon(Polygon&&);
    Polygon& operator=(Polygon&&);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(double) override;
  private:
    point_t* points_;
    size_t size_;
    point_t pos_;
  };
  class Circle:public Shape
  {
  public:
    Circle(double, const point_t&);
    ~Circle() override = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(const double, const double) override;
    void scale(double) override;
  private:
    point_t center_;
    double radius_;
  };
  Rectangle::Rectangle(const rectangle_t& rectangle):
    body(rectangle)
  {
    if (rectangle.height < 0 || rectangle.width < 0)
    {
      throw std::invalid_argument("rectangle's sizes mustn't be less than zero");
    }
  }
  double Rectangle::getArea() const
  {
    return body.height * body.width;
  }
  rectangle_t Rectangle::getFrameRect() const
  {
    return body;
  }
  void Rectangle::move(const point_t& d)
  {
    body.pos = d;
  }
  void Rectangle::move(const double dx, const double dy)
  {
    body.pos.x += dx;
    body.pos.y += dy;
  }
  void Rectangle::scale(double k)
  {
    if (k < 0)
    {
      throw std::invalid_argument("k mustn't be less than zero");
    }
    body.height *= k;
    body.width *= k;
  }
  Polygon::Polygon(const point_t* points, size_t size, const point_t& pos):
    points_(new point_t[size]),
    size_(size),
    pos_(pos)
  {
    if (size_ < 3)
    {
      delete[] points_;
      throw std::logic_error("polygon contains more than 2 points");
    }
    for (size_t i = 0; i < size; ++i)
    {
      points_[i] = points[i];
    }
    delete [] points;
  }
  Polygon::~Polygon()
  {
    delete[] points_;
  }
  Polygon::Polygon(const Polygon& v):
    points_(new point_t[v.size_]),
    size_(v.size_),
    pos_(v.pos_)
  {
    for (size_t i = 0; i < size_; ++i)
    {
      points_[i] = v.points_[i];
    }
  }
  Polygon& Polygon::operator=(const Polygon& v)
  {
    point_t* temp = new point_t [v.size_];
    for (size_t i = 0; i < v.size_; ++i)
    {
      temp[i] = v.points_[i];
    }
    delete[] points_;
    points_ = temp;
    size_ = v.size_;
    pos_ = v.pos_;
    return *this;
  }
  Polygon::Polygon(Polygon&& v):
    points_(v.points_),
    size_(v.size_),
    pos_(v.pos_)
  {
    v.points_ = nullptr;
  }
  Polygon& Polygon::operator=(Polygon&& v)
  {
    if (this == std::addressof(v))
    {
      return *this;
    }
    delete[] points_;
    points_ = v.points_;
    size_ = v.size_;
    pos_ = v.pos_;
    v.points_ = nullptr;
    return *this;
  }
  double Polygon::getArea() const
  {
    double area = 0.0;
    for (size_t i = 0; i < size_; ++i)
    {
      size_t j = (i + 1) % size_;
      area += points_[i].x * points_[j].y;
      area -= points_[j].x * points_[i].y;
    }
    return std::abs(area) / 2.0;
  }
  rectangle_t Polygon::getFrameRect() const
  {
    double minx = points_[0].x;
    double maxx = points_[0].x;
    double miny = points_[0].y;
    double maxy = points_[0].y;
    for (size_t i = 0; i < size_; ++i)
    {
      minx = points_[i].x < minx ? points_[i].x : minx;
      maxx = points_[i].x > maxx ? points_[i].x : maxx;
      miny = points_[i].y < miny ? points_[i].y : miny;
      maxy = points_[i].y > maxy ? points_[i].y : maxy;
    }
    rectangle_t frame;
    frame.height = maxy - miny;
    frame.width = maxx- minx;
    frame.pos = point_t{frame.width * 0.5, frame.height * 0.5};
    return frame;
  }
  void Polygon::move(const point_t& d)
  {
    pos_ = d;
    double dx = d.x - pos_.x;
    double dy = d.y - pos_.y;
    move(dx, dy);
  }
  void Polygon::move(const double dx, const double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
    for (size_t i = 0; i < size_; ++i)
    {
      points_[i].x += dx;
      points_[i].y += dy;
    }
  }
  void Polygon::scale(double k)
  {
    if (k < 0)
    {
      throw std::invalid_argument("k mustn't be less than zero");
    }
    for (size_t i = 0; i < size_; ++i)
    {
      double dx = points_[i].x - pos_.x;
      double dy = points_[i].y - pos_.y;
      points_[i] = {pos_.x + dx * k, pos_.y + dy * k};
    }
  }
  Circle::Circle(double r, const point_t& c):
    center_(c),
    radius_(r)
  {
    if (r < 0)
    {
      throw std::invalid_argument("radius mustn't be less than zero");
    }
  }
  double Circle::getArea() const
  {
    return PI * radius_ * radius_;
  }
  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{radius_ * 2, radius_ * 2, center_};
  }
  void Circle::move(const point_t& d)
  {
    center_ = d;
  }
  void Circle::move(const double dx, const double dy)
  {
    center_.x += dx;
    center_.y += dy;
  }
  void Circle::scale(double k)
  {
    if (k < 0)
    {
      throw std::invalid_argument("k mustn't be less than zero");
    }
    radius_ *= k;
  }
  void isotropicScale(donkeev::Shape&, point_t, double);
}
void donkeev::isotropicScale(Shape& figure, point_t target, double k)
{
  rectangle_t first_rect = figure.getFrameRect();
  point_t first_p = {0, 0};
  first_p.x = first_rect.pos.x + first_rect.width;
  first_p.y = first_rect.pos.y - first_rect.height;
  figure.move(target);
  rectangle_t second_rect= figure.getFrameRect();
  point_t second_p = {0, 0};
  second_p.x = second_rect.pos.x + second_rect.width;
  second_p.y = second_rect.pos.y - second_rect.height;
  double dx = second_p.x - first_p.x;
  double dy = second_p.y - first_p.y;
  figure.scale(k);
  figure.move(dx * k, dy * k);
}
void getCoordinates(double* coordinates, const donkeev::Shape* shape)
{
  double minx = shape->getFrameRect().pos.x - shape->getFrameRect().width / 2;
  double maxx = minx + shape->getFrameRect().width;
  double miny = shape->getFrameRect().pos.y - shape->getFrameRect().height / 2;
  double maxy = miny + shape->getFrameRect().height;
  coordinates[0] = minx;
  coordinates[1] = maxx;
  coordinates[2] = miny;
  coordinates[3] = maxy;
}
void print(std::ostream& output, const donkeev::Shape* const * shape, const char* const* names, const size_t size)
{
  double sumArea = 0;
  double coordinates[4] = {};
  getCoordinates(coordinates, shape[0]);
  double minx = coordinates[0];
  double maxx = coordinates[1];
  double miny = coordinates[2];
  double maxy = coordinates[3];
  for (size_t i = 0; i < size; ++i)
  {
    output << names[i] << '\n';
    output << "Area: " << shape[i]->getArea() << '\n';
    output << "Frame width: " << shape[i]->getFrameRect().width << '\n';
    output << "Frame height: " << shape[i]->getFrameRect().height << '\n';
    output << "Frame position (x): " << shape[i]->getFrameRect().pos.x << '\n';
    output << "Frame position (y): " << shape[i]->getFrameRect().pos.y << '\n';
    sumArea += shape[i]->getArea();
    getCoordinates(coordinates, shape[i]);
    minx = coordinates[0] < minx ? coordinates[0] : minx;
    maxx = coordinates[1] > maxx ? coordinates[1] : maxx;
    miny = coordinates[2] < miny ? coordinates[2] : miny;
    maxy = coordinates[3] > maxy ? coordinates[3] : maxy;
  }
  double width = maxx - minx;
  double height = maxy - miny;
  donkeev::point_t position = {0, 0};
  position.x = maxx - width / 2;
  position.y = maxy - height / 2;
  output << "Total area: " << sumArea << '\n';
  output << "Total frame width: " << width << '\n';
  output << "Total frame height: " << height << '\n';
  output << "Total frame position (x): " << position.x << '\n';
  output << "Frame position (y): " << position.y << '\n';
}
int main()
{
  using namespace donkeev;
  const size_t shapesSize = 3;
  const size_t polygonPointsSize = 4;
  Shape** shapes = new Shape* [shapesSize];
  const char* names[shapesSize] = {"Rectangle", "Polygon", "Circle"};
  shapes[0] = new Rectangle({7, 3, {2, 0}});
  try
  {
    point_t* points = new point_t [polygonPointsSize];
    points[0] = point_t{1.0, 1.0};
    points[1] = point_t{5.0, 1.0};
    points[2] = point_t{4.0, 4.0};
    points[3] = point_t{2.0, 4.0};
    shapes[1] = new Polygon(points, polygonPointsSize, {3.0, 2.5});
  }
  catch (const std::bad_alloc& e)
  {
    delete[] shapes[0];
    delete[] shapes;
    std::cerr << "memory error\n";
    return 1;
  }
  catch (const std::logic_error& e)
  {
    delete[] shapes[0];
    delete[] shapes;
    std::cerr << e.what() << '\n';
    return 1;
  }
  shapes[2] = new Circle(13.5, {4, 7});
  print(std::cout, shapes, names, shapesSize);
  point_t sclaePoint = {0.0, 0.0};
  double k;
  std::cin >> sclaePoint.x >> sclaePoint.y;
  std::cin >> k;
  if (!std::cin || k < 0)
  {
    for (size_t i = 0; i < shapesSize; ++i)
    {
      delete shapes[i];
    }
    delete[] shapes;
    std::cerr << "bad input\n";
    return 1;
  }
  for (size_t i = 0; i < 3; ++i)
  {
    isotropicScale(*(shapes[i]), sclaePoint, k);
  }
  print(std::cout, shapes, names, shapesSize);
  for (size_t i = 0; i < shapesSize; ++i)
  {
    delete shapes[i];
  }
  delete[] shapes;
}
