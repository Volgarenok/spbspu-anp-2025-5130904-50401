#include "geometry.hpp"
#include <cmath>

const double PI = std::acos(-1.0);

void goltsov::Shape::scale(double k)
{
  if (k <= 0)
  {
    throw std::logic_error("The zoom level must be greater than 0");
  }
  doScale(k);
}

goltsov::Rectangle::Rectangle(const double width, const double height, const point_t pos)
{
  if (width <= 0 || height <= 0)
  {
    throw std::logic_error("The width and height must be greater than zero");
  }
  a.width = width;
  a.height = height;
  a.pos = pos;
}
double goltsov::Rectangle::getArea() const
{
  return a.width * a.height;
}
goltsov::rectangle_t goltsov::Rectangle::getFrameRect() const
{
  return a;
}
void goltsov::Rectangle::move(const goltsov::point_t newPos)
{
  a.pos = newPos;
}
void goltsov::Rectangle::move(const double dx, const double dy)
{
  a.pos.x += dx;
  a.pos.y += dy;
}
void goltsov::Rectangle::doScale(const double k)
{
  a.height *= k;
  a.width *= k;
}

goltsov::Rubber::Rubber(const double r10, const point_t pos10, const double r20, const point_t pos20):
  r1(r10),
  r2(r20),
  pos1(pos10),
  pos2(pos20)
{
  if (r1 <= 0 || r2 <= 0)
  {
    throw std::logic_error("The radii of the circles must be greater than 0");
  }
  if (pos1.x == pos2.x && pos1.y == pos2.y)
  {
    throw std::logic_error("The centers of the circles should not coincide");
  }
  if ((sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y)) + r2) > r1)
  {
    throw std::logic_error("The smaller circle should lie completely inside the larger one");
  }
}
double goltsov::Rubber::getArea() const
{
  return PI * (r1 * r1 - r2 * r2);
}
goltsov::rectangle_t goltsov::Rubber::getFrameRect() const
{
  return {r1 * 2, r1 * 2, pos1};
}
void goltsov::Rubber::move(const goltsov::point_t newPos)
{
  double dx = pos1.x - pos2.x;
  double dy = pos1.y - pos2.y;
  pos2 = newPos;
  pos1.x = pos2.x + dx;
  pos1.y = pos2.y + dy;
}
void goltsov::Rubber::move(const double dx, const double dy)
{
  pos1.x += dx;
  pos2.x += dx;
  pos1.y += dy;
  pos2.y += dy;
}
void goltsov::Rubber::doScale(const double k)
{
  r1 *= k;
  r2 *= k;
  double dx = pos1.x - pos2.x;
  double dy = pos1.y - pos2.y;
  pos1.x = pos2.x + k * dx;
  pos1.y = pos2.y + k * dy;
}

goltsov::point_t goltsov::Polygon::polygonCentroid(const goltsov::point_t* mtx, const size_t n)
{
  if (n < 3)
  {
      point_t center = {0, 0};
      if (n > 0)
      {
          for (size_t i = 0; i < n; i++)
          {
            center.x += mtx[i].x;
            center.y += mtx[i].y;
          }
          center.x /= n;
          center.y /= n;
      }
      return center;
  }
  double area = 0.0;
  double centroid_x = 0.0;
  double centroid_y = 0.0;
  for (size_t i = 0; i < n; i++)
  {
    size_t j = (i + 1) % n;
    double cross = (mtx[i].x * mtx[j].y - mtx[j].x * mtx[i].y);
    area += cross;
    centroid_x += (mtx[i].x + mtx[j].x) * cross;
    centroid_y += (mtx[i].y + mtx[j].y) * cross;
  }
  area *= 0.5;
  double factor = 1.0 / (6.0 * area);
  point_t centroid;
  centroid.x = centroid_x * factor;
  centroid.y = centroid_y * factor;
  return centroid;
}
goltsov::Polygon::Polygon(const point_t* mtx0, const size_t n0):
  n(n0),
  pos(polygonCentroid(mtx0, n))
{
  if (n < 3)
  {
    throw std::logic_error("The polygon must have at least 3 vertices");
  }
  this->mtx = new point_t[n];
  for (size_t i = 0; i < n; ++i)
  {
    this->mtx[i] = mtx0[i];
  }
}
goltsov::Polygon::Polygon(const Polygon& other):
  n(other.n),
  pos(other.pos)
{
  mtx = new point_t[other.n];
  for (size_t i = 0; i < n; ++i)
  {
    mtx[i] = other.mtx[i];
  }
}
goltsov::Polygon::Polygon(Polygon&& other):
  n(std::move(other.n)),
  pos(other.pos)
{
  mtx = other.mtx;
  other.mtx = nullptr;
}
goltsov::Polygon& goltsov::Polygon::operator=(const Polygon& other)
{
  if (this != std::addressof(other))
  {
    delete[] mtx;
    n = other.n;
    pos = other.pos;
    mtx = new point_t[n];
    for (size_t i = 0; i < n; ++i)
    {
      mtx[i] = other.mtx[i];
    }
  }
  return * this;
}
goltsov::Polygon& goltsov::Polygon::operator=(Polygon&& other)
{
  if (this != std::addressof(other))
  {
    delete[] mtx;
    mtx = other.mtx;
    other.mtx = nullptr;
    n = other.n;
    pos = other.pos;
  }
  return * this;
}
goltsov::Polygon::~Polygon()
{
  delete[] mtx;
}
double goltsov::Polygon::getArea() const
{
    if (n < 3) return 0.0;
    double area = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        size_t j = (i + 1) % n;
        area += mtx[i].x * mtx[j].y - mtx[j].x * mtx[i].y;
    }
    return fabs(area) * 0.5;
}
goltsov::rectangle_t goltsov::Polygon::getFrameRect() const
{
  double max_x = mtx[0].x;
  double min_x = mtx[0].x;
  double max_y = mtx[0].y;
  double min_y = mtx[0].y;
  for (size_t i = 0; i < n; ++i)
  {
    max_x = (max_x < mtx[i].x ? mtx[i].x : max_x);
    min_x = (min_x > mtx[i].x ? mtx[i].x : min_x);
    max_y = (max_y < mtx[i].y ? mtx[i].y : max_y);
    min_y = (min_y > mtx[i].y ? mtx[i].y : min_y);
  }
  return {max_x - min_x, max_y - min_y, {(max_x + min_x)/2, (max_y + min_y)/2}};
}
void goltsov::Polygon::move(const goltsov::point_t newPos)
{
  double dx = newPos.x - pos.x;
  double dy = newPos.y - pos.y;
  for (size_t i = 0; i < n; ++i)
  {
    mtx[i].x += dx;
    mtx[i].y += dy;
  }
  pos = newPos;
}
void goltsov::Polygon::move(const double dx, const double dy)
{
  for (size_t i = 0; i < n; ++i)
  {
    mtx[i].x += dx;
    mtx[i].y += dy;
  }
  pos.x += dx;
  pos.y += dy;
}
void goltsov::Polygon::doScale(const double k)
{
  for (size_t i = 0; i < n; ++i)
  {
    double dx = mtx[i].x - pos.x;
    double dy = mtx[i].y - pos.y;
    dx *= k;
    dy *= k;
    mtx[i].x = pos.x + dx;
    mtx[i].y = pos.y + dy;
  }
}

void goltsov::scaleRelativePoint(goltsov::Shape* a, goltsov::point_t p, double k)
{
  point_t p1 = a->getFrameRect().pos;
  a->move(p);
  a->scale(k);
  point_t p2 = a->getFrameRect().pos;
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  dx *= k;
  dy *= k;
  a->move(dx, dy);
}
