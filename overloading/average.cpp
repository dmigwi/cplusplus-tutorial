#include <iostream>
#include <cstdint>

class Average
{
    public:
        explicit Average(std::int32_t val=0)
            : m_val {val}
            {}
        
        Average(const Average& avg)
        {
            if (*this != avg)
            {
                m_val = avg.m_val;
                m_counter = avg.m_counter;
            } 
        }

        Average& operator+= (std::int32_t val)
        {
            m_val += val;
            ++m_counter;
            return *this;
        }

        friend bool operator!= (const Average& a, const Average& b)
        {
            return a.m_val != b.m_val;
        }

        friend std::ostream& operator<< (std::ostream& out, const Average& avg)
        {
            out << ((avg.m_counter == 0) ? 0 : static_cast<double>(avg.m_val)/avg.m_counter);
            return out;
        }

    private:
        std::int32_t m_val {};
        std::int32_t m_counter{0};
};

int main()
{
	Average avg{};
	std::cout << avg << '\n';

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}