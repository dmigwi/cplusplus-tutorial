#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Point
{
private:
	int m_x{};
	int m_y{};

public:
	Point(int x, int y)
		: m_x{ x }, m_y{ y }
	{}

	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
	}
};

class Shape
{
    public:
        friend std::ostream& operator<< (std::ostream& out, const Shape& shape)
        {
            return shape.print(out);
        }

        virtual std::ostream& print(std::ostream& out) const = 0;

        virtual ~Shape() = default;
};

class Circle : public Shape
{
    public:
        Circle(Point center, int radius)
            : m_center {center}, m_radius {radius}
        {}

        std::ostream& print(std::ostream& out) const override
        {
            out << "Circle(" << m_center << " , radius " << m_radius << ").\n";
            return out;
        }

        int getRadius() const { return m_radius; };

    private:
        Point m_center;
        int m_radius;
};

class Triangle : public Shape
{
    public:
        Triangle(Point p1, Point p2, Point p3)
            : m_p1 {p1}, m_p2{p2}, m_p3{p3}
        {}

        std::ostream& print(std::ostream& out) const override
        {
            out << "Triangle(" << m_p1 << " , " << m_p2 << ", " << m_p3 <<").\n";
            return out;
        }

    private:
        Point m_p1;
        Point m_p2;
        Point m_p3;
};

int getLargestRadius(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    int largestRadius {0};
    for (const auto& item : shapes)
    {
        auto c {dynamic_cast<Circle*>(item.get())};

        if (c)
            largestRadius = std::max( largestRadius, c->getRadius());
    }
    return largestRadius;
}

int main()
{
	std::vector<std::unique_ptr<Shape>> v{};
    v.reserve(3);

    v.emplace_back(new Circle {Point{ 1, 2 }, 7});
    v.emplace_back(new Triangle {Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }});
    v.emplace_back(new Circle {Point{ 7, 8 }, 3});

	// print each shape in vector v on its own line here
    for (const auto& item : v)
    {
        std::cout << *item;
    }

	std::cout << "\nThe largest radius is: " << getLargestRadius(v) << '\n'; // write this function

	// delete each element in the vector here
    // for (auto item : v)
    // {
    //     delete item;
    // }

	return 0;
}