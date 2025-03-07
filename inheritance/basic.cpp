#include <iostream>
#include <string>
#include <string_view>

class Fruit
{
    public:
        Fruit(std::string_view name, std::string_view color)
            : m_name {name}, m_color {color}
        {}

        std::string getName() const { return m_name; }
        std::string getColor() const { return m_color; }
    
    private:
        const std::string m_name;
        const std::string m_color;

};

class Apple : public Fruit
{
    public:
        Apple(std::string_view color, double fiber = 4.7)
            : Fruit{"Apple", color}, m_fiber {fiber}
        {}

        friend std::ostream& operator<< (std::ostream& out , const Apple& a)
        {
            out << " Apple (" << a.getName() <<", " << a.getColor() << ", " << a.m_fiber <<")\n";
            return out;
        }
    
    protected:
       Apple(std::string_view name, std::string_view color, double fiber = 4.7)
            : Fruit{name, color}, m_fiber {fiber}
        {}

    private:
        double m_fiber;
};

class Banana : public Fruit
{
    public:
        Banana(std::string_view color = "yellow")
            : Fruit{ "Banana", color}
        {}

        friend std::ostream& operator<< (std::ostream& out, const Banana& b)
        {
            out << "Banana (" << b.getName() << ", " << b.getColor() << ")\n";
            return out;
        }

};

class GrannySmith : public Apple
{
    public:
        GrannySmith()
        : Apple {"granny smith apple", "green"} 
        {}
};

int main()
{
	Apple a{ "red" };
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}