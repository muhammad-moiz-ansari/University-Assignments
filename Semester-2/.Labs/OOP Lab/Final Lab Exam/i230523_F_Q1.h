#pragma once
#include <cmath>
#include <string>

class Mythoria
{
public:
    int x0, x1;
    int y0, y1;

public:
    Mythoria(int X0 = 0, int X1 = 0, int Y0 = 0, int Y1 = 0);
};

class Point
{
private:
    int x;
    int y;

public:
    Point(int X = 0, int Y = 0);

    int getx();
    void setx(int X);
};

class Creature
{
protected:
    std::string name;
    int level;
    int health;
    int force;
    Point p;

public:
    Creature(std::string n = "", int lvl = 0, int h = 0, int f = 0, int X = 0);

    void setPosx(int X);

    int getHealth();
    int getPosx();
    virtual int getRange() = 0; // Pure virtual function

    bool Alive();
    int AttackPoints();
    void Move(Creature& character, int l, Mythoria& land);
    void GoodBye();
    void Weak(int dam);
    virtual void Display();
    void Attack(Creature& victim);

    virtual void Slither(Creature& en, Mythoria& land) = 0; // Pure virtual function
    virtual void BlowFlame(Creature& vic) = 0; // Pure virtual function
    virtual void injectPoison(Creature& vic) = 0; // Pure virtual function
};

class Dragon : public virtual Creature
{
private:
    int range;

public:
    Dragon(int r, std::string n = "", int lvl = 0, int h = 0, int f = 0, int X = 0);

    void Slither(Creature& en, Mythoria& land) override;
    void BlowFlame(Creature& vic) override;
    int getRange() override;

    void Display() override;

    void injectPoison(Creature& vic) override
    {}
};

class Hydra : public virtual Creature
{
private:
    int necklength;
    int poisondose;

public:
    Hydra(int nl = 0, int pd = 0, std::string n = "", int lvl = 0, int h = 0, int f = 0, int X = 0);

    int getRange() override;

    void injectPoison(Creature& vic) override;
    void Display() override;

    void Slither(Creature& en, Mythoria& land) override
    {}
    void BlowFlame(Creature& vic) override
    {}
};
