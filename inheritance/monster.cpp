#include <string>
#include <string_view>
#include <iostream>
#include <limits>

#include "randomMt.h"

class Creature
{
    public:
        Creature(std::string_view name, char symbol, int health, int damage, int gold)
            : m_name{name}, m_symbol {symbol}, m_health {health},
                m_damage {damage}, m_gold {gold}
        {}

        const std::string& getName() const { return m_name; }
        char getSymbol() const { return m_symbol; }
        int getHealth() const { return m_health; }
        int getDamage() const { return m_damage; }
        int getGold() const { return m_gold; }

        void reduceHealth(int health) { m_health -= health; }
        bool isDead() const { return m_health < 1; }
        void addGold(int gold) { m_gold += gold; }

    protected:
        std::string m_name;
        char m_symbol;
        int m_health;
        int m_damage; // Damage per attack
        int m_gold;
};

class Portion
{
    public:
        enum Type
        {
            health,
            strength,
            poison,
            max_types,
        };

        enum Size
        {
            small,
            medium,
            large,
            max_sizes,
        };

        Portion()
            : m_type {static_cast<Type>(RandomMt::get(0, max_types-1))},
             m_size {static_cast<Size>(RandomMt::get(0, max_sizes-1))}
        {}

        std::string getPortionTypeName()
        {
            switch(m_type)
            {
                case health:
                    return "Health";
                case strength:
                    return "Strength";
                case poison:
                    return "Poison";
                case max_types:
                    return "Unknown-Portion";
            }
        }

        std::string getPortionSizeName()
        {
            switch(m_size)
            {
                case small:
                    return "Small";
                case medium:
                    return "Medium";
                case large:
                    return "Large";
                case max_sizes:
                    return "Unknown-Quantity";
            }
        }

        const Type getType() const { return m_type; }
        const Size getSize() const { return m_size; }

    private:
        Size m_size;
        Type m_type;
};

class Player : public Creature
{
    public:
        Player(std::string_view name)
            : Creature{name, '@', 10, 1, 0}
            {}
        
        void levelUp()
        {
            ++m_level;
            ++m_damage;
        }

        bool hasWon() { return m_level >= 20; }
        int getLevel() const { return m_level; }

        void drinkPortion(Portion& portion)
        {
            switch (portion.getType())
            {
                case Portion::health:
                    m_health += ((portion.getSize() == Portion::large) ? 5 : 2);
                    break;
                case Portion::strength:
                    ++m_damage;
                    break;
                case Portion::poison:
                    --m_health;
                    break;
                case Portion::max_types: // unknown case.
                    break;
            }
        }

    private:
        int m_level {1};
};

class Monster : public Creature
{
    public:
        enum Type
        {
            dragon,
            orc,
            slime,
            max_types,
        };

        static inline Creature MonsterData[] {
            {"dragon", 'D', 20, 4, 100},
            {"orc", 'o', 4, 2, 25},
            {"slime", 's', 1, 1, 10},
        };

        Monster(Type monsterType)
            : Creature{MonsterData[monsterType]} 
        { }

        static Type getRandomMonster()
        {
            int randMonster { RandomMt::get(0, max_types-1) };
            return static_cast<Type>(randMonster);
        }
}; 

char readUserInput()
{
    char input {};
    std::cin >> input;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

// Player attacks the monster
void attackMonster(Player& player, Monster& monster) 
{
    monster.reduceHealth(player.getDamage());
    std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";

    if (monster.isDead())
    {
        player.addGold(monster.getGold());
        player.levelUp();

        std::cout << "You killed the " << monster.getName() << " .\n";
        std::cout << "You are now level " <<  player.getLevel() << ".\n";
        std::cout << "You found " << player.getGold() << " gold.\n";

        // Player has a 30% chance of finding the portion on killing
        // the monster.
        if (RandomMt::get(0, 2) == 2)
        {
            std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";

            char input { readUserInput() };
            if (input == 'Y' || input == 'y')
            {
                Portion portion {};
                player.drinkPortion(portion);

                std::cout << "You drank a " << portion.getPortionTypeName() 
                    << " portion of " << portion.getPortionSizeName() << ".\n";
            }
        }
    }
}

// Monster attacks the player
void attackPlayer(Player& player, Monster& monster) 
{
    if (monster.isDead()) // a dead monster cannot attack.
        return;

    player.reduceHealth(monster.getDamage());
    std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
}

void fightMonster(Player& player) {
    Monster monster { Monster::getRandomMonster()};
    std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";
    std::cout << "(R)un or (F)ight: ";

    char input { readUserInput() };

    if (input == 'f' || input == 'F')
    {
        attackMonster(player, monster);
        attackPlayer(player, monster);
    }
    else if (input == 'r' || input == 'R')
    {
        if (RandomMt::get(1, 2) == 1)
        {
            std::cout << "You successfully fled.\n";
            return;
        }

        std::cout << "You failed to flee.\n";
        attackPlayer(player, monster);
    }
}

int main()
{
	std::cout << "Enter your name: ";

    std::string username{};   
    std::getline(std::cin, username);

    std::cout << "Welcome, " << username << '\n';

    Player p {username};
    
    while (!p.hasWon() && !p.isDead())
    {
        fightMonster(p);
        std::cout << '\n';
    }

    if (p.isDead())
    {
        std::cout << "You died at level " << p.getLevel() << " and with " << p.getGold() << " gold.\n";
        std::cout << "Too bad you can't take it with you!\n";
    }

    if (p.hasWon())
    {
        std::cout << "Congratulations on your well deserved win!\n";
        std::cout << "You won at level " << p.getLevel() << " and with " << p.getGold() << " gold.\n";
    }

	return 0;
}