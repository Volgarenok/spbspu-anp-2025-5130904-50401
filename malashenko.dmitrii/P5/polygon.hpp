#ifndef POLYGON
#define POLYGON
#include "pod.hpp"
#include "shape.hpp"
#include <cstddef>
namespace malashenko {
  struct Polygon : Shape {
    Polygon(point_t * tops, size_t length);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    ~Polygon() override
    {
    delete[] tops_;
    }

  private:
    size_t length_;
    point_t * tops_;
    point_t pos_;
  };
}
#endif
