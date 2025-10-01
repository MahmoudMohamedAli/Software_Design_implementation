#include<iostream>
#include<vector>
#include<mutex>
#include<thread>
#include <condition_variable>
#include<functional>
#include<queue>
#include<sstream>
using namespace std;
class threadpool
{
private:
    int numthread;
    std::mutex m1;
    std::condition_variable condvar;
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> workerthread;
    bool pool_shutdown;
    thread::id thread_id;
public:
    threadpool(int num_thread);
    ~threadpool();
    template<typename F>
    void Enqueue_tasks(F&& f);
};

threadpool::threadpool(int num_thread): numthread(num_thread), pool_shutdown(false)
{
    for(int x= 0; x < numthread; x++)
    {
        workerthread.emplace_back([this](){
            for(;;)
            {
                //std::cout<<"hello world"<< std::this_thread::get_id()<<std::endl;
                std::unique_lock<mutex> lock(m1);
                //lock on queue
                condvar.wait(lock,[this](){return (pool_shutdown || !(tasks.empty()));});
                //tasks.pop();
                if(pool_shutdown && tasks.empty()) //
                    return;
                std::function<void()> task =  std::move(tasks.front());
                tasks.pop();
                lock.unlock();
                task(); 
            }
        }

        );
    }
}

template<typename F>
void threadpool::Enqueue_tasks(F&& f)
{
    std::unique_lock<mutex> lock(m1);
    tasks.emplace(std::forward<F>(f));
    lock.unlock();
    condvar.notify_all();
}

threadpool::~threadpool()
{
    std::unique_lock<mutex> lock(m1);
    pool_shutdown = true;
    lock.unlock();
    condvar.notify_all();
    for(std::thread &work : workerthread)
    {
        work.join();
    }
}

std::string get_thread_id() {
  auto myid = std::this_thread::get_id();
  std::stringstream ss;
  ss << myid;
  std::string mystr = ss.str();
  return mystr;
}


void lastfunction()
{
    std::cout<<"Hello Last Func!  Thread_id: "<< get_thread_id()<< std::endl;
}


int main()
{
 threadpool pool(10);
 std::mutex m2;

 //thread_id
 for(int x= 0; x < 40; x++)
 {
    pool.Enqueue_tasks([x,&m2](){
    m2.lock();
    cout<< x <<": " << get_thread_id() <<": hello world!" <<endl;
    m2.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    });
 }

  pool.Enqueue_tasks(lastfunction);

} 