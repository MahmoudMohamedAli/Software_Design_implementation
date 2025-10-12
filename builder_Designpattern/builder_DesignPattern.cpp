#include <iostream>
#include <memory>
#include <string>
class Wheel
{
private:
    /* data */
    int size;

public:
    Wheel(int z) : size(z) {}
    ~Wheel() = default;
    int getSize() { return size; }
    Wheel() = default; // because of the limitation of unique pointer
};

class body
{
public:
    body() = default; //(std::unique_ptr<char> c) : color(std::move(c)) {}
    std::string color;
    ~body() = default;
};

// final product
class Car
{
private:
    /* data */

public:
    std::unique_ptr<Wheel[]> ptr_wheel;
    std::unique_ptr<body> ptr_body;
    void print_details()
    {
        std::cout << "body color: " << ptr_body->color << std::endl;
        std::cout << "wheel_Size: " << ptr_wheel[0].getSize() << std::endl;
    }
    Car() = default;
    ~Car() = default;
};

class Builder
{
public:
    virtual std::unique_ptr<Wheel[]> getWheel() = 0;
    virtual std::unique_ptr<body> getbody() = 0;
    Builder() = default;
    virtual ~Builder() = default;
};

class Director
{
private:
    std::unique_ptr<Builder> builder;

public:
    Director() = default;
    Director(std::unique_ptr<Builder> b) : builder(std::move(b))
    {
    }
    void setbuilder(std::unique_ptr<Builder> b)
    {
        builder = std::move(b);
    }
    std::unique_ptr<Car> getCar(std::unique_ptr<Car> car)
    {
        car->ptr_body = builder->getbody();
        car->ptr_wheel = builder->getWheel();
        return car;
    }
    ~Director() = default;
};

class modernCarBuilder : public Builder
{
public:
    std::unique_ptr<Wheel[]> getWheel() override
    {
        std::unique_ptr<Wheel[]> wheels = std::make_unique<Wheel[]>(4);
        for (int i = 0; i < 4; i++)
        {
            wheels[i] = Wheel(18);
        }
        return wheels;
    }

    std::unique_ptr<body> getbody() override
    {
        std::unique_ptr<body> b = std::make_unique<body>();
        b->color = "Modern Car Sucks";
        return b;
    }
    modernCarBuilder() = default;
    ~modernCarBuilder() = default;
};

class oldCarBuilder : public Builder
{
public:
    std::unique_ptr<Wheel[]> getWheel() override
    {
        std::unique_ptr<Wheel[]> wheels = std::make_unique<Wheel[]>(4);
        for (int i = 0; i < 4; i++)
        {
            wheels[i] = Wheel(3);
        }
        return wheels;
    }

    std::unique_ptr<body> getbody() override
    {
        std::unique_ptr<body> b = std::make_unique<body>();
        b->color = "old is gold";
        return b;
    }
    oldCarBuilder() = default;
    ~oldCarBuilder() = default;
};

int main()
{
    std::unique_ptr<Car> car = std::make_unique<Car>();
    Director director;
    std::unique_ptr<modernCarBuilder> moderncar = std::make_unique<modernCarBuilder>();
    std::unique_ptr<oldCarBuilder> oldcarbuild = std::make_unique<oldCarBuilder>();

    director.setbuilder(std::move(moderncar));
    car = director.getCar(std::move(car));
    car->print_details();

    director.setbuilder(std::move(oldcarbuild));
    car = director.getCar(std::move(car));
    car->print_details();
    return 0;
}