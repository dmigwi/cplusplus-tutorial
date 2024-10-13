#include <iostream>
#include <string>
#include <string_view>

class MyString
{
    public:
        explicit MyString(std::string_view word={})
            : m_word {word}
        {}

        MyString operator()(std::size_t start, std::size_t count)
        {
            return MyString { m_word.substr(start, count)};
        }

        friend std::ostream& operator<<(std::ostream& out, const MyString& val);

    private:
        std::string_view m_word{};
};

std::ostream& operator<<(std::ostream& out, const MyString& val)
{
    out << val.m_word;
    return out;
}

int main()
{
    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters

    return 0;
}