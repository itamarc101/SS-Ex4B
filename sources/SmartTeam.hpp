#pragma once

#include "Team.hpp"

namespace ariel
{
    class SmartTeam : public Team
    {
        public:
            SmartTeam(Character *leader) :Team(leader){}
            Character* findWeakestCharacter(Team* other);
            void attack(Team * other) override;
    };
}
