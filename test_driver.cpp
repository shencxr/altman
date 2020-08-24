#include "test_driver.h"
#include <ctime>

Itest_base::~Itest_base(){}

inline void test_case::run(){
    if(p!=nullptr){
        p();
    }
}

inline void test_driver::run(){
    cout<<"********** test run **********"<<endl;
    clock_t t=clock();
    if(ptest!=nullptr){
        ptest->run();
    }
    cout<<"test Total time : "<<double(clock()-t)/CLOCKS_PER_SEC<<"s"<<endl;
}

