#include <iostream>
#include <limits>

#include "board.h"
    
int main()
{
    Board b {};
    b.shuffleTiles();
    b.printTiles();

    Direction command {};

    bool isExitCommand {false};
    
    // Handles user input and processes valid commands.
    while(!isExitCommand && !b.isSorted())
    {
        std::cout << "\nEnter a command: ";
        std::cin >> command;
        std::cout << "You entered direction: " << command << '\n';

        isExitCommand = (command.getType() == Direction::quit);

        if (!isExitCommand) // ignore moving tile is quit command was detected.
        {
            b.moveTile(command.getType());
            b.printTiles();
        }
        std::cout << '\n';
    } 

    if (b.isSorted())
        std::cout << "\n\nYou won!\n\n";

    std::cout << "\n\nBye!\n\n";
}
