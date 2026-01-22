#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <fstream>
namespace goltsov
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
  struct Shape
  {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t) = 0;
    virtual void move(const double, const double) = 0;
    virtual void scale(const double);
    virtual ~Shape() = default;
  protected:
    virtual void doScale(const double k) = 0;
  };
  struct Rectangle: Shape
  {
    Rectangle(const double, const double, const point_t);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t) override;
    void move(const double, const double) override;
    void doScale(const double) override;
  private:
    rectangle_t a;
  };
  struct Rubber: Shape
  {
    Rubber(const double, const point_t, const double, const point_t);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t) override;
    void move(const double, const double) override;
    void doScale(const double) override;
  private:
    double r1, r2;
    point_t pos1, pos2;
  };
  struct Polygon: Shape
  {
    Polygon(const point_t*, const size_t);
    Polygon(const Polygon&);
    Polygon(Polygon&&);
    Polygon& operator=(const Polygon&);
    Polygon& operator=(Polygon&&);
    ~Polygon();
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t) override;
    void move(const double, const double) override;
    void doScale(const double) override;
  private:
    point_t* mtx = nullptr;
    size_t n;
    point_t pos;
    point_t polygonCentroid(const point_t*, const size_t);
  };
  void scaleRelativePoint(goltsov::Shape*, goltsov::point_t, double);
  void totalPrint(size_t, Shape**, std::ostream&);
}
#endif
