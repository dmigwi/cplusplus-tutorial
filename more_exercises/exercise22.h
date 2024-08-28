#ifndef EXERCISE22_H
#define EXERCISE22_H

#include <string>
#include <string_view>

class Monster
{
public:
    enum Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,

        maxMonsterTypes, // Types total count
    };

    // Monster class constructor.
    Monster(Type type, const std::string_view name, const std::string_view roar, int points)
        : m_type{type}, m_name {name}, m_roar {roar}, m_points {points}
    {}

    constexpr std::string_view getTypeName(Monster::Type monsterType) const;
    void print() const;

private:
    Type m_type {};
    std::string m_name {"?"};
    std::string m_roar {"?"};
    int m_points {};
};

namespace MonsterGenerator
{
    // getName takes a number between 0 and 5 (inclusive) and return a name of your choice
    std::string_view getName(int n) {
        switch(n)
        {
            case 0:  return "Blarg";
            case 1:  return "Moog";
            case 2:  return "Pksh";
            case 3:  return "Tyrn";
            case 4:  return "Mort";
            case 5:  return "Hans";
            default: return "???";
        }
    }

    std::string_view getRoar(int n) {
        switch(n)
        {
            case 0:  return "*ROAR*";
            case 1:  return "*peep*";
            case 2:  return "*squeal*";
            case 3:  return "*whine*";
            case 4:  return "*growl*";
            case 5:  return "*burp*";
            default: return "???";
        }
    }

    Monster generate();
};

#endif