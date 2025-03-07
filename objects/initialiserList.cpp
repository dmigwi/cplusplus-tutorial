#include <iostream>
#include <algorithm>
#include <initializer_list>

class IntArray
{
    public:
        IntArray() = default;

        IntArray(int length)
            : m_length {length},
                m_data {new int [static_cast<std::size_t>(length)] {}}
            {}

        IntArray(std::initializer_list<int> data)
            : IntArray (static_cast<int>(data.size()))
        {
            std::copy(data.begin(), data.end(), m_data);
        }

        ~IntArray()
        {
            delete[] m_data;
        }

        int operator[] (int index)
        {
            return *(m_data+index);
            // return m_data[index];
        }

        IntArray& operator= (std::initializer_list<int> newData)
        {
            // If the new list is a different size, reallocate it
            int length { static_cast<int>(newData.size()) };
            if (length != m_length)
            {
                delete[] m_data;
                m_length = length;
                m_data = new int[newData.size()]{};
            }

            std::copy(newData.begin(), newData.end(), m_data);
            return *this;
        }

        int getLength() const { return m_length; }

    private:
        int m_length {};
        int* m_data {};
};

int main()
{
	IntArray array { 5, 4, 3, 2, 1 }; // initializer list
	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	std::cout << '\n';

	array = { 1, 3, 5, 7, 9, 11 };

	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	std::cout << '\n';

	return 0;
}