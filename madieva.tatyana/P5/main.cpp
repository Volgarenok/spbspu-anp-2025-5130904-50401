#include <iostream>
namespace madieva {
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
  class Rectangle: public Shape {
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
  class Bubble: public Shape {
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
  class Ring: public Shape {
    double big_radius;
    double small_radius;
    point_t centre;
    public:
    Ring(double radius1, double radius2, point_t centre_);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(point_t a) override;
    void move(double dx, double dy) override;
    void scale(double ratio) override;
    ~Ring() = default;
  };
  const double pi = 3.14;
  Rectangle::Rectangle(double width_, double height_, point_t centre_):
    Shape(), width(width_), height(height_), centre(centre_)
  {
    if (width <= 0 || height <= 0) {
      throw std::invalid_argument("Incorrect rectangle size");
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
    width = width * ratio;
    height = height * ratio;
  }
  Bubble::Bubble(double radius_, point_t bottom_):
    Shape(), radius(radius_), bottom(bottom_)
  {
    if (radius <= 0) {
      throw std::invalid_argument("Incorrect bubble size");
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
    point_t centre{bottom.x, bottom.y + radius};
    radius *= ratio;
    bottom = {centre.x, centre.y - radius};
  }
  Ring::Ring(double radius1, double radius2, point_t centre_):
    Shape(),
    big_radius(radius1 > radius2 ? radius1 : radius2),
    small_radius(radius1 < radius2 ? radius1 : radius2),
    centre(centre_)
  {
    if (big_radius <= 0 || small_radius <= 0 || big_radius == small_radius) {
      throw std::invalid_argument("Incorrect ring size");
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
    big_radius *= ratio;
    small_radius *= ratio;
  }

  rectangle_t totalGetFrameRect(Shape * const * const array, size_t size)
  {
    double width = array[0]->getFrameRect().width;
    double height = array[0]->getFrameRect().height;
    double posx = array[0]->getFrameRect().pos.x;
    double posy = array[0]->getFrameRect().pos.y;
    double left_x = posx - (width / 2);
    double right_x = posx + (width / 2);
    double bottom_y = posy - (height / 2);
    double top_y = posy + (height / 2);
    double minx = left_x;
    double maxx = right_x;
    double miny = bottom_y;
    double maxy = top_y;
    for (size_t i = 0; i < size; ++i) {
      width = array[i]->getFrameRect().width;
      height = array[i]->getFrameRect().height;
      posx = array[i]->getFrameRect().pos.x;
      posy = array[i]->getFrameRect().pos.y;
      left_x = posx - (width / 2);
      right_x = posx + (width / 2);
      bottom_y = posy - (height / 2);
      top_y = posy + (height / 2);
      if (left_x < minx) {
        minx = left_x;
      }
      if (right_x > maxx) {
        maxx = right_x;
      }
      if (bottom_y < miny) {
        miny = bottom_y;
      }
      if (top_y > maxy) {
        maxy = top_y;
      }
    }
    return {maxx - minx, maxy - miny, {(maxx + minx) / 2, (maxy + miny) / 2}};
  }

  void print(std::ostream &cout, Shape * const * const array, size_t size)
  {
    cout << "Area rectangle: " << array[0]->getArea() << "\n";
    rectangle_t frame = array[0]->getFrameRect();
    cout << "rectangle frame width: " << frame.width << "\n";
    cout << "rectangle frame height: " << frame.height << "\n";
    cout << "rectangle frame position (x): " << frame.pos.x << "\n";
    cout << "rectangle frame position (y): " << frame.pos.y << "\n";
    cout << "\n";

    cout << "Area bubble: " << array[1]->getArea() << "\n";
    frame = array[1]->getFrameRect();
    cout << "bubble frame width: " << frame.width << "\n";
    cout << "bubble frame height: " << frame.height << "\n";
    cout << "bubble frame position (x): " << frame.pos.x << "\n";
    cout << "bubble frame position (y): " << frame.pos.y << "\n";
    cout << "\n";

    cout << "Area ring: " << array[2]->getArea() << "\n";
    frame = array[2]->getFrameRect();
    cout << "ring frame width: " << frame.width << "\n";
    cout << "ring frame height: " << frame.height << "\n";
    cout << "ring frame position (x): " << frame.pos.x << "\n";
    cout << "ring frame position (y): " << frame.pos.y << "\n";
    cout << "\n";

    cout << "total area: " << array[0]->getArea() + array[1]->getArea() + array[2]->getArea() << "\n";
    frame = totalGetFrameRect(array, size);
    cout << "total frame width: " << frame.width << "\n";
    cout << "total frame height: " << frame.height << "\n";
    cout << "total frame position (x): " << frame.pos.x << "\n";
    cout << "total frame position (y): " << frame.pos.y << "\n";
  }
  void scalingFromAPoint(Shape * const * const array, size_t size, point_t a, double k)
  {
    for (size_t i = 0; i < size; ++i) {
      rectangle_t frame = array[i]->getFrameRect();
      double dx = frame.pos.x - a.x;
      double dy = frame.pos.y - a.y;
      array[i]->move(a);
      array[i]->scale(k);
      dx *= k;
      dy *= k;
      array[i]->move(dx, dy);
    }
  }
}

int main()
{
  const size_t size = 3;
  if (size == 0) {
    std::cerr << "a bad number of shapes\n";
    return 1;
  }
  madieva::Shape * array[size] = {};
  try {
    array[0] = new madieva::Rectangle(5, 6, {2, 5});
    array[1] = new madieva::Bubble(5, {7, 7});
    array[2] = new madieva::Ring(6, 2, {8, 15});
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << "\n";
    for (size_t i = 0; i < size; ++i) {
      delete array[i];
    }
    return 1;
  }
  double x = 0;
  double y = 0;
  madieva::point_t a = {0, 0};
  double k = 0;
  std::cout << "to scale relative to a point, enter the following data\n";
  std::cout << "enter x: ";
  if (!(std::cin >> x)) {
    std::cerr << "bad argument x\n";
    for (size_t i = 0; i < size; ++i) {
      delete array[i];
    }
    return 1;
  }
  std::cout << "\nenter y: ";
  if (!(std::cin >> y)) {
    std::cerr << "bad argument y\n";
    for (size_t i = 0; i < size; ++i) {
      delete array[i];
    }
    return 1;
  }
  a = {x, y};
  std::cout << "\nenter a positive coefficient: ";
  if (!(std::cin >> k)) {
    std::cerr << "bad argument k\n";
    for (size_t i = 0; i < size; ++i) {
     delete array[i];
    }
    return 1;
  }
  if (k <= 0) {
    std::cerr << "the coefficient cannot be equal to or less than zero\n";
    return 1;
  }
  std::cout << "\n";
  std::cout << "BEFORE SCALING\n\n";
  madieva::print(std::cout, array, size);
  std::cout << "\n";
  madieva::scalingFromAPoint(array, size, a, k);
  std::cout << "AFTER SCALING\n\n";
  madieva::print(std::cout, array, size);
  for (size_t i = 0; i < size; ++i) {
    delete array[i];
  }
  return 0;
}
