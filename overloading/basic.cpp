#include <iostream>
#include <numeric> // for std::gcd

class Fraction
{
    public:
        Fraction(int numerator=0, int denominator=1)
            : m_numerator {numerator}, m_denominator {denominator}
            {
                int divisor { std::gcd(m_numerator, m_denominator) };
                if (divisor > 0)
                {
                    m_numerator /= divisor;
                    m_denominator /= divisor;
                }
            }

        void print() const
        {
            std::cout << m_numerator << "/" << m_denominator << '\n';
        }

        friend Fraction operator*(const Fraction& f1, const Fraction& f2);
        friend Fraction operator*(const Fraction& f, int value);
        friend Fraction operator*(int value, const Fraction& f);

        friend std::ostream& operator<< (std::ostream& out, const Fraction& f);
        friend std::istream& operator>> (std::istream& in, Fraction& f);

        friend bool operator== (const Fraction& f1, const Fraction& f2);
        friend bool operator!= (const Fraction& f1, const Fraction& f2);
        friend bool operator> (const Fraction& f1, const Fraction& f2);
        friend bool operator< (const Fraction& f1, const Fraction& f2);
        friend bool operator>= (const Fraction& f1, const Fraction& f2);
        friend bool operator<= (const Fraction& f1, const Fraction& f2);
    
    private:
        int m_numerator{};
        int m_denominator{};
};

Fraction operator*(const Fraction& f1, const Fraction& f2) 
{
    int numerator { f1.m_numerator * f2.m_numerator};
    int denominator { f1.m_denominator * f2.m_denominator};
    return Fraction {numerator, denominator};
}

Fraction  operator*(const Fraction& f, int value)
{
    return f * Fraction{value};
}

Fraction  operator*(int value, const Fraction& f)
{
    return  f * Fraction{value};
}

std::ostream& operator<< (std::ostream& out, const Fraction& f)
{
    out << f.m_numerator << "/" << f.m_denominator;
    return out;
}

std::istream& operator>> (std::istream& in, Fraction& f)
{
    [[maybe_unused]] char input{};
    in >> f.m_numerator >> input >> f.m_denominator;
    if (!in)
        f = {};
    return in;
}

bool operator== (const Fraction& f1, const Fraction& f2)
{
   return (f1.m_numerator==f2.m_numerator) && 
            (f1.m_denominator==f2.m_denominator); 
}

bool operator!= (const Fraction& f1, const Fraction& f2)
{
    return !(operator==(f1, f2)); 
}

bool operator> (const Fraction& f1, const Fraction& f2)
{
    // return (static_cast<double>(f1.m_numerator)/f1.m_denominator > 
    //          static_cast<double>(f2.m_numerator)/f2.m_denominator); 
    return (f1.m_numerator * f2.m_denominator > f2.m_numerator * f1.m_denominator);
}

bool operator< (const Fraction& f1, const Fraction& f2)
{
    return operator>(f2, f1); 
}

bool operator>= (const Fraction& f1, const Fraction& f2)
{
 return operator<(f2, f1); 
}

bool operator<= (const Fraction& f1, const Fraction& f2)
{
 return operator>(f2, f1);
}

int main()
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    Fraction f7{0, 6};
    f7.print();

    Fraction f11{};
	std::cout << "Enter fraction 1: ";
	std::cin >> f11;

	Fraction f21{};
	std::cout << "Enter fraction 2: ";
	std::cin >> f21;

	std::cout << f11 << " * " << f21 << " is " << f11 * f21 << '\n'; // note: The result of f1 * f2 is an r-value

    Fraction f111{ 3, 2 };
	Fraction f211{ 5, 8 };

    std::cout << f111 << ((f111 == f211) ? " == " : " not == ") << f211 << '\n';
	std::cout << f111 << ((f111 != f211) ? " != " : " not != ") << f211 << '\n';
	std::cout << f111 << ((f111 < f211) ? " < " : " not < ") << f211 << '\n';
	std::cout << f111 << ((f111 > f211) ? " > " : " not > ") << f211 << '\n';
	std::cout << f111 << ((f111 <= f211) ? " <= " : " not <= ") << f211 << '\n';
	std::cout << f111 << ((f111 >= f211) ? " >= " : " not >= ") << f211 << '\n';

    return 0;
}