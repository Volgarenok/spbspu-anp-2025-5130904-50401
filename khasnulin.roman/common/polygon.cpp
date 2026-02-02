#include <headers/point.hpp>
#include <headers/shapes/polygon.hpp>
#include <stdexcept>

namespace
{
  double triagleSignedArea(khasnulin::point_t v1, khasnulin::point_t v2)
  {
    return (v1.x * v2.y - v2.x * v1.y) / 2;
  }

  khasnulin::point_t getTriangleCenter(khasnulin::point_t v1, khasnulin::point_t v2)
  {
    return (v1 + v2) / 3;
  }

  khasnulin::point_t calculateCenter(const khasnulin::point_t *points, size_t k)
  {
    double figure_area = triagleSignedArea(points[0], points[1]);
    khasnulin::point_t figure_center = getTriangleCenter(points[0], points[1]) * figure_area;
    for (size_t i = 1; i < k - 1; i++)
    {
      double current_area = triagleSignedArea(points[i], points[i + 1]);
      khasnulin::point_t current_center = getTriangleCenter(points[i], points[i + 1]);
      figure_center = figure_center + current_center * current_area;
      figure_area += current_area;
    }
    double last_area = triagleSignedArea(points[k - 1], points[0]);
    figure_center = figure_center + getTriangleCenter(points[k - 1], points[0]) * last_area;
    figure_area += last_area;
    return figure_area ? (figure_center / figure_area) : khasnulin::point_t{0, 0};
  }

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

khasnulin::Polygon::~Polygon()
{
  delete[] vertex;
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

khasnulin::IShape *khasnulin::Polygon::clone() const
{
  return new Polygon(*this);
}