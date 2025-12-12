#include <iostream>

namespace hvostov {
  struct point_t {
    double x, y;
  };
  struct rectangle_t {
    double width, height;
    point_t pos;
  };
  class Shape {
    public:
      virtual ~Shape() = default;
      virtual double getArea() const = 0;
      virtual rectangle_t getFrameRect() const = 0;
      virtual void move(point_t pos) = 0;
      virtual void move(double x, double y) = 0;
      virtual void scale(double k) = 0;
  };
  class Rectangle: public Shape {
    public:
      Rectangle(double width, double height, point_t pos);
      double getArea() const override;
      rectangle_t getFrameRect() const override;
      void move(point_t pos) override;
      void move(double x, double y) override;
      void scale(double k) override;
    private:
      double width_, height_;
      point_t pos_;
  };
}

hvostov::Rectangle::Rectangle(double width, double height, point_t pos):
  width_(width),
  height_(height),
  pos_(pos)
{}

double hvostov::Rectangle::getArea() const
{
  return width_ * height_;
}

hvostov::rectangle_t hvostov::Rectangle::getFrameRect() const
{
  rectangle_t frame;
  frame.height = height_;
  frame.width = width_;
  frame.pos = pos_;
  return frame;
}

void hvostov::Rectangle::move(point_t pos)
{
  pos_ = pos;
}

void hvostov::Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void hvostov::Rectangle::scale(double k)
{
  width_ *= k;
  height_ *= k;
}

int main()
{}
