#include "matrix_actions.hpp"
#include <algorithm>

void khasnulin::lftBotClk(int *arr, size_t n, size_t m)
{
  if (n > 0 && m > 0)
  {
    size_t currI = (n - 1) * m;

    int directionI = -1;
    int directionJ = 0;
    int factor = 1;
    size_t spiral_circle = 0;
    size_t elem_counter = 0;
    for (size_t i = 0; i < n * m; i++)
    {
      arr[currI] -= factor;
      factor++;
      elem_counter++;
      if (directionI && elem_counter == (n - spiral_circle))
      {
        if (directionI == -1)
        {
          directionJ = 1;
        }
        else
        {
          directionJ = -1;
        }
        spiral_circle++;
        elem_counter = 0;
        directionI = 0;
      }
      else if (directionJ && elem_counter == (m - spiral_circle))
      {
        if (directionJ == -1)
        {
          directionI = -1;
        }
        else
        {
          directionI = 1;
        }
        elem_counter = 0;
        directionJ = 0;
      }
      currI += directionI * m + directionJ;
    }
  }
}

bool khasnulin::lwrTriMtx(const int *arr, size_t n, size_t m)
{
  size_t minSide = std::min(n, m);
  if (minSide == 0)
  {
    return false;
  }
  for (size_t i = 0; i < minSide; i++)
  {
    for (size_t j = i + 1; j < m; j++)
    {
      if (arr[i * m + j] != 0)
      {
        return false;
      }
    }
  }

  return true;
}
