#pragma once
#include "Team.hpp"

namespace ariel
{
    class Team2 : public Team
    {
        public:
            Team2(Character * leader): Team(leader) {}
            void attack(Team * other) override; 
            void print() override;
            Character* findClosestCharacter(Team * other) override;

    };
}