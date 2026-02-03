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
    void preappend(const CompositeFigure &compFig);
    void preappend(CompositeFigure &&compFig);
    CompositeFigure preappend(const CompositeFigure &comFig) const;
    CompositeFigure preappend(CompositeFigure &&comFig) const;

    void append(IShape *figure);
    void append(const CompositeFigure &compFig);
    void append(CompositeFigure &&compFig);
    CompositeFigure append(const CompositeFigure &comFig) const;
    CompositeFigure append(CompositeFigure &&comFig) const;

    void add(IShape *figure, size_t pos);
    void add(const CompositeFigure &compFig, size_t pos);
    void add(CompositeFigure &&compFig, size_t pos);
    CompositeFigure add(const CompositeFigure &comFig, size_t pos) const;
    CompositeFigure add(CompositeFigure &&comFig, size_t pos) const;

    void merge(const CompositeFigure &comFig);
    void merge(CompositeFigure &&comFig);
    CompositeFigure merge(const CompositeFigure &comFig) const;
    CompositeFigure merge(CompositeFigure &&comFig) const;

    void premerge(const CompositeFigure &comFig);
    void premerge(CompositeFigure &&comFig);
    CompositeFigure premerge(const CompositeFigure &comFig) const;
    CompositeFigure premerge(CompositeFigure &&comFig) const;

    void mergeAt(const CompositeFigure &comFig, size_t pos);
    void mergeAt(CompositeFigure &&comFig, size_t pos);
    CompositeFigure mergeAt(const CompositeFigure &comFig, size_t pos) const;
    CompositeFigure mergeAt(CompositeFigure &&comFig, size_t pos) const;

    void merge();
    CompositeFigure merge() const;

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
      IShape *&operator[](size_t index) const;

      ~ShapeVector();

      void insert(IShape *figure, size_t pos);
      void insert(const ShapeVector &vector, size_t pos);
      void moveInsert(ShapeVector &&vector, size_t pos);

      void merge(const ShapeVector &vector, size_t pos);
      void moveMerge(ShapeVector &&vector, size_t pos);

      void merge();

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
      void shift(size_t pos, size_t size);
      void insertPositionCheck(size_t pos) const;
      int find(IShape *figure) const;
      ShapeVector getUniqs(const ShapeVector &vector) const;
    };

    ShapeVector figures;

    bool isSameAddr(const CompositeFigure &compFig) const noexcept;
  };
}

#endif
