#include<iostream>
#include<mutex>
#include<thread>
#include<atomic>

using namespace std;
class Singleton1
{
public:

    static Singleton1*      getSingleton1Instance();

private:

    static atomic<Singleton1*> _mInstance;
    static mutex               _mMutex;
    //To check how many times Singleton2 constructor is called.
    static int                 _mCount;

    Singleton1();
};

atomic<Singleton1*> Singleton1::_mInstance {nullptr};
mutex Singleton1::_mMutex;
int Singleton1::_mCount = 0;

Singleton1* Singleton1::getSingleton1Instance()
{
    //Double checked locking mechanism is used for thread safety.
    if(_mInstance == nullptr)
    {
        lock_guard<mutex>lg(_mMutex);
        if(_mInstance == nullptr)
        {
           _mInstance = new Singleton1();
        }
    }
    return _mInstance;
}

Singleton1::Singleton1()
{
    ++_mCount;
    cout<< "\n Singleton1 constructor. I'm called - " << _mCount << " times." << endl;
}

void threadFunc()
{
    cout<<"\n Thread-2: Calling getSingleton1Instance() 10 times: " << endl;
    for(int i=0; i< 10; ++i)
    {
        Singleton1::getSingleton1Instance();
    }
}

int main()
{
    cout<<"****** Thread-safe Singleton by using mutex and atomic ******" << endl;

    thread t(threadFunc);

    cout<<"\n Thread-1: Calling getSingleton1Instance() 10 times: " << endl;
    for(int i=100; i< 110; ++i)
    {
        Singleton1::getSingleton1Instance();
    }

    t.join();
    return EXIT_SUCCESS;
}



