#include "composite_figure.hpp"
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
    size_(0),
    capacity_(sv.capacity_),
    figures_(new IShape *[sv.capacity_])
{
  try
  {
    for (size_t i = 0; i < sv.size_; ++i)
    {
      figures_[i] = sv[i]->clone();
      ++size_;
    }
  }
  catch (...)
  {
    clear();
    delete[] figures_;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
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

khasnulin::IShape *&khasnulin::CompositeFigure::ShapeVector::operator[](size_t index) const
{
  return figures_[index];
}

void khasnulin::CompositeFigure::ShapeVector::insert(IShape *figure, size_t pos)
{
  insertPositionCheck(pos);
  ensureCapacity(size_ + 1);
  for (size_t i = size_; i > pos; --i)
  {
    figures_[i] = figures_[i - 1];
  }
  figures_[pos] = figure;
  ++size_;
}

void khasnulin::CompositeFigure::ShapeVector::insert(const ShapeVector &vector, size_t pos)
{
  insertPositionCheck(pos);
  shift(pos, vector.size());
  size_t inserted = 0;
  try
  {
    for (size_t i = pos, end = pos + vector.size(); i < end; ++i)
    {
      figures_[i] = vector[i - pos]->clone();
      ++inserted;
    }
  }
  // TODO: создавать буфер, сделать операцию shift в самом конце
  catch (...)
  {
    clear();
    throw;
  }
}

void khasnulin::CompositeFigure::ShapeVector::moveInsert(ShapeVector &&vector, size_t pos)
{
  insertPositionCheck(pos);
  shift(pos, vector.size());
  for (size_t i = pos, end = pos + vector.size(); i < end; ++i)
  {
    figures_[i] = vector[i - pos];
    vector[i - pos] = nullptr;
  }
  vector.size_ = 0;
}

void khasnulin::CompositeFigure::ShapeVector::insertPositionCheck(size_t pos) const
{
  if (pos > size_)
  {
    throw std::out_of_range("trying to insert elements over array boundary");
  }
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

void khasnulin::CompositeFigure::ShapeVector::shift(size_t pos, size_t shiftSize)
{
  if (!shiftSize)
  {
    throw std::invalid_argument("shiftSize must be more than zero");
  }
  ensureCapacity(size_ + shiftSize);
  for (size_t i = size_ + shiftSize - 1, end = pos + shiftSize - 1; i > end; --i)
  {
    figures_[i] = figures_[i - shiftSize];
    figures_[i - shiftSize] = nullptr;
  }
  size_ += shiftSize;
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

size_t khasnulin::CompositeFigure::ShapeVector::merge(const ShapeVector &vector, size_t pos)
{
  if (pos > size_)
  {
    throw std::out_of_range("trying to merge elements over array boundary");
  }
  ShapeVector uniqFigures = getUniqs(vector);
  size_t eliminatedDuplicates = vector.size() - uniqFigures.size();
  insert(uniqFigures, pos);
  for (size_t i = 0; i < uniqFigures.size_; ++i)
  {
    uniqFigures[i] = nullptr;
  }
  return eliminatedDuplicates;
}

size_t khasnulin::CompositeFigure::ShapeVector::moveMerge(ShapeVector &&vector, size_t pos)
{
  if (pos > size_)
  {
    throw std::out_of_range("trying to merge elements over array boundary");
  }

  ShapeVector uniqFigures = getUniqs(vector);
  size_t eliminatedDuplicates = vector.size() - uniqFigures.size();
  for (size_t i = 0; i < vector.size_; ++i)
  {
    vector.figures_[i] = nullptr;
  }
  moveInsert(std::move(uniqFigures), pos);
  return eliminatedDuplicates;
}

khasnulin::CompositeFigure::ShapeVector
khasnulin::CompositeFigure::ShapeVector::getUniqs(const ShapeVector &vector) const
{
  ShapeVector uniqFigures;
  for (size_t i = 0; i < vector.size_; ++i)
  {
    if (find(vector.figures_[i]) == -1)
    {
      uniqFigures.insert(vector.figures_[i], uniqFigures.size());
    }
  }
  return uniqFigures;
}

int khasnulin::CompositeFigure::ShapeVector::find(IShape *figure) const
{
  for (size_t i = 0; i < size_; ++i)
  {
    if (figures_[i] == figure)
    {
      return i;
    }
  }
  return -1;
}

void khasnulin::CompositeFigure::ShapeVector::merge()
{
  size_t firstDuplicatePos = 0;
  for (size_t i = 0; i < size_; ++i)
  {
    bool isDupl = false;
    for (size_t j = 0; j < i && !isDupl; ++j)
    {
      if (figures_[j] == figures_[i])
      {
        isDupl = true;
      }
    }

    if (!isDupl)
    {
      figures_[firstDuplicatePos] = figures_[i];
      ++firstDuplicatePos;
    }
  }

  for (size_t i = firstDuplicatePos; i < size_; ++i)
  {
    figures_[i] = nullptr;
  }
  size_ = firstDuplicatePos;
}