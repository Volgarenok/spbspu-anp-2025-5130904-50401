#include <iostream>

namespace tarasenko
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

  point_t getRectLeftBot(rectangle_t);
  point_t getRectRightTop(rectangle_t);
  rectangle_t makeRect(point_t, point_t);
  void expandRect(point_t &, point_t &, rectangle_t);
  void printRect(rectangle_t);

  class Shape
  {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual rectangle_t getFrameRect() const = 0;
      virtual void move(point_t dest) = 0;
      virtual void move(double dx, double dy) = 0;
      void scale(double coeff);
    private:
      virtual void scaling(double coeff) = 0;
  };

  class Rectangle final: public Shape
  {
    public:
      Rectangle(rectangle_t rect);
      Rectangle(point_t left_bot, point_t right_top);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(point_t dest) override;
      void move(double dx, double dy) override;
    private:
      void scaling(double coeff) override;
      double width, height;
      point_t center;
  };

  class Square final: public Shape
  {
    public:
      Square(rectangle_t rect);
      Square(point_t left_bot, double len);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(point_t dest) override;
      void move(double dx, double dy) override;
    private:
      void scaling(double coeff) override;
      double size;
      point_t center;
  };

  class Polygon final: public Shape
  {
    public:
      ~Polygon() override;
      Polygon(const point_t* points, size_t len);
      Polygon(const Polygon & poly);
      Polygon &operator=(const Polygon & poly);
      Polygon(Polygon && poly);
      Polygon &operator=(Polygon && poly);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(point_t dest) override;
      void move(double dx, double dy) override;
    private:
      void scaling(double coeff) override;
      point_t getPolygonCenter(const point_t*, size_t) const;
      double getSignedPolygonArea(const point_t*, size_t) const;
      size_t length;
      point_t* vertices;
      point_t center;
  };

  void scaleIsotropic(Shape**, size_t, point_t, double);
  void printFigures(Shape**, size_t);
}

int main()
{
  using namespace tarasenko;
  size_t n = 6;
  int exit_code = 0;
  Shape** figures = nullptr;
  try
  {
    figures = new Shape*[n];
    for (size_t i = 0; i < n; ++i)
    {
      figures[i] = nullptr;
    }
    figures[0] = new Rectangle({6, 7, {11, 2}});
    figures[1] = new Rectangle({1, 2}, {4, 7});
    figures[2] = new Square({5, 2, {0, 0}});
    figures[3] = new Square({2, -1}, 10);
    point_t verts1[4] = {{0, 0}, {0, 5}, {7, 5}, {7, 0}};
    figures[4] = new Polygon(verts1, 4);
    point_t verts2[7] = {{-2, 2}, {-1, 5}, {2, 8}, {5, 7}, {6, 4}, {4, 1}, {0, 0}};
    figures[5] = new Polygon(verts2, 7);
    printFigures(figures, n);
    point_t point = {0, 0};
    double coefficient = 0;
    std::cout << "point: ";
    if (!(std::cin >> point.x >> point.y))
    {
      exit_code = 1;
      throw std::runtime_error("two floating point numbers expected");
    };
    std::cout << "coefficient: ";
    if (!(std::cin >> coefficient))
    {
      exit_code = 1;
      throw std::runtime_error("floating point number expected");
    }
    scaleIsotropic(figures, n, point, coefficient);
    printFigures(figures, n);
    for (size_t i = 0; i < n; ++i)
    {
      delete figures[i];
    }
    delete[] figures;
    return exit_code;
  }
  catch (const std::exception &e)
  {
    exit_code = 1;
    for (size_t i = 0; i < n; ++i)
    {
      delete figures[i];
    }
    delete[] figures;
    std::cerr << e.what() << "\n";
    return exit_code;
  }
}

void tarasenko::Shape::scale(double coeff)
{
  if (coeff < 0.0)
  {
    throw std::invalid_argument("scale coefficient must be positive");
  }
  scaling(coeff);
}

tarasenko::Rectangle::Rectangle(rectangle_t rect):
  width(rect.width),
  height(rect.height),
  center(rect.pos)
{}

tarasenko::Rectangle::Rectangle(point_t left_bot, point_t right_top):
  width(right_top.x - left_bot.x),
  height(right_top.y - left_bot.y),
  center({(right_top.x + left_bot.x) / 2, (right_top.y + left_bot.y) / 2})
{}

double tarasenko::Rectangle::getArea() const
{
  return width * height;
}

tarasenko::rectangle_t tarasenko::Rectangle::getFrameRect() const
{
  return {width, height, {center.x, center.y}};
}

void tarasenko::Rectangle::move(point_t dest)
{
  center = dest;
}

void tarasenko::Rectangle::move(double dx, double dy)
{
  center.x += dx;
  center.y += dy;
}

void tarasenko::Rectangle::scaling(double coeff)
{
  width *= coeff;
  height *= coeff;
}

tarasenko::point_t tarasenko::getRectLeftBot(rectangle_t rect)
{
  return {rect.pos.x - (rect.width / 2), rect.pos.y - (rect.height / 2)};
}

tarasenko::point_t tarasenko::getRectRightTop(rectangle_t rect)
{
  return {rect.pos.x + (rect.width / 2), rect.pos.y + (rect.height / 2)};
}

void tarasenko::expandRect(point_t & left_bot, point_t & right_top, rectangle_t current)
{
  left_bot.x = getRectLeftBot(current).x < left_bot.x ? getRectLeftBot(current).x : left_bot.x;
  left_bot.y = getRectLeftBot(current).y < left_bot.y ? getRectLeftBot(current).y : left_bot.y;
  right_top.x = getRectRightTop(current).x > right_top.x ? getRectRightTop(current).x : right_top.x;
  right_top.y = getRectRightTop(current).y > right_top.y ? getRectRightTop(current).y : right_top.y;
}

void tarasenko::printRect(rectangle_t rect)
{
  std::cout << "  width: " << rect.width << "; height: " << rect.height << '\n';
  std::cout << "  center: " << rect.pos.x << ' ' << rect.pos.y << '\n';
}

tarasenko::Square::Square(rectangle_t rect):
  size(rect.height > rect.width ? rect.width : rect.height),
  center(rect.pos)
{}

tarasenko::Square::Square(point_t left_bot, double len):
  size(len),
  center({left_bot.x + (len / 2), left_bot.y + (len / 2)})
{}

double tarasenko::Square::getArea() const
{
  return size * size;
}

tarasenko::rectangle_t tarasenko::Square::getFrameRect() const
{
  return {size, size, {center.x, center.y}};
}

void tarasenko::Square::move(point_t dest)
{
  center = dest;
}

void tarasenko::Square::move(double dx, double dy)
{
  center.x += dx;
  center.y += dy;
}

void tarasenko::Square::scaling(double coeff)
{
  size *= coeff;
}

tarasenko::Polygon::~Polygon()
{
  delete[] vertices;
}

tarasenko::Polygon::Polygon(const point_t* points, size_t len):
  length(len)
{
  if (len < 3)
  {
    throw std::runtime_error("invalid poligon");
  }
  vertices = new point_t[len];
  for (size_t i = 0; i < len; ++i)
  {
    vertices[i] = points[i];
  }
  center = getPolygonCenter(vertices, len);
}

tarasenko::Polygon::Polygon(const Polygon & poly):
  length(poly.length),
  vertices(new point_t[poly.length]),
  center(poly.center)
{
  for (size_t i = 0; i < length; ++i)
  {
    vertices[i] = poly.vertices[i];
  }
}

tarasenko::Polygon & tarasenko::Polygon::operator=(const Polygon & poly)
{
  if (this == & poly)
  {
    return *this;
  }
  point_t * newVerts = new point_t[poly.length];
  for (size_t i = 0; i < poly.length; ++i)
  {
    newVerts[i] = poly.vertices[i];
  }
  delete[] vertices;
  vertices = newVerts;
  length = poly.length;
  center = poly.center;
  return *this;
}

tarasenko::Polygon::Polygon(Polygon && poly):
  length(poly.length),
  vertices(poly.vertices),
  center(poly.center)
{
  poly.vertices = nullptr;
}

tarasenko::Polygon & tarasenko::Polygon::operator=(Polygon && poly)
{
  if (this == & poly)
  {
    return *this;
  }
  delete[] vertices;
  vertices = poly.vertices;
  length = poly.length;
  center = poly.center;
  poly.vertices = nullptr;
  return *this;
}

double tarasenko::Polygon::getArea() const
{
  double area = getSignedPolygonArea(vertices, length);
  return area > 0 ? area : -area;
}

tarasenko::rectangle_t tarasenko::Polygon::getFrameRect() const
{
  double max_x = vertices[0].x;
  double min_x = vertices[0].x;
  double max_y = vertices[0].y;
  double min_y = vertices[0].y;
  for (size_t i = 1; i < length; ++i)
  {
    max_x = vertices[i].x > max_x ? vertices[i].x : max_x;
    min_x = vertices[i].x < min_x ? vertices[i].x : min_x;
    max_y = vertices[i].y > max_y ? vertices[i].y : max_y;
    min_y = vertices[i].y < min_y ? vertices[i].y : min_y;
  }
  return makeRect({min_x, min_y}, {max_x, max_y});
}

void tarasenko::Polygon::move(point_t dest)
{
  double dx = dest.x - center.x;
  double dy = dest.y - center.y;
  move(dx, dy);
}

void tarasenko::Polygon::move(double dx, double dy)
{
  center.x += dx;
  center.y += dy;
  for (size_t i = 0; i < length; ++i)
  {
    vertices[i].x += dx;
    vertices[i].y += dy;
  }
}

void tarasenko::Polygon::scaling(double coeff)
{
  for (size_t i = 0; i < length; ++i)
  {
    vertices[i].x = center.x - coeff * (center.x - vertices[i].x);
    vertices[i].y = center.y - coeff * (center.y - vertices[i].y);
  }
}

tarasenko::point_t tarasenko::Polygon::getPolygonCenter(const point_t* vert, size_t len) const
{
  double x = 0;
  double y = 0;
  for (size_t i = 0; i < (len - 1); ++i)
  {
    double triangle_area = ((vert[i].x * vert[i + 1].y - vert[i + 1].x * vert[i].y) / 2);
    x += ((vert[i].x + vert[i + 1].x) * triangle_area);
    y += ((vert[i].y + vert[i + 1].y) * triangle_area);
  }
  double triangle_area = ((vert[len - 1].x * vert[0].y - vert[0].x * vert[len - 1].y) / 2);
  x += ((vert[len - 1].x + vert[0].x) * triangle_area);
  y += ((vert[len - 1].y + vert[0].y) * triangle_area);
  double area = getSignedPolygonArea(vert, len);
  x /= (area * 3);
  y /= (area * 3);
  return {x, y};
}

double tarasenko::Polygon::getSignedPolygonArea(const point_t* vert, size_t len) const
{
  double area = 0;
  for (size_t i = 0; i < (len - 1); ++i)
  {
    area += (vert[i].x * vert[i + 1].y - vert[i + 1].x * vert[i].y);
  }
  area += (vert[len - 1].x * vert[0].y - vert[0].x * vert[len - 1].y);
  area /= 2;
  return area;
}

tarasenko::rectangle_t tarasenko::makeRect(point_t left_bot, point_t right_top)
{
  point_t center = {(right_top.x + left_bot.x) / 2, (right_top.y + left_bot.y) / 2};
  return {right_top.x - left_bot.x, right_top.y - left_bot.y, center};
}

void tarasenko::scaleIsotropic(Shape** figures, size_t len, point_t point, double coeff)
{
  for (size_t i = 0; i < len; ++i)
  {
    point_t left_bot_initial = getRectLeftBot(figures[i]->getFrameRect());
    figures[i]->move(point);
    point_t left_bot_moved = getRectLeftBot(figures[i]->getFrameRect());
    figures[i]->scale(coeff);
    double dx = (left_bot_moved.x - left_bot_initial.x) * coeff;
    double dy = (left_bot_moved.y - left_bot_initial.y) * coeff;
    figures[i]->move(dx, dy);
  }
}

void tarasenko::printFigures(Shape** figures, size_t len)
{
  double total_area = 0;
  for (size_t i = 0; i < len; ++i)
  {
    double current = figures[i]->getArea();
    std::cout << "area " << i << ": " << current << '\n';
    total_area += current;
  }
  std::cout << "total area: " << total_area << '\n';
  point_t left_bot = getRectLeftBot(figures[0]->getFrameRect());
  point_t right_top = getRectRightTop(figures[0]->getFrameRect());
  for (size_t i = 0; i < len; ++i)
  {
    rectangle_t current = figures[i]->getFrameRect();
    std::cout << "frame rectangle " << i << ":\n";
    printRect(current);
    expandRect(left_bot, right_top, current);
  }
  rectangle_t total_rect = makeRect(left_bot, right_top);
  std::cout << "total frame rectangle:\n";
  printRect(total_rect);
}
