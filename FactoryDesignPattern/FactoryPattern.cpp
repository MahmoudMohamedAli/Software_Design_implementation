#include<iostream>
#include<string>

using namespace std;
class product
{
private:
    /* data */
    std::string name;
public:
    product() = default;
    virtual ~product() = default;
    virtual string retProduct() = 0;
};

class productA : public product
{
private:

public:
    productA() = default;
    ~productA() = default;
    string retProduct() override { return "Product A"; }
};

class productB : public product
{
private:

public:
    productB() = default;
    ~productB() = default;
    string retProduct() override { return "Product B"; }
};

class Creator
{
private:
    /* data */
public:
    Creator() = default;
    virtual ~Creator() = default;
    virtual product* getproduct(string pro) = 0;
    virtual void deleteproduct(product* pro) = 0;
};

class ConcreteCreator : public Creator
{
private:
    /* data */
public:
    ConcreteCreator() = default;

    product* getproduct(string pro) override {
        if (pro == "A")
        {
            return new productA();
        }
        return new productB();
    }
    void deleteproduct(product* pro) override {
        delete pro;
    }
    ~ConcreteCreator() = default;


};

int main()
{

    Creator* Createfactory1 = new ConcreteCreator();
    product* p = Createfactory1->getproduct("A");
    auto product_A = p->retProduct();

    p = Createfactory1->getproduct("B");
    auto product_B = p->retProduct();
    cout << "A: " << product_A << " B: " << product_B << endl;

    delete Createfactory1;



}



