#include "SmartTeam.hpp"

using namespace std;

namespace ariel
{
    void SmartTeam::attack(Team* other)
    {
        if (other == this) throw invalid_argument("Cannot attack yourself!");

        if (other == nullptr) throw invalid_argument("Cannot attack null!");

        if (stillAlive() == 0 || other->stillAlive() == 0)
            throw runtime_error("Both teams must have alive members!");

        if (!getLeader()->isAlive())
        {
            setLeader(getNewLeader());
        }

        while (other->stillAlive() > 0)
        {
            Character* victim = findWeakestCharacter(other);

            if (victim->getHP() > 40 || victim == nullptr)
            {
                // If no weakest character with low HP, attack the closest opponent
                victim = findClosestCharacter(other);
            }

            for (Character* character : getTeam())
            {
                if (!character->isAlive()) continue;

                Cowboy* cowboy = dynamic_cast<Cowboy*>(character);
                Ninja* ninja = dynamic_cast<Ninja*>(character);

                if(victim->getHP() > 40 && character->isAlive())  
                {
                    if(cowboy != nullptr && cowboy->isAlive())
                    {
                        if(cowboy->hasboolets()) cowboy->shoot(victim);
                        else cowboy->reload();
                    }

                    if(ninja != nullptr && ninja->isAlive())
                    {
                        if(ninja->distance(victim) <= 1)
                            ninja->slash(victim);
                        else ninja->move(victim);
                    }
                }  

                if (cowboy != nullptr && cowboy->isAlive())
                {
                    if (cowboy->hasboolets() && 10 >= victim->getHP())
                    {
                        cowboy->shoot(victim);
                    }
                    else if (ninja != nullptr && ninja->isAlive() && ninja->distance(victim) <= 1 && 40 >= victim->getHP())
                    {
                        ninja->slash(victim);
                    }
                    else
                    {
                        ninja->move(victim);
                        cowboy->reload();
                    }
                }
                else if (ninja != nullptr && ninja->isAlive() && 40 >= victim->getHP())
                {
                    ninja->slash(victim);
                }
            }
        }
    }


    Character* SmartTeam::findWeakestCharacter(Team* other)
    {
        int minHP = numeric_limits<int>::max();
        Character* weakestCharacter = nullptr;

        for (Character* character : other->getTeam())
        {
            if (character->isAlive() && character->getHP() < minHP)
            {
                minHP = character->getHP();
                weakestCharacter = character;
            }
        }

        return weakestCharacter;
    }
}
