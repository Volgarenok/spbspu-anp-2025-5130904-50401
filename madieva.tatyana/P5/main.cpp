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
  point_t centre;
  public:
  Rectangle(double width_, double height_, point_t centre_);
  double getArea() override;
  rectangle_t getFrameRect() override;
  void move(point_t a) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;
  ~Rectangle() = default;
};
class Bubble: Shape {
  double radius;
  point_t bottom;
  public:
  Bubble(double radius_, point_t bottom_);
  double getArea() override;
  rectangle_t getFrameRect() override;
  void move(point_t a) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;
  ~Bubble() = default;
};
class Ring: Shape {
  double big_radius;
  double small_radius;
  point_t centre;
  public:
  Ring(double big_radius_, double small_radius_, point_t centre_);
  double getArea() override;
  rectangle_t getFrameRect() override;
  void move(point_t a) override;
  void move(double dx, double dy) override;
  void scale(double ratio) override;
  ~Ring() = default;
};
static double pi = 3.14;
Rectangle::Rectangle(double width_, double height_, point_t centre_):
  Shape(), width(width_), height(height_), centre(centre_)
{
  if (width <= 0 || height <= 0) {
    throw;
  }
}
double Rectangle::getArea()
{
  return width * height;
}
rectangle_t Rectangle::getFrameRect()
{
  return {width, height, centre};
}
void Rectangle::move(point_t a)
{
  centre = a;
}
void Rectangle::move(double dx, double dy)
{
  centre = {centre.x + dx, centre.y + dy};
}
void Rectangle::scale(double ratio)
{
  if (ratio <= 0) {
    throw;
  }
  width = width * ratio;
  height = height * ratio;
}
Bubble::Bubble(double radius_, point_t bottom_):
  Shape(), radius(radius_), bottom(bottom_)
{
  if (radius <= 0) {
    throw;
  }
}
double Bubble::getArea()
{
  return pi * radius * radius;
}
rectangle_t Bubble::getFrameRect()
{
  point_t centre{bottom.x, bottom.y + radius};
  return {radius * 2, radius * 2, centre};
}
void Bubble::move(point_t a)
{
  bottom = a;
}
void Bubble::move(double dx, double dy)
{
  bottom = {bottom.x + dx, bottom.y + dy};
}
void Bubble::scale(double ratio)
{
  if (ratio <= 0) {
    throw;
  }
  point_t centre{bottom.x, bottom.y + radius};
  radius *= ratio;
  bottom = {centre.x, centre.y - radius};
}
Ring::Ring(double big_radius_, double small_radius_, point_t centre_):
  Shape(), big_radius(big_radius_), small_radius(small_radius_), centre(centre_)
{
  if (big_radius <= 0 || small_radius <= 0) {
    throw;
  }
}
double Ring::getArea()
{
  double big_area = pi * big_radius * big_radius;
  double small_area = pi * small_radius * small_radius;
  return big_area - small_area;
}
rectangle_t Ring::getFrameRect()
{
  return {big_radius * 2, big_radius * 2, centre};
}
void Ring::move(point_t a)
{
  centre = a;
}
void Ring::move(double dx, double dy)
{
  centre = {centre.x + dx, centre.y + dy};
}
void Ring::scale(double ratio)
{
  if (ratio <= 0) {
    throw;
  }
  big_radius *= ratio;
  small_radius *= ratio;
}



int main()
{}
