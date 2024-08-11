#include <iostream>

double fetchTowerHeight() 
{
    std::cout << "Enter the height of the tower in meters: ";
    double height {};
    std::cin >> height;
    return height;
}

void printCurrentHeight(int seconds, double ballHeight)
{
    if (ballHeight > 0)
        std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters \n";
    else
        std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

int main() 
{

    constexpr double gravity { 9.8 }; // Normal Earth Gravity is Approx. 9.8m/s
    double towerHeight { fetchTowerHeight() };
    double distanceFallen {0};
    double ballHeight {towerHeight};

    for (int seconds {0}; ballHeight > 0; seconds++) {
        if (seconds != 0) // Prevents 0/2 division from happening
            distanceFallen = (seconds * seconds * gravity)/2;
        
        ballHeight = {towerHeight - distanceFallen};

        printCurrentHeight(seconds, ballHeight);
    }

    return 0;
}