#ifndef SHAPES_COMP_H
#define SHAPES_COMP_H
#include <all.hpp>
namespace zubarev
{
  struct ShapeComp : Shape
  {
    ShapeComp();
    ~ShapeComp() noexcept;
    ShapeComp(const ShapeComp& w);
    ShapeComp& operator=(const ShapeComp& w);
    ShapeComp(ShapeComp&& w);
    ShapeComp& operator=(ShapeComp&& w);

    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& p) noexcept override;
    void move(double dx, double dy) noexcept override;
    void scale(double k) override;

    void append(Shape* value);
    void preappend(Shape* value);
    void add(Shape* value, size_t index);
    Shape& first() noexcept;
    const Shape& first() const noexcept;
    Shape& last() noexcept;
    const Shape& last() const noexcept;
    Shape& at(size_t index);
    const Shape& at(size_t index) const;
    Shape& get(size_t index) noexcept;
    const Shape& get(size_t index) const noexcept;
    void remove(size_t index);
    void dropFirst();
    void dropLast();
    void clear() noexcept;
    size_t size() noexcept;
    bool empty() noexcept;
    void reserve(size_t newCapacity);
    void shrink();
    size_t capacity() noexcept;
    Shape** shapes() noexcept;

  private:
    size_t size_;
    size_t capacity_;
    Shape** shapes_;
  };
}
#endif
