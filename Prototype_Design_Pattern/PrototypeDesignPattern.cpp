#include<iostream>
#include<memory>
using namespace std;

class shape {
public:
    ~shape() = default;
    virtual unique_ptr<shape> clone() = 0;
    virtual void Draw() = 0;

};

class Circle :public shape {
private:
    int r;
public:
    Circle() :r(0) {}
    Circle(int r) :r(r) {}
    unique_ptr<shape> clone() override {
        return  make_unique<Circle>(*this);
    }
    void Draw() override {
        cout << "raduis = " << r << endl;
    }
    void set_radius(int r) { this->r = r; }


};

class Rect :public shape {
private:
    int width;
    int height;
public:
    Rect() :width(0), height(0) {}
    Rect(int width, int height) :width(width), height(height) {}
    unique_ptr<shape> clone() override {
        return  make_unique<Rect>(*this);
    }
    void Draw() override {
        cout << "Width = " << width << " Height = " << height << endl;
    }
    void set_height(int h) { height = h; }
    void set_width(int w) { width = w; }
};


int main()
{
    Rect rect_prototype(100, 100);
    Circle cir_prototype(200);
    rect_prototype.Draw();
    unique_ptr<shape> cloned_cir = cir_prototype.clone();
    unique_ptr<shape> cloned_rect = rect_prototype.clone();
    cloned_cir->Draw();
    cloned_rect->Draw();
    Rect* modify_rect = dynamic_cast<Rect*> (cloned_rect.get());
    modify_rect->set_width(300);
    modify_rect->Draw();

}