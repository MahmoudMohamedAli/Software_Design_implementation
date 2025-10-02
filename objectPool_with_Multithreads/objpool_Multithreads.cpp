#include<iostream>
#include<vector>
#include<memory>
#include<mutex>
#include<chrono>
#include<thread>
using namespace std;

class myclass
{
public:
    void print()
    {
        cout<< "print something"<<endl;
    }
};

class objectpool
{
private:
    vector<shared_ptr<myclass>> pool;
    int _size;
    mutex m1;
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
    unique_lock<mutex> lock(m1);
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
    unique_lock<mutex> lock(m1);
    if(pool.empty())
    {
        cout<<"pool is empty can't create  more objects........" << endl;
        return nullptr;
    }
    else{
        auto obj =  pool.front();
        pool.erase(pool.begin());
        cout<<"send object and delete it from pool"<<endl;
        return obj;
    }
}
};

void worker(objectpool& pool)
{
    for(int x=0; x < 15; x++)
    {
        auto obj = pool.acquireObject();
        if(obj)
        {
         //   obj->print();
            //simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
            pool.releaseObject(obj);
        }
        else{
        //null ptr
           printf("Thread  failed to acquire object\n");    
        }

    }


}


int main()
{
objectpool pool(3); // Create a pool with a maximum size of 3
  std::vector<std::thread> workers; // Workers list will store all the threads.
  int workers_count = 5; // How many threads you want ?
  
  for(int i=0; i<workers_count; i++) {
    workers.emplace_back(worker, std::ref(pool));
  }

  for(int i=0; i<workers_count; i++) {
    workers[i].join();
  }

    return 0;
}