
#include "car.cpp"

class CarFactory
{
protected:
    car* c;
public:
    CarFactory() = default;
    virtual ~CarFactory() = default;
    virtual car* buildCar() = 0;
};

class Simplecar : public CarFactory
{

public:
    car* buildCar() override {
        car* simplecar = new car("simplecar", new simpleTire(), new SimpleBody());
        return simplecar;
    }

};


class Luxurycar : public CarFactory
{

public:
    car* buildCar() override {
        car* luxurycar = new car("Luxurycar", new LuxuryTire(), new LuxuryBody());
        return luxurycar;
    }
};

