#include "composite_figure.hpp"
#include <utility>

void khasnulin::CompositeFigure::merge(const CompositeFigure &compFigure)
{
  if (!isSameAddr(compFigure))
  {
    figures.merge(compFigure.figures, figures.size());
  }
}

void khasnulin::CompositeFigure::merge(CompositeFigure &&compFigure)
{
  if (!isSameAddr(compFigure))
  {
    figures.moveMerge(std::move(compFigure.figures), figures.size());
  }
}

void khasnulin::CompositeFigure::premerge(const CompositeFigure &compFigure)
{
  if (!isSameAddr(compFigure))
  {
    figures.merge(compFigure.figures, 0);
  }
}

void khasnulin::CompositeFigure::mergeAt(const CompositeFigure &compFigure, size_t pos)
{
  if (!isSameAddr(compFigure))
  {
    figures.merge(compFigure.figures, pos);
  }
}