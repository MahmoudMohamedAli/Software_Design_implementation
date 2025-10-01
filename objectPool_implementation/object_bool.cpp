#include<iostream>
#include<vector>
#include<memory>

using namespace std;

class myclass
{
    void print()
    {
        cout<< "print something";
    }
};

class objectpool
{
private:
    vector<shared_ptr<myclass>> pool;
    int _size;
public:
objectpool(int size):_size(size)
{
   for(int  i = 0;i < _size;i++ )
   {
    pool.push_back(make_shared<myclass>());
    cout<< "show address:" << pool.back() << endl;

   }
    
}


void releaseObject(shared_ptr<myclass> obj)
{
    if(_size > pool.size())
    {
        cout<<"added myclass object back"<<endl;
        pool.push_back(obj);
    }
    else
    {
        cout<<"can't add more objects" << endl;
    }

}
shared_ptr<myclass> acquireObject()
{
    if(pool.empty())
    {
        cout<<"pool is empty create new object........" << endl;
        return make_shared<myclass>();
    }
    else{
        auto obj =  pool.front();
        pool.erase(pool.begin());
        cout<<"send object and delete it from pool"<<endl;
        return obj;
    }
}

};


int main()
{
    objectpool objs(2);
    auto obj_1 = objs.acquireObject();
    auto obj_2 = objs.acquireObject();
    auto obj_3 = objs.acquireObject();
    auto obj_4 = objs.acquireObject();

    objs.releaseObject(obj_1);
    objs.releaseObject(obj_2);
    objs.releaseObject(obj_3);
    //check it still the same object we used.
    cout<<"obj_1 " << obj_1 <<endl;
    cout<<"obj_2 " << obj_2 <<endl;

    return 0;
}