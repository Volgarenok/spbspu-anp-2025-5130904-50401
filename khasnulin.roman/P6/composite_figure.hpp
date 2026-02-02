#ifndef COMPOSITE_FIGURE_HPP
#define COMPOSITE_FIGURE_HPP

#include <headers/shapes/ishape.hpp>

namespace khasnulin
{
  class CompositeFigure
  {
  public:
    CompositeFigure() noexcept = default;
    CompositeFigure(const CompositeFigure &cf) = default;
    CompositeFigure(CompositeFigure &&cf) noexcept = default;

    ~CompositeFigure() = default;

    CompositeFigure &operator=(const CompositeFigure &cf) = default;
    CompositeFigure &operator=(CompositeFigure &&cf) = default;

    void preappend(IShape *figure);
    void append(IShape *figure);
    void add(IShape *figure, size_t pos);

    IShape &last();
    IShape &first();
    const IShape &last() const;
    const IShape &first() const;

    IShape &at(size_t index);
    IShape &get(size_t index);
    const IShape &at(size_t index) const;
    const IShape &get(size_t index) const;

    void remove(size_t index);

    void dropFirst();
    void dropLast();

    void clear();

    size_t size() const;

    bool empty() const;

    void reserve(size_t newCapacity);
    void shrink();
    size_t capacity() const;

  private:
    class ShapeVector
    {
    public:
      ShapeVector() noexcept;
      ShapeVector(const ShapeVector &sv);
      ShapeVector(ShapeVector &&sv) noexcept;

      ShapeVector &operator=(const ShapeVector &sv);
      ShapeVector &operator=(ShapeVector &&sv) noexcept;
      IShape *operator[](size_t index) const;

      ~ShapeVector();

      void insert(IShape *figure, size_t pos);
      void erase(size_t pos);
      size_t size() const noexcept;
      bool empty() const;

      void clear();

      size_t getCapacity() const;
      void changeCapacity(size_t newCapacity);

    private:
      size_t size_;
      size_t capacity_;
      IShape **figures_;

      void ensureCapacity(size_t newSize);
      void makeShapesByCapacity(size_t capacity);
    };

    ShapeVector figures;
  };
}

#endif
