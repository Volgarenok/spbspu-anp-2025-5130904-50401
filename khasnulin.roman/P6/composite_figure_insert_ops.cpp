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
  figures.moveInsert(std::move(compFig.figures), 0);
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
  figures.moveInsert(std::move(compFig.figures), figures.size());
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
  figures.moveInsert(std::move(compFig.figures), pos);
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
