#include "shape_comp.hpp"
#include <iostream>
zubarev::ShapeComp::ShapeComp():
  size_(0),
  capacity_(0),
  shapes_(nullptr)
{}

zubarev::ShapeComp::~ShapeComp() noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    delete shapes_[i];
  }
  delete[] shapes_;
}

zubarev::ShapeComp::ShapeComp(const ShapeComp& w):
  size_(w.size_),
  capacity_(w.capacity_),
  shapes_(w.size_ ? new Shape*[w.capacity_] : nullptr)
{
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i] = w.shapes_[i];
  }
}

zubarev::ShapeComp& zubarev::ShapeComp::operator=(const ShapeComp& w)
{
  Shape** r = nullptr;
  if (w.size_) {
    r = new Shape*[w.capacity_];
    for (size_t i = 0; i < w.size_; ++i) {
      r[i] = w.shapes_[i];
    }
  }
  delete[] shapes_;
  shapes_ = r;
  size_ = w.size_;
  capacity_ = w.capacity_;
  return *this;
}

zubarev::ShapeComp::ShapeComp(ShapeComp&& w):
  size_(w.size_),
  capacity_(w.capacity_),
  shapes_(w.shapes_)
{
  w.shapes_ = nullptr;
}

zubarev::ShapeComp& zubarev::ShapeComp::operator=(zubarev::ShapeComp&& w)
{
  if (this == &w) {
    return *this;
  }
  delete[] shapes_;
  shapes_ = w.shapes_;
  size_ = w.size_;
  capacity_ = w.capacity_;
  w.shapes_ = nullptr;
  return *this;
}

double zubarev::ShapeComp::getArea() const noexcept
{
  return getWholeArea(shapes_, size_);
}

zubarev::rectangle_t zubarev::ShapeComp::getFrameRect() const noexcept
{
  return getWholeFrame(shapes_, size_);
}

void zubarev::ShapeComp::move(const zubarev::point_t& p) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->move(p);
  }
}

void zubarev::ShapeComp::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->move(dx, dy);
  }
}

void zubarev::ShapeComp::scale(double k)
{
  if (k <= 0) {
    throw std::invalid_argument("Scale must be positive");
  }

  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->scale(k);
  }
}

void zubarev::ShapeComp::append(Shape* value)
{
  add(value, size_);
}

void zubarev::ShapeComp::preappend(Shape* value)
{
  add(value, 0);
}

void zubarev::ShapeComp::add(Shape* value, size_t index)
{
  if (index > size_) {
    throw std::out_of_range("Index out of range");
  }

  if (size_ >= capacity_) {
    size_t newCapacity = (capacity_ == 0) ? 2 : capacity_ * 2;
    Shape** newArr = new Shape*[newCapacity];

    for (size_t i = 0; i < index; ++i) {
      newArr[i] = shapes_[i];
    }

    newArr[index] = value;

    for (size_t i = index; i < size_; ++i) {
      newArr[i + 1] = shapes_[i];
    }

    delete[] shapes_;
    shapes_ = newArr;
    capacity_ = newCapacity;
  } else {
    for (size_t i = size_; i > index; --i) {
      shapes_[i] = shapes_[i - 1];
    }
    shapes_[index] = value;
  }

  ++size_;
}

zubarev::Shape& zubarev::ShapeComp::first() noexcept
{
  return get(0);
}
zubarev::Shape& zubarev::ShapeComp::last() noexcept
{
  return get(size_ - 1);
}

zubarev::Shape& zubarev::ShapeComp::at(size_t index)
{
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return *shapes_[index];
}

zubarev::Shape& zubarev::ShapeComp::get(size_t index) noexcept
{
  return *shapes_[index];
}

void zubarev::ShapeComp::remove(size_t index)
{
  if (index > size_) {
    throw std::out_of_range("Index out of range");
  }

  for (size_t i = index; i < size_; i++) {
    shapes_[i] = shapes_[i + 1];
  }

  --size_;
}

void zubarev::ShapeComp::dropFirst()
{
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  }

  remove(0);
}

void zubarev::ShapeComp::dropLast()
{
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  }

  remove(size_ - 1);
}

void zubarev::ShapeComp::clear() noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    delete shapes_[i];
  }
  size_ = 0;
}

size_t zubarev::ShapeComp::size() noexcept
{
  return size_;
}

bool zubarev::ShapeComp::empty() noexcept
{
  return (size_ == 0);
}

void zubarev::ShapeComp::reserve(size_t newCapacity)
{
  Shape** newArr = new Shape*[newCapacity];

  for (size_t i = 0; i < size_; ++i) {
    newArr[i] = shapes_[i];
  }

  delete[] shapes_;
  shapes_ = newArr;
  capacity_ = newCapacity;
}

void zubarev::ShapeComp::shrink()
{
  reserve(size_);
}

size_t zubarev::ShapeComp::capacity() noexcept
{
  return capacity_;
}

zubarev::Shape** zubarev::ShapeComp::shapes() noexcept
{
  return shapes_;
}
