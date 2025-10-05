#include<iostream>
#include<vector>
#include<algorithm>

class Observer; //forward declaration


class Car {
private:
    std::vector<Observer*> obsList;

public:
    int _tmp;
    int _pos;
    ~Car() = default;
    void attach_obs(Observer* obs)
    {
        obsList.push_back(obs);
        // obs->setcar_inst(this);

    }
    void deatch_obs(Observer* obs)
    {
        obsList.erase(std::remove(obsList.begin(), obsList.end(), obs),
            obsList.end());

    }
    void set_tmp(int tmp) {
        _tmp = tmp;
        notify_tmp();
    }
    void set_pos(int pos) {
        _pos = pos;
        notify_pos();
    }
    int get_tmp()
    {
        return _tmp;
    }
    int get_pos()
    {
        return _pos;
    }
    void notify_pos();
    void notify_tmp();
};

class Observer {
private:
    Car* _car;
protected:
    Car* getcar_inst()
    {
        return _car;
    }
public:
    //   void setcar_inst(Car* c);
    virtual void update_Pos() = 0;
    virtual void update_Tmp() = 0;
    Observer(Car* c) {
        _car = c;
        _car->attach_obs(this);
    }

};
//void Observer::setcar_inst(Car* c) { _car = c; }
class RightWheel : public Observer
{
public:
    RightWheel(Car* car) :Observer(car) {}
    void update_Pos()override {
        std::cout << " RightWheel  got it " << getcar_inst()->get_pos() << std::endl;
    }
    void update_Tmp()override {
        std::cout << " RightWheel  got it " << getcar_inst()->get_tmp() << std::endl;
    }


};

class LeftWheel : public Observer
{
public:
    LeftWheel(Car* car) :Observer(car) {}
    void update_Pos()override {

        std::cout << " LeftWheel  got it " << getcar_inst()->get_pos() << std::endl;
    }
    void update_Tmp()override {
        std::cout << " LeftWheel  got it " << getcar_inst()->get_tmp() << std::endl;
    }
};


void Car::notify_pos()
{
    std::cout << "Position changed Notify  all Observer:" << std::endl;
    for (Observer* obs : obsList)
    {
        obs->update_Pos();
    }
}
void Car::notify_tmp()
{
    std::cout << "Temperature changed Notify  all Observer" << std::endl;
    for (Observer* obs : obsList)
    {
        obs->update_Tmp();
    }
}



int main()
{

    Car* c1 = new Car();
    RightWheel sub3(c1);
    c1->set_pos(400);
    c1->set_tmp(300);
}