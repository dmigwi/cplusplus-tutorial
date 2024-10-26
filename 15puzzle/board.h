#ifndef BOARD_15PUZZLE
#define  BOARD_15PUZZLE

#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include "random.h"

// Settings to handle the games control settings.
namespace Settings
{
    // ROWS and COLUMNS defines the grids measurement.
    const static int ROWS {4};
    const static int COLUMNS {4};

    // also the grid size.
    const static int EmptyTileNumber {ROWS * COLUMNS}; 
};

// Direction is a helper class to help read the various commands supported.
class Direction 
{
    public:
        enum Type : char
        {
            unknown,
            up = 'w',
            down = 's',
            left = 'a',
            right = 'd',
            quit = 'q',
        } ;

        explicit Direction(Type type = unknown)
            : m_type {type}
        {}

        friend std::istream& operator>> (std::istream& in, Direction& direction)
        {
            char input {};
            in >> input;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            auto command = static_cast<Type>(input);
            switch(command)
            {
                case up:
                case down:
                case right:
                case left:
                case quit:
                    direction.m_type = command;
                    break;
                default:
                    direction.m_type = unknown;
            }
            return in;
        }

        Direction operator-()
        {
            if (m_type == up)
                return Direction {down};
            else if (m_type == down)
                return Direction {up};
            else if (m_type == right)
                return Direction {left};
            else if (m_type == left)
                return Direction {right};
            else
                return Direction{};
        }

        Direction::Type getType() const
        {
            return m_type;
        }

        // Returns a random direction that is only between the four supported directions.
        static Type randomizeDirection()
        {
            int randNo { RandomMT::get(0, 3) };
            switch(randNo)
            {
                case 0:
                    return up;
                case 1:
                    return down;
                case 2:
                    return right;
                default:
                    return left; 
            }
        }
    
    private:
        Type m_type {unknown};
};

std::ostream& operator<< (std::ostream& out, const Direction& direction)
{
    switch (direction.getType())
    {
        case Direction::up:
            out << "up";
            break;
        case Direction::down:
            out << "down";
            break;
        case Direction::right:
            out << "right";
            break;
        case Direction::left:
            out << "left";
            break;
        case Direction::quit:
            out << "quit";
            break;
        default:
            out << "unknown";
    }
    return out;
}

class Point
{
    public:
        Point(int column, int row)
            : m_column{column}, m_row{row}
        {}

        Point& getAdjacentPoint(Direction::Type dType)
        {
            switch(dType)
            {
                case Direction::up:
                    if (m_row > 0)
                        --m_row;
                    break;
                case Direction::down:
                    if (m_row < Settings::ROWS - 1)
                        ++m_row;
                    break;
                case Direction::left:
                    if (m_column > 0)
                        --m_column;
                    break;
                case Direction::right:
                    if (m_column < Settings::COLUMNS - 1)
                        ++m_column;
                    break;
                case Direction::unknown:
                case Direction::quit:
                    break;
            }
            return *this;
        }

        friend bool operator==( const Point& a, const Point& b)
        {
            return (a.m_column == b.m_column) && (a.m_row == b.m_row);
        }

        friend bool operator!= (const Point& a, const Point& b)
        {
            return !(a==b);
        }

        Point& operator= (const Point& copy)
        {
            if (*this != copy)
            {
                m_column = copy.m_column;
                m_row = copy.m_row;
            }
            return *this;
        }

        std::size_t getArrayIndex()
        {
            return static_cast<std::size_t>(m_row * Settings::ROWS + m_column);
        }

    private:
        int m_column {0};
        int m_row {0};
};

/*
    Class Tile displays an individual tile.
*/
class Tile
{
    public:
        explicit Tile(int tileNumber=0)
            : m_tileNumber{tileNumber}
        {}

        friend std::ostream& operator<< (std::ostream& out, const Tile& tile)
        {
            std::string tileNo {" -"};
            if (tile.m_tileNumber != Settings::EmptyTileNumber)
            {
                tileNo = std::to_string(tile.m_tileNumber);
                tileNo = (tile.m_tileNumber < 10) ? " "+tileNo : tileNo;
            }
           
            out << tileNo + " ";
            return out;
        }

        friend bool operator!= (const Tile& a, const Tile& b)
        {
            return !operator==(a, b);
        }

        friend bool operator== (const Tile& a, const Tile& b)
        {
            return a.m_tileNumber == b.m_tileNumber;
        }

        friend bool operator< (const Tile& a, const Tile& b)
        {
            return a.m_tileNumber < b.m_tileNumber;
        }

        // isEmpty checks if a tile has been assigned a number.
        bool isEmpty()
        {
            return m_tileNumber == Settings::EmptyTileNumber;
        }

    private:
        int m_tileNumber {0};
};

/*
Board class that will handle:
    1. Randomize the starting positions of each tile.
    2. Displaying the tile positions on the UI.
    3. Slide each tile appropriately.
    4. Determine if the win condition is reached after each tile slide.
*/
class Board
{
    public:
        // initilizes the game grid in a solved state.
        Board()
        {
            for (int i {0}; i < Settings::EmptyTileNumber; ++i)
                m_tiles[static_cast<std::size_t>(i)] = Tile(i+1);
        }

        // Randomly moves the individual tiles within the grid and updates the
        // new position of the empty tile.
        void shuffleTiles()
        {
            // Move the tiles randomly for 1000 times.
            for( int i {0}; i < 1000; ++i)
                moveTile(Direction::randomizeDirection());
            // std::shuffle(m_tiles.begin(), m_tiles.end(), RandomMT::mt);

            // // Search for the empty tile position
            // for (int i {0}; i < Settings::EmptyTileNumber; ++i)
            // {
            //     if (m_tiles[static_cast<std::size_t>(i)].isEmpty())
            //     {
            //         int tempRow {i/Settings::ROWS};
            //         int tempCol {i - (tempRow * Settings::ROWS)};
            //         m_emptyTilePosition = Point(tempCol, tempRow);

            //         break; // exit the loop;
            //     }
            // }
        }

        bool isSorted() const
        {
            // Returns true once the whole array is sorted.
            return std::is_sorted(m_tiles.begin(), m_tiles.end());
        }

        void moveTile(Direction::Type direction)
        {
            std::size_t currentPos {m_emptyTilePosition.getArrayIndex()};

            m_emptyTilePosition.getAdjacentPoint(direction);
            std::size_t newPos { m_emptyTilePosition.getArrayIndex() };

            // Swap the two tiles.
            std::swap( m_tiles[currentPos],  m_tiles[newPos]);
        }

        void printTiles()
        {
            int index {0};
            for (int i {0}; i < Settings::COLUMNS; ++i){
                for (int k {0}; k < Settings::ROWS; ++k)
                {
                    index = (i * Settings::COLUMNS) + k;
                   std::cout << m_tiles[static_cast<std::size_t>(index)];
                }
                std::cout << '\n';
            }
        }

    private: 
        std::array <Tile, Settings::EmptyTileNumber> m_tiles;

        // By default the empty tile position of a resolved or initial grid
        // should always be the last item in the array.
        Point m_emptyTilePosition {Settings::COLUMNS-1, Settings::ROWS-1};
};

#endif