#include <cassert>
#include <iostream>
#include <algorithm>
#include <cmath>

class FixedPoint2
{
    public:
        FixedPoint2(std::int16_t integer, std::int16_t fraction)
            : m_base { static_cast<std::int16_t>(std::abs(integer)) }, 
                m_decimal { static_cast<std::int16_t>(std::abs(fraction))}
        {
            if (m_base != integer || m_decimal != fraction)
                 m_signing = -1; // either int or decimal part is negative.

            // if the decimal part is above 99, reduce it to below 100.
            // For every 100 remove from the fractional part, 1 should be added on
            // integer part.
            while (m_decimal > 100)
            {
                m_decimal -= 100;
                m_base += 1;
            } 
        }

        FixedPoint2(double rawVal)
            : FixedPoint2( 
                static_cast<std::int16_t>(std::trunc(rawVal)),
                static_cast<std::int16_t>(std::round(rawVal*100) - std::trunc(rawVal)*100)
                )
        {}

        friend bool operator== (const FixedPoint2& a, const FixedPoint2& b)
        {
            return (a.m_base == b.m_base) && (a.m_decimal == b.m_decimal);
        }

        friend FixedPoint2 operator+ (const FixedPoint2& a, const FixedPoint2& b)
        {
            return FixedPoint2( static_cast<double>(a) + static_cast<double>(b));
        }

        friend std::ostream& operator<< (std::ostream& out, const FixedPoint2& data)
        {
            out << static_cast<double>(data);
            return out;
        }

        friend std::istream& operator>> (std::istream& in, FixedPoint2& data)
        {
            double input{};
            in >> input;

            if (!in)
                in.setstate(in.failbit);
            else 
                data = FixedPoint2{input};
            return in;
        }

        explicit operator double() const
        {
            double integerPart {static_cast<double>(m_base)};
            double fractionalPart {static_cast<double>(m_decimal)};
            fractionalPart = (fractionalPart == 0) ? 0 : (fractionalPart / 100);

            return  (integerPart + fractionalPart) * m_signing;
        }

        FixedPoint2 operator-()
        {
            double val = static_cast<double>(*this);
            return FixedPoint2(-1 * val);
        }

        friend bool testDecimal(const FixedPoint2 &fp);

    private:
        std::int16_t m_base {0};
        std::int16_t m_decimal {0};
        std::int16_t m_signing {1};
};

// You will need to make testDecimal a friend of FixedPoint2
// so the function can access the private members of FixedPoint2
bool testDecimal(const FixedPoint2 &fp)
{
    if (fp.m_base >= 0)
        return fp.m_decimal >= 0 && fp.m_decimal < 100;
    else
        return fp.m_decimal <= 0 && fp.m_decimal > -100;
}

int main()
{
	FixedPoint2 a{ 34, 56 };
	std::cout << a << '\n';
	std::cout << static_cast<double>(a) << '\n';
	assert(static_cast<double>(a) == 34.56);

	FixedPoint2 b{ -2, 8 };
	assert(static_cast<double>(b) == -2.08);

	FixedPoint2 c{ 2, -8 };
	assert(static_cast<double>(c) == -2.08);

	FixedPoint2 d{ -2, -8 };
	assert(static_cast<double>(d) == -2.08);

	FixedPoint2 e{ 0, -5 };
	assert(static_cast<double>(e) == -0.05);

	FixedPoint2 f{ 0, 10 };
	assert(static_cast<double>(f) == 0.1);

    FixedPoint2 g{ 1, 104 };
	std::cout << g << '\n';
	std::cout << static_cast<double>(g) << '\n';
	assert(static_cast<double>(g) == 2.04);
	assert(testDecimal(g));

	FixedPoint2 h{ 1, -104 };
	assert(static_cast<double>(h) == -2.04);
	assert(testDecimal(h));

	FixedPoint2 j{ -1, 104 };
	assert(static_cast<double>(j) == -2.04);
	assert(testDecimal(j));

	FixedPoint2 k{ -1, -104 };
	assert(static_cast<double>(k) == -2.04);
	assert(testDecimal(k));

    FixedPoint2 l{ 0.01 };
	assert(static_cast<double>(l) == 0.01);

	FixedPoint2 m{ -0.01 };
	assert(static_cast<double>(m) == -0.01);

	FixedPoint2 n{ 1.9 }; // make sure we handle single digit decimal
    std::cout << "n :" << n << '\n';
	assert(static_cast<double>(n) == 1.9);

	FixedPoint2 p{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	assert(static_cast<double>(p) == 5.01);

	FixedPoint2 q{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	assert(static_cast<double>(q) == -5.01);

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 r { 106.9978 }; // should be stored with base 107 and decimal 0
	assert(static_cast<double>(r) == 107.0);

	// Handle case where the argument's decimal rounds to -100 (need to decrease base by 1)
	FixedPoint2 s { -106.9978 }; // should be stored with base -107 and decimal 0
	assert(static_cast<double>(s) == -107.0);



    assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // Test equality true
	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

	// Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // both positive, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // both positive, with decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // second negative, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // second negative, possible decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // first negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // first negative, possible decimal overflow

	FixedPoint2 aa{ -0.48 };
	assert(static_cast<double>(aa) == -0.48);
    std::cout << -aa << " >> ";
	assert(static_cast<double>(-aa) == 0.48);

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> aa;
	std::cout << "You entered: " << aa << '\n';
	assert(static_cast<double>(aa) == 5.68);

	return 0;
}