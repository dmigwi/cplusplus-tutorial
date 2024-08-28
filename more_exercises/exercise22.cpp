#include <iostream>
#include "exercise22.h"
#include "random.h"

constexpr std::string_view Monster::getTypeName(Monster::Type monsterType) const
{
    switch(monsterType)
    {
        case dragon: return "dragon";
        case goblin: return "goblin";
        case ogre: return "ogre";
        case orc: return "orc";
        case skeleton: return "skeleton";
        case troll: return "troll";
        case vampire: return "vampire";
        case zombie: return "zombie";
        default: return "Unknown!";
    }
}

void Monster::print() const 
{
    std::cout << m_name << " the " << getTypeName(m_type);
    if (m_points)
        std::cout  << " has "<< m_points << " hit points and says " << m_roar << ".\n";
    else 
        std::cout << " is dead.\n";
}

Monster MonsterGenerator::generate()
{
    return Monster{
        static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterTypes-1)),
        getName(Random::get(0, 5)),
        getRoar(Random::get(0, 5)), 
        Random::get(0, 100),
    };
}

int main()
{
    Monster m { MonsterGenerator::generate() };
	m.print();

	return 0;
}