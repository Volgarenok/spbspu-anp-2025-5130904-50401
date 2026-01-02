struct point_t {
  double x;
  double y;
};
struct rectangle_t {
  double width;
  double height;
  point_t pos;
};
class Shape {
  public:
  virtual double getArea() = 0;
  virtual rectangle_t getFrameRect() = 0;
  virtual void move(point_t a) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double ratio) = 0;
  virtual ~Shape() = default;
};
class Rectangle: Shape {
  double width;
  double height;
  point_t pos;
  public:
  Rectangle(double width_, double height_, point_t pos_);
  double getArea() override;
  rectangle_t getFrameRect() override;
  void move(point_t a) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;
  ~Rectangle() = default;
};
// class Bubble: Shape {
//   public:
//   double getArea() override;
//   rectangle_t getFrameRect() override;
//   void move() override;
//   void move() override;
//   void scale() override;
//   ~Bubble() = default;
// };
// class Ring: Shape {
//   public:
//   double getArea() override;
//   rectangle_t getFrameRect() override;
//   void move() override;
//   void move() override;
//   void scale() override;
//   ~Ring() = default;
// };
Rectangle::Rectangle(double width_, double height_, point_t pos_):
  width(width), height(height), pos(pos_)
{}
double Rectangle::getArea()
{
  return width * height;
}
rectangle_t Rectangle::getFrameRect()
{

  rectangle_t frame{width, height, pos};
  return frame;
}
void Rectangle::move(point_t a)
{
  pos = a;
}
void Rectangle::move(double dx, double dy)
{
  pos = {pos.x + dx, pos.y + dy};
}
void Rectangle::scale(double ratio)
{
  width = width * ratio;
  height = height * ratio;
}





int main()
{}
