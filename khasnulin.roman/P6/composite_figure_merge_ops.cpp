#include "composite_figure.hpp"
#include <utility>

void khasnulin::CompositeFigure::merge(const CompositeFigure &comFig)
{
  if (!isSameAddr(comFig))
  {
    figures.merge(comFig.figures, figures.size());
  }
}

void khasnulin::CompositeFigure::merge(CompositeFigure &&comFig)
{
  if (!isSameAddr(comFig))
  {
    figures.moveMerge(std::move(comFig.figures), figures.size());
  }
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::merge(const khasnulin::CompositeFigure &comFig) const
{
  CompositeFigure newFig(*this);
  newFig.merge(comFig);
  return newFig;
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::merge(khasnulin::CompositeFigure &&comFig) const
{
  CompositeFigure newFig(*this);
  newFig.merge(std::move(comFig));
  return newFig;
}

void khasnulin::CompositeFigure::premerge(const CompositeFigure &comFig)
{
  if (!isSameAddr(comFig))
  {
    figures.merge(comFig.figures, 0);
  }
}

void khasnulin::CompositeFigure::premerge(CompositeFigure &&comFig)
{
  if (!isSameAddr(comFig))
  {
    figures.moveMerge(std::move(comFig.figures), 0);
  }
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::premerge(const CompositeFigure &comFig) const
{
  CompositeFigure newFig(*this);
  newFig.premerge(comFig);
  return newFig;
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::premerge(CompositeFigure &&comFig) const
{
  CompositeFigure newFig(*this);
  newFig.premerge(std::move(comFig));
  return newFig;
}

void khasnulin::CompositeFigure::mergeAt(const CompositeFigure &comFig, size_t pos)
{
  if (!isSameAddr(comFig))
  {
    figures.merge(comFig.figures, pos);
  }
}

void khasnulin::CompositeFigure::mergeAt(CompositeFigure &&comFig, size_t pos)
{
  if (!isSameAddr(comFig))
  {
    figures.moveMerge(std::move(comFig.figures), pos);
  }
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::mergeAt(const CompositeFigure &comFig,
                                                               size_t pos) const
{
  CompositeFigure newFig(*this);
  newFig.mergeAt(comFig, pos);
  return newFig;
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::mergeAt(CompositeFigure &&comFig, size_t pos) const
{
  CompositeFigure newFig(*this);
  newFig.mergeAt(std::move(comFig), pos);
  return newFig;
}

void khasnulin::CompositeFigure::merge()
{
  figures.merge();
}

khasnulin::CompositeFigure khasnulin::CompositeFigure::merge() const
{
  CompositeFigure newFigure(*this);
  newFigure.merge();
  return newFigure;
}
