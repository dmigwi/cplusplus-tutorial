#include <iostream>
#include <limits>
#include "random.h"

int guessNumber(int pos) 
{
    std::cout << "Guess #" << pos << " :";
    int num {};
    std::cin >> num;

    if (!std::cin) { // or std::cin.fail()
        std::cin.clear();
        num = {-1};
    }

    // Ignore all characters in the buffer till a newline char is found.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return num;
}

void playGame(int tries, int min, int max) 
{
    int randNum { Random::get(min, max) };
    for (int i {1}; i <= tries; ++i) {
        int numGuess { guessNumber(i) }; 

        if (numGuess < min || numGuess > max ) {
            std::cout << "Invalid guess.\n";
        }
        else if (numGuess > randNum) {
            std::cout << "Your guess is too high.\n";
        } else if (numGuess < randNum) {
            std::cout << "Your guess is too low.\n";
        } else {
            std::cout << "Correct! You win!\n";
            return;
        }
    }
    std::cout << "Sorry, you lose. The correct number was " << randNum << ".\n";
}

bool playAgain()
{
    while(true) {
        std::cout << "Would you like to play again (y/n)?";
        char ch {};
    
        std::cin >> ch;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (ch) {
            case 'y':
                return true;
            case 'n':
                return false;
        }
    }
}

int main()
{
    constexpr int min { 1 };
    constexpr int max { 100 };
    constexpr int tries { 7 };

    std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max ;
    std::cout << ". You have " << tries << " tries to guess what it is.\n";

    do {
        playGame(tries, min, max);
    }
    while(playAgain());

    std::cout << "Thank you for playing.\n";
	return 0;
}