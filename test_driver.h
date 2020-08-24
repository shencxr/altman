#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H

#include <iostream>
using namespace std;
class Itest_base{
public:
    virtual ~Itest_base();
    virtual void run()=0;
};


class test_driver:public Itest_base{
public:
    test_driver():ptest(nullptr){}
    test_driver(Itest_base &test){
        ptest=&test;
    }
    ~test_driver(){}
    test_driver& set_case(Itest_base &test){
        ptest=&test;
        return *this;
    }
    test_driver& set_case(Itest_base *test){
        ptest=test;
        return *this;
    }
    void operator()(Itest_base &test){
        ptest=&test;
        run();
    }
    void run();
private:
    Itest_base * ptest;
};

class test_case:public Itest_base{
public:
    test_case(void (*tcase)(void)=nullptr):p(tcase){
//        cout<<"test_case ctor"<<endl;
    }
    test_case(const test_case& ){
//        cout<<"i am test_case copy ctor"<<endl;
    }
    test_case& operator()(void (*tcase)(void)=nullptr){
        p=tcase;
        return *this;
    }
    ~test_case(){
//        cout<<"test_case dector"<<endl;
    }
    void run();
private:
    void (*p)(void);
};



#endif // TEST_DRIVER_H
