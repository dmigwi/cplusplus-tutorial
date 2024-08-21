#include <iostream>
#include <string>
#include <string_view>

struct Monster
{
    enum Type 
    {
        ogre, dragon, orc, giantSpider, slime,
    } type;

    std::string name;
    int health;
};

constexpr std::string_view getMonsterType(Monster::Type mType) 
{
    switch(mType)
    {
        case  Monster::ogre: return "Ogre";
        case  Monster::dragon: return "Dragon";
        case  Monster::orc: return "Orc";
        case  Monster::giantSpider: return "Giant Spider";
        case  Monster::slime: return "Slime";
        default: return "Unknown!";
        }
}

void printMonster(const Monster& monster)
{
    std::cout << "This " << getMonsterType(monster.type) << " is named ";
    std::cout << monster.name <<" and has "<< monster.health<<" health. \n";
}

int main ()
{
    Monster ogre { Monster::ogre, "Torg", 145 };
    Monster slime { Monster::slime, "Blurp", 23 };

    printMonster(ogre);
    printMonster(slime);

    return 0;
}