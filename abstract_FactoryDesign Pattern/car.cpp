#include<iostream>

#include<string>

using namespace std;
class tire
{
protected:
    string name = "General tire";
    int pressure = 0;
public:
    virtual string getname() { return name; };
    virtual int getPressure() { return pressure; };
    virtual ~tire() = default;
    tire(string name, int pressure) : name(name), pressure(pressure) {};
};

class simpleTire : public tire
{

public:
    simpleTire() : tire("simpletire", 100) {}
};

class LuxuryTire : public tire
{
public:
    LuxuryTire() : tire("luxurytire", 200) {}
};


class Body
{
protected:
    string name = "General body";
    int colorCode = 0;
public:
    string getname() { return name; }
    int getColor() { return colorCode; }
    virtual ~Body() = default;
    Body(string name, int colorCode) : name(name), colorCode(colorCode) {};
};

class SimpleBody : public Body {
public:
    SimpleBody() :Body("SimpleBody", 1) {}

};
class LuxuryBody : public Body {
public:
    LuxuryBody() :Body("LuxuryBody", 2) {}

};

class car {

protected:
    string name;
    tire* t;
    Body* body;

public:
    void setTire(tire* tire)
    {
        tire = tire;
    }
    void setBody(Body* body)
    {
        body = body;
    }
    car(string name, tire* t, Body* b) : name(name), t(t), body(b) {}
    void printCardetials()
    {
        cout << "car_Brand: " << name << " Car_body: " << body->getname() << " Car_tire: " << t->getname() << endl;
    }

};

