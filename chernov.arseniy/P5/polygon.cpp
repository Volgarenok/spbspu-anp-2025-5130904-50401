#include "polygon.hpp"
#include <stdexcept>

chernov::Polygon::Polygon(point_t * points, size_t size):
  Shape(),
  verts(new point_t[size]),
  count(size),
  center({0, 0})
{
  if (count < 3) {
    delete [] verts;
    throw std::invalid_argument("the count must not be less than 3");
  }
  for (size_t i = 0; i < count; ++i) {
    verts[i] = points[i];
  }
  center = getCentroid();
}

chernov::Polygon::~Polygon()
{
  delete [] verts;
}

chernov::Polygon::Polygon(const Polygon & p):
  Shape(),
  verts(new point_t[p.count]),
  count(p.count),
  center(p.center)
{
  for (size_t i = 0; i < count; ++i) {
    verts[i] = p.verts[i];
  }
}

chernov::Polygon & chernov::Polygon::operator=(const Polygon & p)
{
  if (this == std::addressof(p)) {
    return *this;
  }
  point_t * points = new point_t[p.count];
  for (size_t i = 0; i < p.count; ++i) {
    points[i] = p.verts[i];
  }
  delete [] verts;
  verts = points;
  count = p.count;
  center = p.center;
  return *this;
}

chernov::Polygon::Polygon(Polygon && p):
  Shape(),
  verts(p.verts),
  count(p.count),
  center(p.center)
{
  p.verts = nullptr;
}

chernov::Polygon & chernov::Polygon::operator=(Polygon && p)
{
  if (this == std::addressof(p)) {
    return *this;
  }
  delete [] verts;
  verts = p.verts;
  count = p.count;
  center = p.center;
  p.verts = nullptr;
  return *this;
}

double chernov::Polygon::getSignedArea() const
{
  double area = 0;
  for (size_t i = 0; i < count; ++i) {
    area += verts[i].x * verts[(i + 1) % count].y;
    area -= verts[i].y * verts[(i + 1) % count].x;
  }
  area *= 0.5;
  return area;
}

double chernov::Polygon::getArea() const
{
  return std::abs(getSignedArea());
}

chernov::rectangle_t chernov::Polygon::getFrameRect() const
{
  return getFrameRectByVerts(verts, count);
}

void chernov::Polygon::move(point_t p)
{
  double dx = p.x - center.x;
  double dy = p.y - center.y;
  move(dx, dy);
}

void chernov::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < count; ++i) {
    verts[i].x += dx;
    verts[i].y += dy;
  }
  center.x += dx;
  center.y += dy;
}

void chernov::Polygon::doScale(double k)
{
  for (size_t i = 0; i < count; ++i) {
    double dx = k * (verts[i].x - center.x);
    double dy = k * (verts[i].y - center.y);
    verts[i].x = center.x + dx;
    verts[i].y = center.y + dy;
  }
}

chernov::point_t chernov::Polygon::getCentroid() const
{
  double cx = 0.0, cy = 0.0;
  for (size_t i = 0; i < count; ++i) {
    double x0 = verts[i].x, y0 = verts[i].y;
    double x1 = verts[(i + 1) % count].x, y1 = verts[(i + 1) % count].y;
    double cross = x0 * y1 - x1 * y0;
    cx += (x0 + x1) * cross;
    cy += (y0 + y1) * cross;
  }
  double signed_area = getSignedArea();
  cx /= 6 * signed_area;
  cy /= 6 * signed_area;
  return {cx, cy};
}
