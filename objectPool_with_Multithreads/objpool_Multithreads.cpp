#include<iostream>
#include<vector>
#include<memory>
#include<mutex>
#include<chrono>
#include<thread>
#include<condition_variable>
#include<sstream>
#include<atomic>
using namespace std;


std::string get_thread_id() {
  auto myid = std::this_thread::get_id();
  std::stringstream ss;
  ss << myid;
  std::string mystr = ss.str();
  return mystr;
}


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
   
    condition_variable cndVar;

public:
 atomic<int> nextthreadindex ={0};
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
       // cout<<"added myclass object back"<<endl;
        pool.push_back(obj);
        cndVar.notify_all();
    }
    else
    {
        //cout<<"can't add more objects" << endl;
    }

}

shared_ptr<myclass> acquireObject()
{
    unique_lock<mutex> lock(m1);
    cndVar.wait(lock,[this](){ return !pool.empty();});
    auto obj =  pool.front();
    pool.erase(pool.begin());
  //  cout<<"send object and delete it from pool"<<endl;
    return obj;
    // if(pool.empty())
    // {
    //     cout<<"pool is empty can't create  more objects........" << endl;
    //     return nullptr;
    // }
    // else{
      
    // }
}
};

void worker(objectpool& pool)
{

    int next_index =  pool.nextthreadindex.fetch_add(1);
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
        cout << "thread Id: " << get_thread_id() <<" with indexed: " << next_index<<" num_ieration: "<< x << endl;

    }


}


int main()
{
  objectpool pool(1);
  std::vector<std::thread> workers; // Workers list will store all the threads.
  int workers_count = 2; // How many threads you want ?


  for(int i=0; i<workers_count; i++) {
    workers.emplace_back(worker, std::ref(pool));
  }

  for(int i=0; i<workers_count; i++) {
    workers[i].join();
  }

    return 0;
}