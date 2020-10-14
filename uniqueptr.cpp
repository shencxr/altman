#include <iostream>
#include <string>
using namespace std;


template<typename T>
class UniquePoint{
public:
    typedef T* Pointer;
    typedef T& Reference;

    UniquePoint():_ptr(nullptr){}
    UniquePoint(Pointer ptr):_ptr(ptr){}
    UniquePoint(UniquePoint&& ptr):_ptr(ptr._ptr){
        ptr._ptr=nullptr;
    }
    ~UniquePoint(){
        if(_ptr!=nullptr){
            delete _ptr;
        }
    }
    UniquePoint(const UniquePoint&) = delete;
    UniquePoint& operator =(const UniquePoint&) = delete;

    UniquePoint& operator= (UniquePoint&& ptr){
        if(_ptr!=nullptr){
            delete _ptr;
        }
        _ptr=ptr._ptr;
        ptr._ptr=nullptr;
        return *this;
    }

    Pointer operator ->(){
        return _ptr;
    }

    Reference operator *(){
        return *_ptr;
    }

private:
    Pointer _ptr;
};

template <typename T>
struct test{
    test(T d):data(d){
        cout<<"test\n";
    }
    test(const test&){}
    ~test(){
        cout<<"~test\n";
    }
    void show(){
        cout<<data<<endl;
    }
    T data;
};

template <typename T>
struct test2{
    test2(){}
    test2(const test2&){}
    ~test2(){
        cout<<"~test\n";
    }
    void show(){
        cout<<"show"<<endl;
    }
};

#include <hashtable.h>
#include <memory>
int umain(){
    pair<test<int>,test2<string>> pa(test<int>(2),test2<string>());

    UniquePoint<test<string>> ptr1(new test<string>("hello"));
    UniquePoint<test2<string>> ptr2;
    ptr1->show();
    if(ptr2.operator->()==nullptr){
        cout<<"ptr2.operator->()==nullptr"<<endl;
    }
    ptr2->show();
    cout<<string()<<endl;

    UniquePoint<test<string>> ptr3(move(ptr1));
    ptr3->show();

    (*ptr3).show();

    UniquePoint<test<string>> ptr4(new test<string>("world"));
    UniquePoint<test<string>> ptr5;
    ptr5=move(ptr4);
    ptr5->show();


    shared_ptr<test2<int>> a;


    return 0;
}















