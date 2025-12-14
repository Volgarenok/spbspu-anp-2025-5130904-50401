#include <iostream>
#include <stdexcept>
#include <cmath>

namespace hvostov {
  struct point_t {
    double x, y;
  };
  struct rectangle_t {
    double width, height;
    point_t center;
  };
  class Shape {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual rectangle_t getFrameRect() const = 0;
      virtual void move(point_t center) = 0;
      virtual void move(double x, double y) = 0;
      virtual void scale(double k) = 0;
  };
  class Rectangle: public Shape {
    public:
      Rectangle(double width, double height, point_t center);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(point_t center) override;
      void move(double x, double y) override;
      void scale(double k) override;
    private:
      double width_, height_;
      point_t center_;
  };
  class Polygon: public Shape {
    public:
      Polygon(point_t * vertices, size_t vertex_count);
      Polygon(const Polygon & polygon);
      Polygon(Polygon && polygon);
      ~Polygon() override;
      Polygon & operator=(const Polygon & polygon);
      Polygon & operator=(Polygon && polygon);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(point_t center) override;
      void move(double x, double y) override;
      void scale(double k) override;
    private:
      point_t * vertices_;
      point_t center_;
      size_t vertex_count_;
  };
  class Complexquad: public Shape {
    public:
      Complexquad(point_t * vertices);
      Complexquad(const Complexquad & complexquad);
      Complexquad(Complexquad && complexquad);
      ~Complexquad() override;
      Complexquad & operator=(const Complexquad & complexquad);
      Complexquad & operator=(Complexquad && complexquad);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(point_t center) override;
      void move(double x, double y) override;
      void scale(double k) override;
    private:
      const size_t VERTEX_COUNT_ = 4;
      point_t * vertices_;
      point_t center_;
  };

  double getAreaByVertices(const point_t * vertices, size_t vertex_count);
  point_t getCenter(const point_t * vertices, size_t vertex_count);
  rectangle_t getFrameRectWithVertices(const point_t * vertices, size_t vertex_count);
  void scaleFromPoint(Shape & shape, double k, const point_t & point);
  rectangle_t getFrameRectOfAllShapes(const Shape * const * shapes, size_t shape_count);
  std::ostream & printInformationAboutShape(std::ostream & out, const Shape *  shape, size_t number);
  std::ostream & printInformationAboutShapes(std::ostream & out, const Shape * const * shapes, size_t shape_count);
  double getAreaOfAllShapes(const Shape * const * shapes, size_t shape_count);
  void deleteShapes(Shape ** shapes, size_t shape_count);
}

int main()
{
  std::ostream & out = std::cout;
  size_t shapes_count = 3;
  hvostov::Shape * shapes[shapes_count] = {};
  hvostov::point_t * polygon_vertices = nullptr;
  hvostov::point_t * complexquad_vertices = nullptr;
  try {
    polygon_vertices = new hvostov::point_t[5] {{0.8, 5.7}, {3.2, 8.3}, {7.7, 1.9}, {0.3, 4.4}, {7.0, 4.3}};
    complexquad_vertices = new hvostov::point_t[4] {{0.1, 0.2}, {2.3, 3.4}, {0.1, 2.7}, {2.0, 0.9}};
    shapes[0] = new hvostov::Rectangle(3.3, 4.6, {5.7, 5.8});
    shapes[1] = new hvostov::Complexquad(complexquad_vertices);
    shapes[2] = new hvostov::Polygon(polygon_vertices, 5);
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    return 2;
  } catch (const std::invalid_argument & e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  double k = 0.0;
  hvostov::point_t scale_point;
  std::cin >> scale_point.x >> scale_point.y;
  std::cin >> k;
  if (!std::cin) {
    std::cerr << "Invalid input!\n";
    return 1;
  } else if (k < 0) {
    std::cerr << "Scale needs to be positive!\n";
    return 1;
  }
  hvostov::printInformationAboutShapes(out, shapes, shapes_count);
  for (size_t i = 0; i < shapes_count; i++) {
    hvostov::scaleFromPoint(*(shapes[i]), k, scale_point);
  }
  hvostov::printInformationAboutShapes(out, shapes, shapes_count);
  delete[] polygon_vertices;
  delete[] complexquad_vertices;
  hvostov::deleteShapes(shapes, shapes_count);
}

hvostov::Rectangle::Rectangle(double width, double height, point_t center):
  Shape(),
  width_(width),
  height_(height),
  center_(center)
{}

double hvostov::Rectangle::getArea() const
{
  return width_ * height_;
}

hvostov::rectangle_t hvostov::Rectangle::getFrameRect() const
{
  rectangle_t frame;
  frame.height = height_;
  frame.width = width_;
  frame.center = center_;
  return frame;
}

void hvostov::Rectangle::move(point_t center)
{
  center_ = center;
}

void hvostov::Rectangle::move(double x, double y)
{
  center_.x += x;
  center_.y += y;
}

void hvostov::Rectangle::scale(double k)
{
  width_ *= k;
  height_ *= k;
}

hvostov::Polygon::Polygon(point_t * vertices, size_t vertex_count):
  Shape(),
  vertices_(new point_t[vertex_count]),
  vertex_count_(vertex_count),
  center_(getCenter(vertices, vertex_count))
{
  if (vertex_count_ < 3) {
    delete[] vertices_;
    throw std::invalid_argument("A polygon needs at least 3 vertices");
  }
  for (size_t i = 0; i < vertex_count_; i++) {
    vertices_[i] = vertices[i];
  }
}

hvostov::Polygon::Polygon(const Polygon & polygon):
  Shape(),
  vertices_(new point_t[polygon.vertex_count_]),
  vertex_count_(polygon.vertex_count_),
  center_(polygon.center_)
{
  for (size_t i = 0; i < vertex_count_; i++) {
    vertices_[i] = polygon.vertices_[i];
  }
}

hvostov::Polygon::Polygon(Polygon && polygon):
  Shape(),
  vertices_(polygon.vertices_),
  vertex_count_(polygon.vertex_count_),
  center_(polygon.center_)
{
  polygon.vertices_ = nullptr;
}

hvostov::Polygon::~Polygon()
{
  delete[] vertices_;
}

hvostov::Polygon & hvostov::Polygon::operator=(const Polygon & polygon)
{
  if (this == &polygon) {
    return *this;
  }
  delete[] vertices_;
  vertex_count_ = polygon.vertex_count_;
  center_ = polygon.center_;
  vertices_ = new point_t[vertex_count_];
  for (size_t i = 0; i < vertex_count_; i++) {
    vertices_[i] = polygon.vertices_[i];
  }
  return *this;
}

hvostov::Polygon & hvostov::Polygon::operator=(Polygon && polygon)
{
  delete[] vertices_;
  vertex_count_ = polygon.vertex_count_;
  center_ = polygon.center_;
  vertices_ = polygon.vertices_;
  polygon.vertices_ = nullptr;
  return *this;
}

double hvostov::Polygon::getArea() const
{
  double s = getAreaByVertices(vertices_, vertex_count_);
  return s;
}

hvostov::rectangle_t hvostov::Polygon::getFrameRect() const
{
  return getFrameRectWithVertices(vertices_, vertex_count_);
}

void hvostov::Polygon::move(double x, double y)
{
  center_.x += x;
  center_.y += y;
  for (size_t i = 0; i < vertex_count_; i++) {
    vertices_[i].x += x;
    vertices_[i].y += y;
  }
}

void hvostov::Polygon::move(point_t center)
{
  double x = center.x - center_.x;
  double y = center.y - center_.y;
  move(x, y);
}

void hvostov::Polygon::scale(double k)
{
  if (k <= 0) {
    throw std::invalid_argument("Scale must be positive");
  }
  for (size_t i = 0; i < vertex_count_; i++) {
    vertices_[i].x = center_.x + k * (vertices_[i].x - center_.x);
    vertices_[i].y = center_.y + k * (vertices_[i].y - center_.y);
  }
}

hvostov::Complexquad::Complexquad(point_t * vertices):
  Shape(),
  vertices_(new point_t[VERTEX_COUNT_]),
  center_(getCenter(vertices, VERTEX_COUNT_))
{
  for (size_t i = 0; i < VERTEX_COUNT_; i++) {
    vertices_[i] = vertices[i];
  }
}

hvostov::Complexquad::Complexquad(const Complexquad & complexquad):
  Shape(),
  vertices_(new point_t[VERTEX_COUNT_]),
  center_(complexquad.center_)
{
  for (size_t i = 0; i < VERTEX_COUNT_; i++) {
    vertices_[i] = complexquad.vertices_[i];
  }
}

hvostov::Complexquad::Complexquad(Complexquad && complexquad):
  Shape(),
  vertices_(complexquad.vertices_),
  center_(complexquad.center_)
{
  complexquad.vertices_ = nullptr;
}

hvostov::Complexquad::~Complexquad()
{
  delete[] vertices_;
}

hvostov::Complexquad & hvostov::Complexquad::operator=(const Complexquad & complexquad)
{
  if (this == &complexquad) {
    return *this;
  }
  delete[] vertices_;
  center_ = complexquad.center_;
  for (size_t i = 0; i < VERTEX_COUNT_; i++) {
    vertices_[i] = complexquad.vertices_[i];
  }
  return *this;
}

hvostov::Complexquad & hvostov::Complexquad::operator=(Complexquad && complexquad)
{
  delete[] vertices_;
  center_ = complexquad.center_;
  vertices_ = complexquad.vertices_;
  complexquad.vertices_ = nullptr;
  return *this;
}

double hvostov::Complexquad::getArea() const
{
  double s = getAreaByVertices(vertices_, VERTEX_COUNT_);
  return s;
}

hvostov::rectangle_t hvostov::Complexquad::getFrameRect() const
{
  return getFrameRectWithVertices(vertices_, VERTEX_COUNT_);
}

void hvostov::Complexquad::move(double x, double y)
{
  center_.x += x;
  center_.y += y;
  for (size_t i = 0; i < VERTEX_COUNT_; i++) {
    vertices_[i].x += x;
    vertices_[i].y += y;
  }
}

void hvostov::Complexquad::move(point_t center)
{
  double x = center.x - center_.x;
  double y = center.y - center_.y;
  move(x, y);
}

void hvostov::Complexquad::scale(double k)
{
  if (k <= 0) {
    throw std::invalid_argument("Scale must be positive");
  }
  for (size_t i = 0; i < VERTEX_COUNT_; i++) {
    vertices_[i].x = center_.x + k * (vertices_[i].x - center_.x);
    vertices_[i].y = center_.y + k * (vertices_[i].y - center_.y);
  }
}

void hvostov::scaleFromPoint(Shape & shape, double k, const point_t & scale_point)
{
  if (k <= 0) {
    throw std::invalid_argument("Scale must be positive");
  }
  point_t center = shape.getFrameRect().center;
  point_t new_center;
  new_center.x = scale_point.x + k * (center.x - scale_point.x);
  new_center.y = scale_point.y + k * (center.y - scale_point.y);
  shape.move(-scale_point.x, -scale_point.y);
  shape.scale(k);
  shape.move(scale_point.x, scale_point.y);
  shape.move(new_center.x - center.x, new_center.y - center.y);
}

hvostov::point_t hvostov::getCenter(const point_t * const vertices, size_t vertex_count)
{
  point_t center = {0.0, 0.0};
  double s = 0;
  for (size_t i = 0; i < vertex_count; i++) {
    size_t next = (i + 1) % vertex_count;
    double s_tmp = vertices[i].x * vertices[next].y - vertices[next].x * vertices[i].y;
    center.x += (vertices[i].x + vertices[next].x) * s_tmp;
    center.y += (vertices[i].y + vertices[next].y) * s_tmp;
    s += s_tmp;
  }
  s = std::abs(s / 2);
  center.x /= s * 6.0;
  center.y /= s * 6.0;
  return center;
}

double hvostov::getAreaByVertices(const point_t * const vertices, size_t vertex_count)
{
  double s = 0.0;
  for (size_t i = 0; i < vertex_count; i++) {
    size_t next = (i + 1) % vertex_count;
    s += vertices[i].x * vertices[next].y - vertices[next].x * vertices[i].y;
  }
  s = std::abs(s) / 2.0;
  return s;
}

hvostov::rectangle_t hvostov::getFrameRectWithVertices(const point_t * const vertices, size_t vertex_count)
{
  rectangle_t frame;
  double min_x = vertices[0].x, max_x = vertices[0].x;
  double min_y = vertices[0].y, max_y = vertices[0].y;
  for (size_t i = 1; i < vertex_count; i++) {
    if (vertices[i].x < min_x) {
      min_x = vertices[i].x;
    } else if (vertices[i].x > max_x) {
      max_x = vertices[i].x;
    }
    if (vertices[i].y < min_y) {
      min_y = vertices[i].y;
    } else if (vertices[i].y > max_y) {
      max_y = vertices[i].y;
    }
  }
  frame.height = max_y - min_y;
  frame.width = max_x - min_x;
  frame.center = {min_x + frame.width / 2, min_y + frame.height / 2};
  return frame;
}

hvostov::rectangle_t hvostov::getFrameRectOfAllShapes(const Shape * const * shapes, size_t shapes_count)
{
  rectangle_t frame = shapes[0]->getFrameRect();
  double min_x = frame.center.x - frame.width / 2;
  double max_x = frame.center.x + frame.width / 2;
  double min_y = frame.center.y - frame.height / 2;
  double max_y = frame.center.y + frame.height / 2;
  for (size_t i = 1; i < shapes_count; ++i) {
    frame = shapes[i]->getFrameRect();
    min_x = std::min(min_x, frame.center.x - frame.width / 2);
    max_x = std::max(max_x, frame.center.x + frame.width / 2);
    min_y = std::min(min_y, frame.center.y - frame.height / 2);
    max_y = std::max(max_y, frame.center.y + frame.height / 2);
  }
  point_t center = {min_x + frame.width / 2, min_y + frame.height / 2};
  return {max_x - min_x, max_y - min_y, center};
}

double hvostov::getAreaOfAllShapes(const Shape * const * shapes, size_t shape_count)
{
  double s = 0.0;
  for (size_t i = 0; i < shape_count; i++) {
    s += shapes[i]->getArea();
  }
  return s;
}

std::ostream & hvostov::printInformationAboutShape(std::ostream & out, const Shape * shape, size_t number)
{
  out << "Area of number " << number << " shape = " << shape->getArea() << "\n";
  rectangle_t frame = shape->getFrameRect();
  out << "Frame of number " << number << " width = " << frame.width << "\n";
  out << "Frame of number " << number << " height = " << frame.height << "\n";
  out << "Frame of number " << number << " center: (" << frame.center.x << "; " << frame.center.y << ")\n";
  return out;
}

std::ostream & hvostov::printInformationAboutShapes(std::ostream & out, const Shape * const * shapes, size_t shape_count)
{
  for (size_t i = 0; i < shape_count; i++) {
    printInformationAboutShape(out, shapes[i], i+1);
  }
  out << "Area of all shapes = " << getAreaOfAllShapes(shapes, shape_count) << "\n";
  rectangle_t frame = getFrameRectOfAllShapes(shapes, shape_count);
  out << "Frame of all shapes " << "width = " << frame.width << "\n";
  out << "Frame of all shapes " << "height = " << frame.height << "\n";
  out << "Frame of all shapes " << "center: (" << frame.center.x << "; " << frame.center.y << ")\n";
  return out;
}

void hvostov::deleteShapes(Shape ** shapes, size_t shape_count)
{
  for (size_t i = 0; i < shape_count; i++) {
    delete shapes[i];
  }
}
