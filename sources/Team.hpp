#pragma once
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include <vector>

namespace ariel
{
    class Team
    {
        private:
            Character *_leader;
            std::vector<Character *> _team;
            int _sizeOfTeam;
        
        public:
            Team(Character * leader);
            virtual ~Team() // destructor
            {
                for(Character* character : _team) delete character;
            }

            void add(Character * member);
            //virtual 
            void attack(Team * other);
            int getSizeOfTeam() { return _sizeOfTeam; }
            //Character* characterIndex(size_t charr);
            int stillAlive() const;
            void print();
            Character* getLeader() const;
            std::vector<Character*> getTeam() const;
            //virtual
            Character* findClosestCharacter(Team* other);
            void setLeader(Character* leader);
            Character* getNewLeader();

    };
}