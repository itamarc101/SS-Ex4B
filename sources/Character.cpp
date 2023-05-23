#include "Character.hpp"

using namespace std;

namespace ariel
{

    bool Character::isAlive() const
    {
        return _health > 0;
    }

    double Character::distance(Character *other)
    {
        return _location.distance(other->getLocation());
    }

    void Character::hit(int dmg)
    {
        if(dmg < 0) throw invalid_argument("dmg can't be negative!");
        if(isAlive())
        {
            if(dmg >= _health) _health = 0;
            else _health -= dmg;
        }
    }

    string Character::getName() const
    {
        return _name;
    }

    int Character::getHP() const
    {
        return _health;
    }
    Point Character::getLocation() const
    {
        return _location;
    }

    void Character::setLocation(Point location)
    {
        _location = location;
    }

  string Character::print() 
    {
        string prnt = "Name:" +  _name + " HP: " + to_string(getHP()) + ", ";
        prnt += "(" + to_string(_location.getX()) + "," + to_string(_location.getY()) + ")";
        return prnt;
    }

    bool Character::inTeam()
    {
        return teamMember;
    }

    void Character::setInTeam(bool curTeamMember)
    {
        teamMember = curTeamMember;
    }
}
