#include "Team.hpp"

using namespace std;

namespace ariel
{
    Team::Team(Character * leader) //: _leader(leader), _sizeOfTeam(1)
    {
        if(leader->inTeam()) throw runtime_error("Leader has been assigned to a team already");
        
        leader->setInTeam(true);
        _leader = leader;
        _team.push_back(leader);
        _sizeOfTeam++;
    }

    void Team::add(Character * member)
    {
        if(_team.size() >= 10) throw runtime_error("Team full");

        for(Character* teamMember : _team)
        {
            if (teamMember == member) throw runtime_error("This player in the team");
        }

        if(member->inTeam()) throw runtime_error("Player has a team"); 

        //if(_sizeOfTeam >= 10) throw runtime_error("The team is full!");

        member->setInTeam(true);
        _team.push_back(member);
        _sizeOfTeam++;
    }

    // Find the closest character based on the leader's location
    Character* Team::findClosestCharacter(Team * other)
    {
        double closest = std::numeric_limits<double>::max();
        Character* closestCharacter = nullptr;

        for (Character* character : other->_team)
        {
            if (character->isAlive())
            {
                double curDist = getLeader()->distance(character);
                if (character->isAlive() && closest > curDist)
                {
                    closest = curDist;
                    closestCharacter = character;
                }
            }
        }
        return closestCharacter;
    }

    void Team::attack(Team* other)
    {
        if(other == this) throw invalid_argument("Cant attack youself!");
        
        if(other == nullptr) throw invalid_argument("Cant attack null");
        
        if (stillAlive() == 0 || other->stillAlive() == 0)
            throw runtime_error("Team must be alive!");

        if (!_leader->isAlive())
        { // find new leader
            _leader = getNewLeader();
        }

        Character* victim = findClosestCharacter(other);

        for(Character* character : _team)
        {
            if(!victim->isAlive()) 
            {
                if(!other->stillAlive()) return;
                victim = findClosestCharacter(other);
            }

            Cowboy* cowboy = dynamic_cast<Cowboy*>(character);
            if(cowboy != nullptr && cowboy->isAlive())
            {
                if(cowboy->hasboolets()) cowboy->shoot(victim);
                //else if(cowboy->isAlive()) cowboy->reload();
                else cowboy->reload();
            }
        }

        for(Character* character : _team)
        {
            if(!victim->isAlive()) 
            {
                if(other->stillAlive() == 0) return;
                victim = findClosestCharacter(other);
            }

            Ninja* ninja = dynamic_cast<Ninja*>(character);
            if(ninja != nullptr && ninja->isAlive())
            {
                if(ninja->getLocation().distance(victim->getLocation()) <= 1)
                    ninja->slash(victim);
                else ninja->move(victim);
            }
        }
    }

    int Team::stillAlive() const
    {
        int flagLive = 0;
        for(Character* character: _team)
        {
            if(character->isAlive()) flagLive++;
        }
        return flagLive;
    }

    void Team::print()
    {
        for(Character* character: _team)
        {
            if(dynamic_cast<Cowboy*>(character) != nullptr)
            {
                Cowboy* cowboy = dynamic_cast<Cowboy*>(character);
                cout << cowboy->print() << endl;
            }
            else if(dynamic_cast<Cowboy*>(character) != nullptr)
            {
                Ninja* ninja = dynamic_cast<Ninja*>(character);
                cout << ninja->print() << endl;
            }
        }
    }
    
    Character* Team:: getLeader() const 
    {
        return _leader;
    }

    void Team::setLeader(Character *leader) 
    {
        _leader = leader; 
    }

    vector<Character*> Team::getTeam() const
    {
        return _team;
    }

    Character* Team::getNewLeader()
    {
        if(_leader->isAlive()) return _leader;

        double closest = std::numeric_limits<double>::max();
        Character* getLeader = nullptr;

        for (Character* character : _team)
        {
            if (character->isAlive())
            {
                double curDist = character->distance(_leader);
                if (closest > curDist && _leader != character)
                {
                    closest = curDist;
                    getLeader = character;
                }
            }
        }
        return getLeader;
    }
}