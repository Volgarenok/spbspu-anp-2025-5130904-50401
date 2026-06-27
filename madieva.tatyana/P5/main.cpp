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
    void scale(double ratio);
    virtual ~Shape() = default;
  protected:
    virtual void doScale(double ratio) = 0;
  };
  class Rectangle: public Shape {
    double width_;
    double height_;
    point_t centre_;
  public:
    Rectangle(double width, double height, point_t centre);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(point_t a) override;
    void move(double dx, double dy) override;
    ~Rectangle() = default;
  protected:
    void doScale(double ratio) override;
  };
  class Bubble: public Shape {
    double radius_;
    point_t bottom_;
  public:
    Bubble(double radius, point_t bottom);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(point_t a) override;
    void move(double dx, double dy) override;
    ~Bubble() = default;
  protected:
    void doScale(double ratio) override;
  };
  class Ring: public Shape {
    double big_radius_;
    double small_radius_;
    point_t centre_;
  public:
    Ring(double radius1, double radius2, point_t centre);
    double getArea() override;
    rectangle_t getFrameRect() override;
    void move(point_t a) override;
    void move(double dx, double dy) override;
    ~Ring() = default;
  protected:
    void doScale(double ratio) override;
  };

  const double pi = 3.14;
  void Shape::scale(double ratio) {
    if (ratio <= 0) {
      throw std::invalid_argument("bad argument k for shape");
    }
    doScale(ratio);
  }
  Rectangle::Rectangle(double width, double height, point_t centre):
    Shape(),
    width_(width),
    height_(height),
    centre_(centre)
  {
    if (width_ <= 0 || height_ <= 0) {
      throw std::invalid_argument("Incorrect rectangle size");
    }
  }
  double Rectangle::getArea()
  {
    return width_ * height_;
  }
  rectangle_t Rectangle::getFrameRect()
  {
    return {width_, height_, centre_};
  }
  void Rectangle::move(point_t a)
  {
    centre_ = a;
  }
  void Rectangle::move(double dx, double dy)
  {
    centre_ = {centre_.x + dx, centre_.y + dy};
  }
  void Rectangle::doScale(double ratio)
  {
    width_ = width_ * ratio;
    height_ = height_ * ratio;
  }
  Bubble::Bubble(double radius, point_t bottom):
    Shape(),
    radius_(radius),
    bottom_(bottom)
  {
    if (radius_ <= 0) {
      throw std::invalid_argument("Incorrect bubble size");
    }
  }
  double Bubble::getArea()
  {
    return pi * radius_ * radius_;
  }
  rectangle_t Bubble::getFrameRect()
  {
    point_t centre{bottom_.x, bottom_.y + radius_};
    return {radius_ * 2, radius_ * 2, centre};
  }
  void Bubble::move(point_t a)
  {
    bottom_ = a;
  }
  void Bubble::move(double dx, double dy)
  {
    bottom_ = {bottom_.x + dx, bottom_.y + dy};
  }
  void Bubble::doScale(double ratio)
  {
    point_t centre{bottom_.x, bottom_.y + radius_};
    radius_ *= ratio;
    bottom_ = {centre.x, centre.y - radius_};
  }
  Ring::Ring(double radius1, double radius2, point_t centre_):
    Shape(),
    big_radius_(radius1 > radius2 ? radius1 : radius2),
    small_radius_(radius1 < radius2 ? radius1 : radius2),
    centre_(centre_)
  {
    if (big_radius_ <= 0 || small_radius_ <= 0 || big_radius_ == small_radius_) {
      throw std::invalid_argument("Incorrect ring size");
    }
  }
  double Ring::getArea()
  {
    double big_area = pi * big_radius_ * big_radius_;
    double small_area = pi * small_radius_ * small_radius_;
    return big_area - small_area;
  }
  rectangle_t Ring::getFrameRect()
  {
    return {big_radius_ * 2, big_radius_ * 2, centre_};
  }
  void Ring::move(point_t a)
  {
    centre_ = a;
  }
  void Ring::move(double dx, double dy)
  {
    centre_ = {centre_.x + dx, centre_.y + dy};
  }
  void Ring::doScale(double ratio)
  {
    big_radius_ *= ratio;
    small_radius_ *= ratio;
  }

  rectangle_t totalGetFrameRect(Shape * const * const array, size_t size)
  {
    rectangle_t frame1 = array[0]->getFrameRect();
    double minx = frame1.pos.x - (frame1.width / 2);
    double maxx = frame1.pos.x + (frame1.width / 2);
    double miny = frame1.pos.y - (frame1.height / 2);
    double maxy = frame1.pos.y + (frame1.height / 2);
    for (size_t i = 1; i < size; ++i) {
      rectangle_t frame = array[i]->getFrameRect();
      double left_x = frame.pos.x - (frame.width / 2);
      double right_x = frame.pos.x + (frame.width / 2);
      double bottom_y = frame.pos.y - (frame.height / 2);
      double top_y = frame.pos.y + (frame.height / 2);
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

  void print(std::ostream & cout, Shape * const * const array, size_t size)
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
    if (k <= 0) {
      throw std::invalid_argument("bad argument k");
    }
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
  } catch (const std::invalid_argument & e) {
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
  std::cout << "\n";
  std::cout << "BEFORE SCALING\n\n";
  madieva::print(std::cout, array, size);
  std::cout << "\n";
  try {
    madieva::scalingFromAPoint(array, size, a, k);
  } catch (const std::invalid_argument & e) {
    std::cerr << e.what() << "\n";
    for (size_t i = 0; i < size; ++i) {
      delete array[i];
    }
    return 1;
  }
  std::cout << "AFTER SCALING\n\n";
  madieva::print(std::cout, array, size);
  for (size_t i = 0; i < size; ++i) {
    delete array[i];
  }
  return 0;
}
