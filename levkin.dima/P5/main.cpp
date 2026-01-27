#include <iostream>

namespace levkin {
  double abs(double x) { return (x >= 0) ? x : -x; }
  struct point_t {
    double x, y;
  };
  struct rectangle_t {
    double width, height;
    point_t pos;
  };
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t dest) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
  };

  class Rectangle : public Shape
  {
    rectangle_t data_fields;

  public:
    Rectangle(point_t center, double width, double height)
        : data_fields{width, height, center}
    {
    }
    double getArea() const override
    {
      return data_fields.height * data_fields.width;
    }
    virtual rectangle_t getFrameRect() const override { return data_fields; }
    virtual void move(point_t dest) override
    {
      data_fields.pos = {dest.x, dest.y};
    }
    virtual void move(double dx, double dy) override
    {
      move({data_fields.pos.x + dx, data_fields.pos.y + dy});
    }
    virtual void scale(double k) override
    {
      data_fields.width *= k;
      data_fields.height *= k;
    }
  };

  class Diamond : public Shape
  {
    rectangle_t data_fields;

  public:
    Diamond(point_t center, double width, double height)
        : data_fields{width, height, center}
    {
    }
    double getArea() const override
    {
      return .5 * data_fields.height * data_fields.width;
    }
    virtual rectangle_t getFrameRect() const override { return data_fields; }
    virtual void move(point_t dest) override
    {
      data_fields.pos = {dest.x, dest.y};
    }
    virtual void move(double dx, double dy) override
    {
      move({data_fields.pos.x + dx, data_fields.pos.y + dy});
    }
    virtual void scale(double k) override
    {
      data_fields.width *= k;
      data_fields.height *= k;
    }
  };

  class Polygon : public Shape
  {
    point_t* points;
    size_t len;
    point_t anchor = {0, 0};

  public:
    Polygon(point_t* points, size_t len) : points(points), len(len) {}
    double getArea() const override
    {
      double area = .0;
      for (size_t i = 0; i < len; ++i)
      {
        const point_t& p1 = points[i];
        const point_t& p2 = points[(1 + i) % len];
        area += (p1.x * p2.y) - (p2.x * p1.y);
      }
      return abs(area) / 2.0;
    }
    virtual rectangle_t getFrameRect() const override
    {
      if (len == 0)
      {
        return {0, 0, {0, 0}};
      }

      double min_x = points[0].x;
      double max_x = points[0].x;
      double min_y = points[0].y;
      double max_y = points[0].y;

      for (size_t i = 1; i < len; ++i)
      {
        const point_t& point = points[i];
        if (point.x < min_x)
        {
          min_x = point.x;
        } else
        {
          max_x = point.x;
        }
        if (point.y < min_y)
        {
          min_y = point.y;
        } else
        {
          max_y = point.y;
        }
      }
      double width = max_x - min_x;
      double height = max_y - min_y;
      point_t center = {min_x + width / 2, min_y + height / 2};
      return {width, height, center};
    }
    virtual void move(point_t dest) override
    {
      double dx = dest.x - anchor.x;
      double dy = dest.y - anchor.y;
      move(dx, dy);
    }
    virtual void move(double dx, double dy) override
    {
      for (size_t i = 0; i < len; ++i)
      {
        point_t& point = points[i];
        point.x += dx;
        point.y += dy;
      }
      anchor.x += dx;
      anchor.y += dy;
    }
    virtual void scale(double k) override
    {
      if (k <= 0.0 || len == 0)
      {
        return;
      }
      point_t center = find_center();
      for (size_t i = 0; i < len; ++i)
      {
        points[i].x = center.x + (points[i].x - center.x) * k;
        points[i].y = center.y + (points[i].y - center.y) * k;
      }
    }
    ~Polygon() { delete points; }
    Polygon(const Polygon& poly) = default;
    Polygon(Polygon&& poly) = default;
    Polygon& operator=(const Polygon& poly) = default;
    Polygon& operator=(Polygon&& poly) = default;

    point_t find_center() const
    {
      if (len == 0)
      {
        return {0, 0};
      }

      double area = getArea();
      if (area == 0)
      {
        return {0, 0};
      }

      double cx = 0.0;
      double cy = 0.0;

      for (size_t i = 0; i < len; ++i)
      {
        const point_t& p1 = points[i];
        const point_t& p2 = points[(i + 1) % len];

        double cross = (p1.x * p2.y) - (p2.x * p1.y);
        cx += (p1.x + p2.x) * cross;
        cy += (p1.y + p2.y) * cross;
      }

      cx /= (6.0 * area);
      cy /= (6.0 * area);

      return {cx, cy};
    }
  };

  void isotropicly_scale(Shape& shape, point_t anchor, double factor)
  {
    if (factor <= 0.0)
    {
      return;
    }
    rectangle_t frame = shape.getFrameRect();
    point_t init_pos = frame.pos;

    double dx = init_pos.x - anchor.x;
    double dy = init_pos.y - anchor.y;

    shape.move(anchor);
    shape.scale(factor);
    shape.move({anchor.x + dx * factor, anchor.y + dy * factor});
  }

  void printState(Shape** shapes, size_t count)
  {
    double totalArea = 0;
    double minX = 1e30, minY = 1e30, maxX = -1e30, maxY = -1e30;

    for (size_t i = 0; i < count; ++i)
    {
      double area = shapes[i]->getArea();
      rectangle_t frame = shapes[i]->getFrameRect();
      totalArea += area;

      std::cout << "shape: " << i + 1 << " area: " << std::fixed << area
                << "\n";
      std::cout << "framerect: w=" << frame.width << " h=" << frame.height
                << "pos=(" << frame.pos.x << "," << frame.pos.y << ")\n";

      minX = std::min(minX, frame.pos.x - frame.width / 2);
      minY = std::min(minY, frame.pos.y - frame.height / 2);
      maxX = std::max(maxX, frame.pos.x + frame.width / 2);
      maxY = std::max(maxY, frame.pos.y + frame.height / 2);
    }
    std::cout << "total area: " << totalArea << "\n";
    std::cout << "global frame: (" << minX << "," << minY << ") to (" << maxX
              << "," << maxY << ")\n";
  }

}

int main()
{
  const size_t count = 3;
  levkin::Shape** shapes = new levkin::Shape*[count];

  shapes[0] = new levkin::Rectangle({0, 0}, 10, 10);
  shapes[1] = new levkin::Diamond({10, 10}, 4, 8);
  levkin::point_t tri[] = {{0, 0}, {4, 0}, {0, 3}};
  shapes[2] = new levkin::Polygon(tri, 3);

  std::cout << "init\n";
  levkin::printState(shapes, count);

  std::cout << "\nenter scale point x y and scale factor: ";
  levkin::point_t anchor;
  double factor;

  if (!(std::cin >> anchor.x >> anchor.y >> factor))
  {
    std::cerr << "error: invalid input data format.\n";
    for (size_t i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
    delete[] shapes;
    return 1;
  }

  if (factor <= 0)
  {
    std::cerr << "error: scale factor must be positive.\n";
    for (size_t i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
    delete[] shapes;
    return 2;
  }

  for (size_t i = 0; i < count; ++i)
  {
    levkin::isotropicly_scale(*shapes[i], anchor, factor);
  }

  std::cout << "\nafter scaling:\n";
  levkin::printState(shapes, count);

  delete[] shapes;

  return 0;
}
