#include "utils.hpp"
#include <iostream>
zubarev::point_t zubarev::getTopLeft(const rectangle_t& frame)
{
  return {frame.pos.x - frame.width / 2, frame.pos.y + frame.height / 2};
}

zubarev::point_t zubarev::getBottomRight(const rectangle_t& frame)
{
  return {frame.pos.x + frame.width / 2, frame.pos.y - frame.height / 2};
}

void zubarev::scaleAtCertainPnt(Shape* shapes[], size_t size, point_t userPos, double k)
{
  for (size_t i = 0; i < size; i++) {
    point_t lastCenter=shapes[i]->getFrameRect().pos;
    shapes[i]->move(userPos);
    shapes[i]->scale(k);
    shapes[i]->move(lastCenter);
  }
}

zubarev::rectangle_t zubarev::getWholeFrame(Shape* shapes[], size_t size)
{
  rectangle_t frame = shapes[0]->getFrameRect();

  point_t leftTopPt = getTopLeft(frame);
  point_t rightBottomPt = getBottomRight(frame);

  for (size_t i = 1; i < size; i++) {
    frame = shapes[i]->getFrameRect();
    const point_t topLeft = getTopLeft(frame);
    const point_t bottomRight = getBottomRight(frame);

    leftTopPt.x = std::min(leftTopPt.x, topLeft.x);
    leftTopPt.y = std::max(leftTopPt.y, topLeft.y);

    rightBottomPt.x = std::max(rightBottomPt.x, bottomRight.x);
    rightBottomPt.y = std::min(rightBottomPt.y, bottomRight.y);
  }

  rectangle_t allFrame = {};
  allFrame.height = std::abs(leftTopPt.y - rightBottomPt.y);
  allFrame.width = std::abs(leftTopPt.x - rightBottomPt.x);
  allFrame.pos = {leftTopPt.x + allFrame.width / 2, leftTopPt.y - allFrame.height / 2};
  return allFrame;
}

double zubarev::getWholeArea(Shape* shapes[], size_t size)
{
  double sum = 0;
  for (size_t i = 0; i < size; i++) {
    sum += shapes[i]->getArea();
  }
  return sum;
}

void zubarev::printInfo(Shape* shapes[], size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    std::cout << "Figure " << i + 1 << '\n';

    rectangle_t frame = shapes[i]->getFrameRect();
    std::cout << "Area: " << shapes[i]->getArea() << '\n';
    std::cout << "Frame width: " << frame.width << '\n';
    std::cout << "Frame height: " << frame.height << '\n';
    std::cout << "Frame center: " << frame.pos.x << " " << frame.pos.y << '\n';
    std::cout << '\n';
  }

  std::cout << "All\n";
  rectangle_t allFrame = getWholeFrame(shapes, size);
  std::cout << "Whole area: " << getWholeArea(shapes, size) << '\n';
  std::cout << "Whole frame width: " << allFrame.width << '\n';
  std::cout << "Whole frame height: " << allFrame.height << '\n';
  std::cout << "Whole frame center: " << allFrame.pos.x << " " << allFrame.pos.y << '\n';
  std::cout << '\n';
}
