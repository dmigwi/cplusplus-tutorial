#include <iostream>

class Storage; // forward declaration for class Storage

class Display
{
public:
    explicit Display(bool displayIntFirst)
        : m_displayIntFirst {displayIntFirst}
    {}

    // forward declaration for Storage needed for reference here
    void displayStorage(const Storage& storage);
   
    void setDisplayIntFirst(bool b) { m_displayIntFirst = b; }

private:
    bool m_displayIntFirst {};
};

class Storage 
{
public:
    Storage(int storage, double dValue)
        : m_nValue {storage}, m_dValue (dValue)
    {}

    // Make the Display class a friend of Storage
    friend void Display::displayStorage(const Storage& storage);

private:
    int m_nValue {};
    double m_dValue {};
};

 void Display::displayStorage(const Storage& storage)
    {
        if (m_displayIntFirst)
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        else // display double first
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
    }

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };

    display.displayStorage(storage);

    display.setDisplayIntFirst(true);
    display.displayStorage(storage);

    return 0;
}