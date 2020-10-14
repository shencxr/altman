#include <iostream>
#include <atomic>
#include <mutex>
#include <pthread.h>
using namespace std;

class chip{
private:
    chip(){}
    chip(const chip&){}
//    ~chip(){
//        chip * tmp=g_chip.load();
//        if(tmp!=nullptr){
//            delete tmp;
//            g_chip.store(nullptr);
//        }
//    }
    static atomic<chip*> g_chip;

public:
    static chip* get_chip();

};

#if 1
//chip* chip::g_chip=nullptr;
atomic<chip*> chip::g_chip;
chip *chip::get_chip()
{
    chip * tmp=g_chip.load();
    if(tmp==nullptr){
        cout<<"nullptr"<<endl;
        g_chip.store(new chip);
    }
    else{
        cout<<"none"<<endl;
        delete tmp;
        tmp=nullptr;
        g_chip.store(tmp);
//        chip * a=static_cast<chip*>(operator new(sizeof(chip)));
//        new (a) chip();
//        a->~chip();
    }
    return tmp;
}
#endif

enum test_enum{
    xxx=256,
    ccc=257,
    cca=258,
    ccb=259,
    ccas=31,
    ccbs=42
};

#include <memory>

template<typename T>
struct myclass{
    T data;
    myclass(T d):data(d){
        cout<<"myclass construct\n";
    }
    ~myclass(){
        cout<<"myclass deconstruct,data = "<<data<<"\n";
    }
};


int smain(){
    {
#if 0
        chip::get_chip();
        chip::get_chip();
        chip::get_chip();
        chip::get_chip();
        atomic_bool b;
        cout<<sizeof (test_enum)<<endl;
#endif
    }
    {
#if 0
        unique_ptr<myclass<string>> a;
        if(a==nullptr){
            cout<<"a==nullptr\n";
        }
        unique_ptr<myclass<string>> b(new myclass<string>(string("hello world")));
        cout<<"b.data:"<<(*b).data<<endl;
        a.reset(move(b.get()));
        cout<<"b.data:"<<(*b).data<<endl;
        cout<<"a.data:"<<(*a).data<<endl;
#endif
    }
    {
#if 1
//        unique_ptr<myclass<int>> a;
//        if(a==nullptr){
//            cout<<"a==nullptr\n";
//        }
        unique_ptr<myclass<int>> b(new myclass<int>(3));
        cout<<"b.data:"<<(*b).data<<endl;
        unique_ptr<myclass<int>> a=(move(b));
        if(b==nullptr){
            cout<<"b==nullptr\n";
        }
        else{
            cout<<"b.data:"<<(*b).data<<endl;
        }
        cout<<"a.data:"<<(*a).data<<endl;
        cout<<"print ...\n";
        a.reset(new myclass<int>(4));
        cout<<"out\n";
#endif
    }
    return 0;
}



























