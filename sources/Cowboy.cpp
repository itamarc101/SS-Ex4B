#include "Cowboy.hpp"

using namespace std;

namespace ariel
{
    Cowboy::Cowboy(string name, Point location): Character(name, location, 110), _bullets(6)
    {}

    bool Cowboy::hasboolets()
    {
        return _bullets > 0;
    }

    void Cowboy::reload()
    {
        if(!isAlive()) throw runtime_error("Cowboy is dead and cant reload!!");
        _bullets = 6;
    }

    void Cowboy::shoot(Character * other)
    {
        if(other == nullptr) throw invalid_argument("cant attack null");
        
        if(!isAlive()) throw runtime_error("Cowboy character is already dead");

        if(other == this) throw runtime_error("Character tries to attack itself!");

        if(!other->isAlive()) throw runtime_error("Cant attack dead character");

        if(hasboolets() > 0)
        {
            other->hit(10);
            _bullets -= 1;
        }
    }

    int Cowboy::getBullets() const
    {
        return _bullets;
    }

    string Cowboy::print() const{
        string cowboyData;
        cowboyData = "Cowboy name: [C] " + getName() + "\n";
        if(isAlive()) cowboyData += "HP: " + to_string(getHP()) + "\n";
        cowboyData += "Location: " + to_string(getLocation().getX()) + "," + to_string(getLocation().getY());
        return cowboyData;
    }
}