#include "composite_figure.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace
{
  void copyShapes(khasnulin::IShape **from, khasnulin::IShape **to, size_t size) noexcept
  {
    for (size_t i = 0; i < size; i++)
    {
      to[i] = from[i];
    }
  }
}

khasnulin::CompositeFigure::ShapeVector::ShapeVector() noexcept:
    size_(0),
    capacity_(0),
    figures_(nullptr)
{
}

khasnulin::CompositeFigure::ShapeVector::ShapeVector(const ShapeVector &sv):
    size_(sv.size_),
    capacity_(sv.capacity_),
    figures_(new IShape *[sv.capacity_])
{
  copyShapes(sv.figures_, figures_, size_);
}

khasnulin::CompositeFigure::ShapeVector::ShapeVector(ShapeVector &&sv) noexcept:
    size_(sv.size_),
    capacity_(sv.capacity_),
    figures_(sv.figures_)
{
  sv.figures_ = nullptr;
  sv.capacity_ = 0;
  sv.size_ = 0;
}

khasnulin::CompositeFigure::ShapeVector &
khasnulin::CompositeFigure::ShapeVector::operator=(const ShapeVector &sv)
{
  if (this == std::addressof(sv))
  {
    return *this;
  }
  IShape **newFigures = new IShape *[sv.capacity_];

  copyShapes(sv.figures_, newFigures, sv.size_);
  delete[] figures_;
  figures_ = newFigures;
  size_ = sv.size_;
  capacity_ = sv.capacity_;
  return *this;
}

khasnulin::CompositeFigure::ShapeVector &
khasnulin::CompositeFigure::ShapeVector::operator=(ShapeVector &&sv) noexcept
{
  if (this == std::addressof(sv))
  {
    return *this;
  }
  std::swap(figures_, sv.figures_);
  std::swap(size_, sv.size_);
  std::swap(capacity_, sv.capacity_);
  return *this;
}

khasnulin::CompositeFigure::ShapeVector::~ShapeVector()
{
  clear();
  delete[] figures_;
}

size_t khasnulin::CompositeFigure::ShapeVector::size() const noexcept
{
  return size_;
}

khasnulin::IShape *khasnulin::CompositeFigure::ShapeVector::operator[](size_t index) const
{
  return figures_[index];
}

void khasnulin::CompositeFigure::ShapeVector::insert(IShape *figure, size_t pos)
{
  if (pos > size_)
  {
    throw std::out_of_range("trying to insert element over array boundary");
  }
  ensureCapacity(size_ + 1);
  for (size_t i = size_; i > pos; --i)
  {
    figures_[i] = figures_[i - 1];
  }
  figures_[pos] = figure;
  ++size_;
}

void khasnulin::CompositeFigure::ShapeVector::ensureCapacity(size_t newSize)
{
  size_t newCapacity = newSize > capacity_ * 2 ? newSize : capacity_ * 2;
  makeShapesByCapacity(newCapacity);
}

bool khasnulin::CompositeFigure::ShapeVector::empty() const
{
  return !size_;
}

void khasnulin::CompositeFigure::ShapeVector::erase(size_t pos)
{
  if (pos >= size_)
  {
    throw std::out_of_range("trying to delete element over array boundary");
  }
  delete figures_[pos];
  copyShapes(&figures_[pos + 1], &figures_[pos], size_ - pos - 1);
  figures_[size_ - 1] = nullptr;
  --size_;
}

void khasnulin::CompositeFigure::ShapeVector::clear()
{
  for (size_t i = 0; i < size_; i++)
  {
    delete figures_[i];
  }
  size_ = 0;
}

void khasnulin::CompositeFigure::ShapeVector::makeShapesByCapacity(size_t capacity)
{
  IShape **newFigures = new IShape *[capacity];
  copyShapes(figures_, newFigures, size_);
  delete[] figures_;
  capacity_ = capacity;
  figures_ = newFigures;
}

void khasnulin::CompositeFigure::ShapeVector::changeCapacity(size_t newCapacity)
{
  newCapacity = newCapacity > size_ ? newCapacity : size_;
  makeShapesByCapacity(newCapacity);
}

size_t khasnulin::CompositeFigure::ShapeVector::getCapacity() const
{
  return capacity_;
}

void khasnulin::CompositeFigure::preappend(IShape *figure)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("can't preappend figure, get nullptr instead of IShape pointer");
  }
  figures.insert(figure, 0);
}

void khasnulin::CompositeFigure::append(IShape *figure)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("can't append figure, get nullptr instead of IShape pointer");
  }
  figures.insert(figure, figures.size());
}

void khasnulin::CompositeFigure::add(IShape *figure, size_t pos)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("can't add figure, get nullptr instead of IShape pointer");
  }
  figures.insert(figure, pos);
}

khasnulin::IShape &khasnulin::CompositeFigure::last()
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get last element, array is empty");
  }
  return *figures[figures.size() - 1];
}

khasnulin::IShape &khasnulin::CompositeFigure::first()
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get first element, array is empty");
  }
  return *figures[0];
}

const khasnulin::IShape &khasnulin::CompositeFigure::last() const
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get last element, array is empty");
  }
  return *figures[figures.size() - 1];
}

const khasnulin::IShape &khasnulin::CompositeFigure::first() const
{
  if (figures.empty())
  {
    throw std::runtime_error("can't get first element, array is empty");
  }
  return *figures[0];
}

khasnulin::IShape &khasnulin::CompositeFigure::at(size_t index)
{
  if (index >= figures.size())
  {
    throw std::out_of_range("index out of array boundaries");
  }
  return *figures[index];
}

khasnulin::IShape &khasnulin::CompositeFigure::get(size_t index)
{
  return *figures[index];
}

const khasnulin::IShape &khasnulin::CompositeFigure::at(size_t index) const
{
  if (index >= figures.size())
  {
    throw std::out_of_range("index out of array boundaries");
  }
  return *figures[index];
}

const khasnulin::IShape &khasnulin::CompositeFigure::get(size_t index) const
{
  return *figures[index];
}

void khasnulin::CompositeFigure::remove(size_t index)
{
  figures.erase(index);
}

void khasnulin::CompositeFigure::dropFirst()
{
  figures.erase(0);
}

void khasnulin::CompositeFigure::dropLast()
{
  figures.erase(!figures.empty() ? figures.size() - 1 : 0);
}

void khasnulin::CompositeFigure::clear()
{
  figures.clear();
}

size_t khasnulin::CompositeFigure::size() const
{
  return figures.size();
}

bool khasnulin::CompositeFigure::empty() const
{
  return figures.empty();
}

void khasnulin::CompositeFigure::reserve(size_t newCapacity)
{
  figures.changeCapacity(newCapacity);
}

void khasnulin::CompositeFigure::shrink()
{
  figures.changeCapacity(figures.size());
}

size_t khasnulin::CompositeFigure::capacity() const
{
  return figures.getCapacity();
}
