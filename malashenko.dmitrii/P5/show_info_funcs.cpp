#include "show_info_funcs.hpp"
#include "general_funcs.hpp"

namespace malashenko {
  point_t * getCordsOfFrame(const rectangle_t & frame)
  {
    point_t * cords = new point_t[4];
    cords[0] = {frame.pos.x - (frame.width / 2), frame.pos.y - (frame.height / 2)};
    cords[1] = {frame.pos.x - (frame.width / 2), frame.pos.y + (frame.height / 2)};
    cords[2] = {frame.pos.x + (frame.width / 2), frame.pos.y - (frame.height / 2)};
    cords[3] = {frame.pos.x + (frame.width / 2), frame.pos.y + (frame.height / 2)};
    return cords;
  }

  point_t * extend(point_t * oldTops, const point_t * topsToAdd, size_t & len, size_t k)
  {
    point_t * newTops = new point_t[len + k];

    for (size_t i = 0; i < len; ++i) {
      newTops[i] = oldTops[i];
    }
    for (size_t i = 0; i < k; ++i) {
      newTops[len + i] = topsToAdd[i];
    }
    delete[] oldTops;
    len += k;
    return newTops;
  }


  void showInfo(const Shape * const * figures, size_t len)
  {
    std::cout << "INFO ABOUT FIGURES:\n";
    double fullSum = 0;
    size_t topsLen = 0;
    point_t * tops = new point_t[topsLen];

    for (size_t i = 0; i < len; ++i) {
      double figureArea = figures[i] -> getArea();
      rectangle_t figureFrameRect = figures[i] -> getFrameRect();
      point_t * frameCords = getCordsOfFrame(figureFrameRect);

      tops = extend(tops, frameCords, topsLen, 4);

      fullSum += figureArea;

      std::cout << "Area of figure №" << i + 1 << ":" << figureArea << "\n";
      std::cout << "Frame coordinates of figure №" << i + 1 << ":\n";

      for (size_t i = 0; i < 4; ++i) {
        std::cout << "\t(" << frameCords[i].x << ", " << frameCords[i].y << ")\n";
      }

      delete[] frameCords;
    }
    std::cout << "\n";
    std::cout << "Total area of all figure: " << fullSum << "\n";

    rectangle_t figgureFrame = generalGetFrameRect(tops, topsLen);
    point_t * allFrameCords = getCordsOfFrame(figgureFrame);

    std::cout << "Frame coordinates of all figures:\n";

    for (size_t i = 0; i < 4; ++i) {
      std::cout << "\t(" << allFrameCords[i].x << ", " << allFrameCords[i].y << ")\n";
    }

    delete[] allFrameCords;
    delete[] tops;
  }
}
