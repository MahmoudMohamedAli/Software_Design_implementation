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
   objectpool pool(3); // Create a pool with a maximum size of 3
  std::vector<std::thread> workers; // Workers list will store all the threads.
  int workers_count = 3; // How many threads you want ?
  
  for(int i=0; i<workers_count; i++) {
    workers.emplace_back(worker, std::ref(pool));
  }

  for(int i=0; i<workers_count; i++) {
    workers[i].join();
  }

    return 0;
}