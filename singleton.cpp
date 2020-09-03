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

int main(){
    chip::get_chip();
    chip::get_chip();
    chip::get_chip();
    chip::get_chip();
    atomic_bool b;
}




