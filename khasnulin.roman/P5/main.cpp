#include <cstring>
#include <iostream>

namespace khasnulin
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

  class IShape
  {
  public:
    virtual ~IShape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t to) = 0;
    virtual void move(double dx, double dy) = 0;
    void scale(double k);

  private:
    const virtual char *getShapeName() const = 0;
    virtual void doScale(double k) = 0;
  };

  class Rectangle: public IShape
  {
  public:
    Rectangle(point_t pos, double w, double h);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

  private:
    const char *getShapeName() const override;
    void doScale(double k) override;
    rectangle_t rect;
  };

  class Polygon: public IShape
  {
  public:
    Polygon(const point_t *points, size_t k);

    Polygon(const Polygon &pol);
    Polygon(Polygon &&pol);
    Polygon &operator=(const Polygon &pol);
    Polygon &operator=(Polygon &&pol);

    ~Polygon();

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

  private:
    const char *getShapeName() const override;
    void doScale(double k) override;
    point_t *vertex;
    size_t size;
    point_t center;
  };

  class Xquare: public IShape
  {
  public:
    Xquare(point_t cent, double d);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t to) override;
    void move(double dx, double dy) override;

  private:
    const char *getShapeName() const override;
    void doScale(double k) override;
    double diag;
    point_t center;
  };

  void printRectInfo(std::ostream &out, rectangle_t rect);
  rectangle_t getCommonRectangleFrame(rectangle_t r1, rectangle_t r2);
  void calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size);
  rectangle_t calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size);

  void isotropicScaling(IShape &shape, point_t scale_pt, double scale);

  point_t getRightTop(rectangle_t frame);

  point_t operator-(point_t p_t1, point_t p_t2);
  point_t operator+(point_t p_t1, point_t p_t2);
  point_t operator*(point_t p_t1, double k);
  point_t operator/(point_t p_t1, double k);

  double triagleSignedArea(point_t v1, point_t v2);
  point_t getTriangleCenter(point_t v1, point_t v2);

  point_t *copy(const point_t *from, point_t *to, size_t k);

  point_t calculateCenter(const point_t *points, size_t k);

}

int main()
{
  using namespace khasnulin;
  IShape *shapes[3];
  size_t size = 0;
  size_t code = 0;
  try
  {
    shapes[size++] = new Rectangle({1, 1}, 5, 3);
    const point_t poly_points[] = {{1, 1}, {3, 2}, {4, 2}, {4, 5}, {1, 5}};
    shapes[size++] = new Polygon(poly_points, 5);
    shapes[size++] = new Xquare({-5, -5}, 10);

    std::cout << "before figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);

    double scale;
    point_t scale_pt;
    std::cout << "before figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);

    std::cin >> scale_pt.x >> scale_pt.y;
    std::cin >> scale;
    if (std::cin.fail())
    {
      throw std::runtime_error("incorrect input: fail to read arguments, must be 3 double");
    }
    if (scale <= 0)
    {
      throw std::runtime_error("incorrect input: scale coefficient must be more than zero");
    }

    for (size_t i = 0; i < size; i++)
    {
      isotropicScaling(*shapes[i], scale_pt, scale);
    }
    std::cout << "\nafter figures scaling: \n";
    calculateAndPrintFiguresInfo(std::cout, shapes, size);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    code = 1;
  }

  for (size_t i = 0; i < size; i++)
  {
    delete shapes[i];
  }
  return code;
}

void khasnulin::IShape::scale(double k)
{
  if (k <= 0.0)
  {
    char message[256] = {};
    strcat(message, getShapeName());
    throw std::invalid_argument(
        std::strcat(message, " incorrect scaling: scale coefficient must be positive"));
  }
  doScale(k);
}

khasnulin::Rectangle::Rectangle(point_t pos, double w, double h):
    rect({w, h, pos})
{
  if (w <= 0.0 || h <= 0.0)
  {
    throw std::invalid_argument("incorrect rectangle creation: width and height must be positive");
  }
}

double khasnulin::Rectangle::getArea() const
{
  return rect.width * rect.height;
}

khasnulin::rectangle_t khasnulin::Rectangle::getFrameRect() const
{
  return rect;
}

void khasnulin::Rectangle::move(double dx, double dy)
{
  rect.pos.x += dx;
  rect.pos.y += dy;
}

void khasnulin::Rectangle::move(point_t to)
{
  rect.pos = to;
}

void khasnulin::printRectInfo(std::ostream &out, rectangle_t rect)
{
  out << "rectangle center x:" << rect.pos.x << ", y: " << rect.pos.y << ", width: " << rect.width
      << ", height: " << rect.height << "\n";
}

khasnulin::rectangle_t khasnulin::getCommonRectangleFrame(rectangle_t r1, rectangle_t r2)
{
  double left = std::min(r1.pos.x - r1.width / 2, r2.pos.x - r2.width / 2);
  double right = std::max(r1.pos.x + r1.width / 2, r2.pos.x + r2.width / 2);
  double bottom = std::min(r1.pos.y - r1.height / 2, r2.pos.y - r2.height / 2);
  double top = std::max(r1.pos.y + r1.height / 2, r2.pos.y + r2.height / 2);
  return rectangle_t{right - left, top - bottom, {(right + left) / 2, (top + bottom) / 2}};
}

void khasnulin::calculateAndPrintFiguresInfo(std::ostream &out, IShape **shapes, size_t size)
{
  double sum_area = 0;
  rectangle_t general_frame = calculateFiguresGeneralRectangleFrame(shapes, size);
  for (size_t i = 0; i < size; i++)
  {
    double area = shapes[i]->getArea();
    out << "figure " << i << " area: " << shapes[i]->getArea() << "\n";
    rectangle_t rect = shapes[i]->getFrameRect();
    out << "figure " << i << " frame ";
    printRectInfo(out, rect);

    sum_area += area;
  }
  out << "area sum: " << sum_area << "\n";
  out << "general figures frame ";
  printRectInfo(out, general_frame);
}

khasnulin::rectangle_t khasnulin::calculateFiguresGeneralRectangleFrame(IShape **shapes, size_t size)
{
  if (!size)
  {
    throw std::runtime_error("figures general frame: empty shapes array error");
  }
  rectangle_t general_frame = shapes[0]->getFrameRect();
  for (size_t i = 1; i < size; i++)
  {
    general_frame = getCommonRectangleFrame(general_frame, shapes[i]->getFrameRect());
  }
  return general_frame;
}

khasnulin::point_t khasnulin::operator-(point_t p_t1, point_t p_t2)
{
  return {p_t1.x - p_t2.x, p_t1.y - p_t2.y};
}

khasnulin::point_t khasnulin::operator+(point_t p_t1, point_t p_t2)
{
  return {p_t1.x + p_t2.x, p_t1.y + p_t2.y};
}

khasnulin::point_t khasnulin::operator*(point_t p_t1, double k)
{
  return {p_t1.x * k, p_t1.y * k};
}

khasnulin::point_t khasnulin::operator/(point_t p_t1, double k)
{
  return {p_t1.x / k, p_t1.y / k};
}

void khasnulin::isotropicScaling(IShape &shape, point_t scale_pt, double scale)
{
  rectangle_t base_frame = shape.getFrameRect();
  point_t old_right_top = getRightTop(base_frame);

  shape.move(scale_pt);

  rectangle_t new_frame = shape.getFrameRect();
  point_t new_right_top = getRightTop(new_frame);

  shape.scale(scale);

  point_t delta = (old_right_top - new_right_top) * scale;

  shape.move(delta.x, delta.y);
}

khasnulin::point_t khasnulin::getRightTop(rectangle_t frame)
{
  return frame.pos + point_t{frame.width / 2, frame.height / 2};
}

khasnulin::Polygon::Polygon(const point_t *points, size_t k):
    vertex(k > 2 ? new point_t[k] : nullptr),
    size(k)
{
  if (!points || k <= 2)
  {
    throw std::invalid_argument(
        "polygon creation error: points array must be not empty, count of vertexes must be more than 2");
  }
  copy(points, vertex, k);
  center = calculateCenter(vertex, size);
}

khasnulin::point_t *khasnulin::copy(const point_t *from, point_t *to, size_t k)
{
  for (size_t i = 0; i < k; i++)
  {
    to[i] = from[i];
  }
  return to + k;
}

khasnulin::Polygon::~Polygon()
{
  delete[] vertex;
}

double khasnulin::triagleSignedArea(point_t v1, point_t v2)
{
  return (v1.x * v2.y - v2.x * v1.y) / 2;
}

double khasnulin::Polygon::getArea() const
{
  double figure_area = 0;
  for (size_t i = 0; i < size - 1; i++)
  {
    figure_area += triagleSignedArea(vertex[i], vertex[i + 1]);
  }
  figure_area += triagleSignedArea(vertex[size - 1], vertex[0]);
  return std::abs(figure_area);
}

khasnulin::point_t khasnulin::getTriangleCenter(point_t v1, point_t v2)
{
  return (v1 + v2) / 3;
}

khasnulin::point_t khasnulin::calculateCenter(const point_t *points, size_t k)
{
  double figure_area = triagleSignedArea(points[0], points[1]);
  point_t figure_center = getTriangleCenter(points[0], points[1]) * figure_area;
  for (size_t i = 1; i < k - 1; i++)
  {
    double current_area = triagleSignedArea(points[i], points[i + 1]);
    point_t current_center = getTriangleCenter(points[i], points[i + 1]);
    figure_center = figure_center + current_center * current_area;
    figure_area += current_area;
  }
  double last_area = triagleSignedArea(points[k - 1], points[0]);
  figure_center = figure_center + getTriangleCenter(points[k - 1], points[0]) * last_area;
  figure_area += last_area;
  return figure_area ? (figure_center / figure_area) : point_t{0, 0};
}

void khasnulin::Polygon::move(point_t to)
{
  point_t delta = to - center;
  for (size_t i = 0; i < size; i++)
  {
    vertex[i] = vertex[i] + delta;
  }
  center = to;
}

void khasnulin::Polygon::move(double dx, double dy)
{
  point_t newCenter = center + point_t{dx, dy};
  move(newCenter);
}

khasnulin::rectangle_t khasnulin::Polygon::getFrameRect() const
{
  double left = vertex[0].x, right = vertex[0].x;
  double top = vertex[0].y, bottom = vertex[0].y;
  for (size_t i = 1; i < size; i++)
  {
    left = std::min(left, vertex[i].x);
    top = std::max(top, vertex[i].y);
    right = std::max(right, vertex[i].x);
    bottom = std::min(bottom, vertex[i].y);
  }
  return rectangle_t{right - left, top - bottom, point_t{(right + left) / 2, (top + bottom) / 2}};
}

khasnulin::Polygon::Polygon(const Polygon &pol):
    vertex(new point_t[pol.size]),
    size(pol.size),
    center(pol.center)
{
  copy(pol.vertex, vertex, size);
}
khasnulin::Polygon::Polygon(Polygon &&pol):
    vertex(pol.vertex),
    size(pol.size),
    center(pol.center)
{
  pol.vertex = nullptr;
}
khasnulin::Polygon &khasnulin::Polygon::operator=(const Polygon &pol)
{
  if (this == std::addressof(pol))
  {
    return *this;
  }
  point_t *newV = new point_t[pol.size];
  copy(pol.vertex, newV, pol.size);
  delete[] vertex;
  vertex = newV;
  size = pol.size;
  center = pol.center;
  return *this;
}

khasnulin::Polygon &khasnulin::Polygon::operator=(Polygon &&pol)
{
  if (this == std::addressof(pol))
  {
    return *this;
  }
  std::swap(vertex, pol.vertex);
  std::swap(size, pol.size);
  center = pol.center;
  return *this;
}

khasnulin::Xquare::Xquare(point_t cent, double d):
    diag(d),
    center(cent)
{
  if (d <= 0)
  {
    throw std::invalid_argument("fail Xquare creation: diagonal must be positive number");
  }
}

double khasnulin::Xquare::getArea() const
{
  return diag * diag / 2;
}
khasnulin::rectangle_t khasnulin::Xquare::getFrameRect() const
{
  return {diag, diag, center};
}
void khasnulin::Xquare::move(point_t to)
{
  center = to;
}
void khasnulin::Xquare::move(double dx, double dy)
{
  center.x += dx;
  center.y += dy;
}

const char *khasnulin::Rectangle::getShapeName() const
{
  return "rectangle";
}

void khasnulin::Rectangle::doScale(double k)
{
  rect.width *= k;
  rect.height *= k;
}

const char *khasnulin::Polygon::getShapeName() const
{
  return "polygon";
}

void khasnulin::Polygon::doScale(double k)
{
  for (size_t i = 0; i < size; i++)
  {
    point_t delta = vertex[i] - center;
    vertex[i] = center + delta * k;
  }
}

const char *khasnulin::Xquare::getShapeName() const
{
  return "xquare";
}

void khasnulin::Xquare::doScale(double k)
{
  diag *= k;
}
