#include "composite_figure.hpp"

void khasnulin::CompositeFigure::merge(const CompositeFigure &compFigure)
{
  if (!isSameAddr(compFigure))
  {
    figures.merge(compFigure.figures, compFigure.size());
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