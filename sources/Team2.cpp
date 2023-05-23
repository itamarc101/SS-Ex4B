#include "Team2.hpp"
using namespace std;

namespace ariel
{

    void Team2::attack(Team* other)
    {
        if(other == this) throw invalid_argument("Cant attack youself!");
        
        if(other == nullptr) throw invalid_argument("Cant attack null");
        
        if (stillAlive() == 0 || other->stillAlive() == 0)
            throw runtime_error("Team must be alive!");
        
        if(!getLeader()->isAlive()) 
            setLeader(getNewLeader());

        Character* victim = findClosestCharacter(other);

        for(Character* character: getTeam())
        {
            if(!victim->isAlive()) 
            {
                if(other->stillAlive() == 0) return;
                victim = findClosestCharacter(other);
            }
            else
            {
                auto* cowboy = dynamic_cast<Cowboy*>(character);
                if(cowboy != nullptr)
                {
                    if(cowboy->hasboolets()) cowboy->shoot(victim);
                    else cowboy->reload();
                }
                auto* ninja = dynamic_cast<Ninja*>(character);
                if(ninja != nullptr)
                {
                    if(ninja->distance(victim) <= 1.0) ninja->slash(victim);
                    else ninja->move(victim);
                }
            }
            
        }
    }

    void Team2::print()
    {
        for(Character* character: getTeam())
        {
            cout << character->print() << endl;
        }
    }

    // Character *Team2::findClosestCharacter(Team * other)
    // {
    //     unsigned int long j = 0;
    //     double minDistance = numeric_limits<double>::max();
    //     for(unsigned int long i = 0; i < getTeam().size(); i++)
    //     {
    //         double tempDis = other->getTeam().at(i)->distance(getLeader());
    //         if(other->getTeam().at(i)->isAlive() && tempDis < minDistance)
    //         {
    //             minDistance = tempDis;
    //             j = i;
    //         }
    //     }
    //     return other->getTeam().at(j);
    // }
}