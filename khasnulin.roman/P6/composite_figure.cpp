#include "composite_figure.hpp"

#include <stdexcept>

void khasnulin::CompositeFigure::preappend(IShape *figure)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("can't preappend figure, get nullptr instead of IShape pointer");
  }
  figures.insert(figure, 0);
}

void khasnulin::CompositeFigure::preappend(const CompositeFigure &compFig)
{
  if (isSameAddr(compFig))
  {
    throw std::runtime_error("can't preappend composite figure for itself by copy");
  }
  figures.insert(compFig.figures, 0);
}

void khasnulin::CompositeFigure::preappend(CompositeFigure &&compFig)
{
  if (isSameAddr(compFig))
  {
    throw std::runtime_error("can't preappend composite figure for itself by move");
  }
  figures.moveInsert(compFig.figures, 0);
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::preappend(const CompositeFigure &comFig) const
{
  CompositeFigure newFigure = CompositeFigure(*this);
  newFigure.preappend(comFig);
  return newFigure;
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::preappend(CompositeFigure &&comFig) const
{
  CompositeFigure newFigure = CompositeFigure(*this);
  newFigure.preappend(std::move(comFig));
  return newFigure;
}

void khasnulin::CompositeFigure::append(IShape *figure)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("can't append figure, get nullptr instead of IShape pointer");
  }
  figures.insert(figure, figures.size());
}

void khasnulin::CompositeFigure::append(const CompositeFigure &compFig)
{
  if (isSameAddr(compFig))
  {
    throw std::runtime_error("can't append composite figure for itself by copy");
  }
  figures.insert(compFig.figures, figures.size());
}

void khasnulin::CompositeFigure::append(CompositeFigure &&compFig)
{
  if (isSameAddr(compFig))
  {
    throw std::runtime_error("can't append composite figure for itself by move");
  }
  figures.moveInsert(compFig.figures, figures.size());
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::append(const CompositeFigure &comFig) const
{
  CompositeFigure newFigure = CompositeFigure(*this);
  newFigure.append(comFig);
  return newFigure;
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::append(CompositeFigure &&comFig) const
{
  CompositeFigure newFigure = CompositeFigure(*this);
  newFigure.append(std::move(comFig));
  return newFigure;
}

void khasnulin::CompositeFigure::add(IShape *figure, size_t pos)
{
  if (figure == nullptr)
  {
    throw std::invalid_argument("can't add figure, get nullptr instead of IShape pointer");
  }
  figures.insert(figure, pos);
}

void khasnulin::CompositeFigure::add(const CompositeFigure &compFig, size_t pos)
{
  if (isSameAddr(compFig))
  {
    throw std::invalid_argument("can't add composite figure for itself by copy");
  }
  figures.insert(compFig.figures, pos);
}

void khasnulin::CompositeFigure::add(CompositeFigure &&compFig, size_t pos)
{
  if (isSameAddr(compFig))
  {
    throw std::invalid_argument("can't add composite figure for itself by move");
  }
  figures.moveInsert(compFig.figures, pos);
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::add(const CompositeFigure &comFig, size_t pos) const
{
  CompositeFigure newFigure = CompositeFigure(*this);
  newFigure.add(comFig, pos);
  return newFigure;
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::add(CompositeFigure &&comFig, size_t pos) const
{
  CompositeFigure newFigure = CompositeFigure(*this);
  newFigure.add(std::move(comFig), pos);
  return newFigure;
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

bool khasnulin::CompositeFigure::isSameAddr(const CompositeFigure &compFig) const noexcept
{
  return this == std::addressof(compFig);
}