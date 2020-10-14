#include <iostream>
#include <thread>
#include <chrono>
#include <memory.h>
#include <mutex>
using namespace std;



class test{
public:
    void count(int start,int n){
        int t=start+n;
        for(int i=start;i<t;i++){
//            cout<<"thread id : "<<this_thread::get_id()<<endl;
            printf("count : %d\n",i);
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
};

static mutex ll;

int tmain(int ,char**){
    thread t1(&test::count,test(),1,2);
    thread t2(&test::count,test(),5,2);
//    std::thread::id t1_id = t1.get_id();
//    cout<<"thread id : "<<t1_id<<endl;
    printf("main begin\n");
    t1.join();
    t2.join();
    printf("join after\n");
//    boolalpha

    auto p=make_shared<test>();

    lock_guard<mutex> a(ll);

    return 0;
}
