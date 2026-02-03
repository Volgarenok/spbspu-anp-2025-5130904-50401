#include "composite_figure.hpp"

#include <istream>
#include <stdexcept>

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

bool khasnulin::CompositeFigure::isSameAddr(const CompositeFigure &compFig) const noexcept
{
  return this == std::addressof(compFig);
}

void khasnulin::CompositeFigure::printFiguresArray(std::ostream &out)
{
  out << "[size]: " << figures.size() << "; [";
  out.flush();
  for (size_t i = 0, end = figures.size(); i < end; ++i)
  {
    if (figures[i] != nullptr)
    {
      out << " " << figures[i]->getShapeName();
      out.flush();
    }
    else
    {
      out << " nullptr";
      out.flush();
    }
    if (i != end - 1)
    {
      out << ", ";
      out.flush();
    }
  }
  out << " ]\n";
  out.flush();
}
