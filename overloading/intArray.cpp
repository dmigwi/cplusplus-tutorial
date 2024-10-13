#include <iostream>

class IntArray
{
    public:
        explicit IntArray(int length)
            : m_length {(length > 0) ? length : 0} // length must be zero or greater than zero.
        {
            if (length > 0)
                m_data = new int [static_cast<size_t>(length)];
            else
                m_data = nullptr;
        }

        // Copy Constructor
        IntArray(const IntArray& copy)
        {
            if (this != &copy)
                deepCopy(copy);
        }

        ~IntArray()
        {
            delete[] m_data;
        }

        IntArray& operator=(const IntArray& array)
        {
            if (this != &array)
                deepCopy(array);
            return *this;
        }

        friend std::ostream& operator<< (std::ostream& out, const IntArray& val)
        {
            for (int i {0}; i < val.m_length; ++i)
                out << val.m_data[i] << " ";
            return out;
        }

        int& operator[] (int index)
        {
            if (m_length > index)
                return m_data[index];
            else
                return m_unknown;
        }

        void deepCopy(const IntArray& copy)
        {
            delete[] m_data;
            m_length = copy.m_length;

            if (copy.m_length > 0)
            {
                m_data = new int [static_cast<size_t>(copy.m_length)];
                for (int i {0}; i < copy.m_length; ++i)
                    m_data[i] = copy.m_data[i];
            }
            else
                m_data = nullptr;
        }

    private:
        int m_length{0};
        int *m_data {nullptr};
        int m_unknown {-1};
};

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

	return 0;
}