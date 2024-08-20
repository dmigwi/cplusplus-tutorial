#include <iostream>
#include <string_view>
#include <limits>

struct AdvertsInfo
{
    int advertsWatched { 0 };   // How many ads were watched.
    double users { 0.0 };       // What percentage of users clicked on an ad.
    double earnings { 0.0 };    // The average earnings per clicked ad.
};

// T is used as a In/Out Parameter.
template<typename T> 
void getInput(T& data, const std::string_view description)
{
    while(true) {
        std::cout << "Enter " << description <<  ": ";
        std::cin >> data;

        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }else {
            // Exit the loop after finally collecting the required input
            return;
        }
    }
}

// Overloaded operator << prints the total made for the day computed from the
// struct details provided.
std::ostream& operator<<(std::ostream& out, const AdvertsInfo& advert)
{
    out << "The total made for the day is: "; 
    out << advert.advertsWatched * advert.users * advert.earnings << '\n';
    return out;
}

int main()
{
    AdvertsInfo advert {};

    getInput(advert.advertsWatched, "how many ads were watched");
    getInput(advert.users, "what percentage of users clicked on an ad");
    getInput(advert.earnings, "the average earnings per clicked ad");

    std::cout << advert;
}