#include<iostream>
#include<string>
#include<algorithm>
class Target
{
private:

public:
    Target() = default;
    ~Target() = default;
    virtual void request() {
        std::cout << "Target phrase " << std::endl;
    }
};

class Adaptee {
public:
    std::string special_func()
    {
        return "!nam ih";
    }
};
class Adapter : public Target {
private:
    Adaptee* _adaptee;
    std::string modified_string;
public:
    Adapter(Adaptee* obj) { _adaptee = obj; }
    void request() {
        //write logic
        std::string reverse = _adaptee->special_func();
        std::reverse(reverse.begin(), reverse.end());
        modified_string = reverse;
    }
    std::string get_string()
    {
        return modified_string;
    }

};

void clintcode(Target* tar)
{
    tar->request();
}

int main()
{
    Target* original = new Target();
    Adaptee* adaptee = new Adaptee();
    clintcode(original);
    std::cout << "not understandable phrase:" << adaptee->special_func() << std::endl;
    Adapter* adapter = new Adapter(adaptee);
    clintcode(adapter);
    std::cout << "understandable phrase: " << adapter->get_string() << std::endl;
}