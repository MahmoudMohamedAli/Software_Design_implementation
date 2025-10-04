#include "CarFactory.cpp"
#include<iostream>
using namespace std;
#define new_car 1
int main()
{

#if new_car == 0 
    CarFactory* carfac = new Simplecar();
#else
    CarFactory* carfac = new Luxurycar();
#endif
    car* c = carfac->buildCar();

    c->printCardetials();
    return 0;
}