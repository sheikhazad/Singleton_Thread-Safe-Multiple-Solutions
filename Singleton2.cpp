#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
class Singleton2
{
public:

    static Singleton2*      getSingleton2Instance();

private:

    static Singleton2*     _mInstance;
    static std::once_flag  _mOnceFlag;
    //To check how many times Singleton2 constructor is called.
    static int             _mCount;

    Singleton2();
};

Singleton2*    Singleton2::_mInstance {nullptr};
std::once_flag Singleton2::_mOnceFlag;
int            Singleton2::_mCount = 0;

Singleton2* Singleton2::getSingleton2Instance()
{
    //call_once() will be called only once irrespective of how many threads are running.
   std::call_once(_mOnceFlag, [&]() {
                   if(_mInstance == nullptr){
                       _mInstance = new Singleton2();
                    }
                  } );

    return _mInstance;
}

Singleton2::Singleton2()
{
    ++_mCount;
    cout<< "\n Singleton2 constructor. I'm called - " << _mCount << " times." << endl;
}

void threadFunc()
{
    cout<<"\n Thread-2: Calling getSingleton2Instance() 10 times: " << endl;
    for(int i=0; i< 10; ++i)
    {
        Singleton2::getSingleton2Instance();
    }
}

int main()
{
    cout<<"****** Thread-safe Singleton by using std::call_once ******" << endl;
    thread t(threadFunc);

    cout<<"\n Thread-1: Calling getSingleton2Instance() 10 times: " << endl;
    for(int i=100; i< 110; ++i)
    {
        Singleton2::getSingleton2Instance();
    }

    t.join();
    return EXIT_SUCCESS;
}



