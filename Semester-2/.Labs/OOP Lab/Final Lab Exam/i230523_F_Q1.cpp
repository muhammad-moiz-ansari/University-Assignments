#include <iostream>
#include "i230523_F_Q1.h"
using namespace std;

Mythoria::Mythoria(int X0, int X1, int Y0, int Y1)
{
    x0 = X0;
    x1 = X1;
    y0 = Y0;
    y1 = Y1;
}

Creature::Creature(std::string n, int lvl, int h, int f, int X)
{
    name = n;
    level = lvl;
    health = h;
    force = f;
    p.setx(X);
}

void Creature::setPosx(int X)
{
    p.setx(X);
}

int Creature::getHealth()
{
    return health;
}

int Creature::getPosx()
{
    return p.getx();
}

bool Creature::Alive()
{
    return health > 0;
}

int Creature::AttackPoints()
{
    return level * force;
}

void Creature::Move(Creature& c, int l, Mythoria& land)
{
    while (true)
    {
        if (this->getPosx() >= land.x1 || this->getPosx() <= land.x0)
            break;

        if (c.getPosx() > this->getPosx())
        {
            this->setPosx(this->getPosx() + 1);
            if (abs(c.getPosx() - this->getPosx()) <= l)
                break;
        }
        else
        {
            this->setPosx(this->getPosx() - 1);
            if (abs(c.getPosx() - this->getPosx()) <= l)
                break;
        }
    }
}

void Creature::GoodBye()
{
    if (health <= 0)
    {
        cout << name << " is no more\n";
    }
}

void Creature::Weak(int dam)
{
    health -= dam;
    GoodBye();
}

void Creature::Display()
{
    cout << "Name: " << name << endl
        << "Level: " << level << endl
        << "Health: " << health << endl
        << "Force: " << force << endl;
}

void Creature::Attack(Creature& victim)
{
    if (victim.health > 0)
    {
        victim.Weak(this->AttackPoints());
    }
}

Point::Point(int X, int Y) : x(X), y(Y) {}

int Point::getx()
{
    return x;
}

void Point::setx(int X)
{
    x = X;
}

Dragon::Dragon(int r, std::string n, int lvl, int h, int f, int X) : Creature(n, lvl, h, f, X)
{
    range = r;
}

void Dragon::Slither(Creature& en, Mythoria& land)
{
    Move(en, range, land);
}

void Dragon::BlowFlame(Creature& vic)
{
    if (Alive() && vic.Alive())
    {
        int of = abs(getPosx() - vic.getPosx());
        if (of <= range)
        {
            this->Attack(vic);
            //vic.Weak(AttackPoints());
            Weak(of);

            if (!vic.Alive() && Alive())
            {
                ++level;
            }
        }
    }
}

int Dragon::getRange()
{
    return range;
}

void Dragon::Display()
{
    Creature::Display();
    cout << "Range: " << range << endl;
}

Hydra::Hydra(int nl, int pd, std::string n, int lvl, int h, int f, int X) : Creature(n, lvl, h, f, X)
{
    necklength = nl;
    poisondose = pd;
}

int Hydra::getRange()
{
    return necklength;
}

void Hydra::Display()
{
    Creature::Display();
    cout << "Neck Length: " << necklength << endl
        << "Poison Dose: " << poisondose << endl;
}

void Hydra::injectPoison(Creature& vic)
{
    int withinrange = abs(getPosx() - vic.getPosx());

    if (Alive() && vic.Alive())
    {
        if (withinrange <= necklength)
        {
            vic.Weak(AttackPoints() + poisondose);
            if (!vic.Alive() && Alive())
            {
                ++level;
            }
        }
    }
}
