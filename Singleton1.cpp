#include<iostream>
#include<mutex>
#include<thread>
#include<atomic>

using namespace std;
//Assuming its hpp file
class Singleton1
{
public:

    static Singleton1&      getSingleton1Instance();

    //deleted functions should generally be public as it results in better error messages
    //due to the compilers behavior to check accessibility before deleted status
    //Singleton1(const Singleton1&) = delete; ==> If you want inline, no need to define in cpp file
    //Singleton1& operator=(const Singleton1&) = delete; ==> If you want inline, no need to define in cpp file    
    Singleton1(const Singleton1&);  
    Singleton1& operator=(const Singleton1&);
      
private:

    //To check how many times Singleton1 constructor is called.
    static int                 _mCount;

    Singleton1();
};

//cpp file:
int Singleton1::_mCount = 0;

Singleton1::Singleton1(const Singleton1&) = delete; 
Singleton1& Singleton1::operator=(const Singleton1&) = delete; 

Singleton1& Singleton1::getSingleton1Instance()
{
    //No need for mutex or atomic as static is thread safe
    static  Singleton1 instance;
    return instance;
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
    cout<<"****** Thread-safe Singleton without using mutex and atomic ******" << endl;

    thread t(threadFunc);

    cout<<"\n Thread-1: Calling getSingleton1Instance() 10 times: " << endl;
    for(int i=100; i< 110; ++i)
    {
        Singleton1::getSingleton1Instance();
    }

    t.join();
    return EXIT_SUCCESS;
}



