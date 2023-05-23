#include "Ninja.hpp"
using namespace std;

namespace ariel
{
    Ninja::Ninja(string name, Point location, int health, int speed):
     Character(name, location, health), _speed(speed) {}
    
    void Ninja::move(Character *other)
    {
        setLocation(Point::moveTowards(getLocation(), other->getLocation(), _speed));
    }

    void Ninja::slash(Character *other)
    {
        if(!isAlive()) throw runtime_error("Cant attack if character is dead");

        if(this == other) throw runtime_error("cant attack itself");

        if(!other->isAlive()) throw runtime_error("cant attack dead character");

        if(getLocation().distance(other->getLocation()) <= 1)
            other->hit(40);
    }

    string Ninja::print() const{
        string ninjaData;
        ninjaData = "Ninja name: [N] " + getName() + "\n";
        if(isAlive()) ninjaData += "HP: " + to_string(getHP()) + "\n";
        ninjaData += "Location: (" + to_string(getLocation().getX()) + "," + to_string(getLocation().getY()) + ")";
        return ninjaData;
    }
}
