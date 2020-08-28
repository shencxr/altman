#include <iostream>
#include "test_driver.h"
#include <array>
#include <vector>
#include <deque>
#include <ctime>
#include <set>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <stack>
//#include <multiset>
#include "binary_search_tree.h"
#include <exception>
#include <algorithm>
#include "avl.h"
using namespace std;

namespace test1 {
    template<typename T>
    class parent{
    public:
        virtual parent* func(){
            cout<<"i am parent!"<<endl;
            return nullptr;
        }
    };

    template<typename T>
    class child:public parent<T>{
    public:
        child* func(){
            cout<<"i am child!"<<endl;
    //        return nullptr;
        }
    };


    template<typename T>
    ostream& operator <<(ostream& os,parent<T> *p){
        os<<"in  <<"<<endl;
        p->func();
        os<<"fun <<"<<endl;
        vector<vector<parent<T>*>> v2d;
        v2d.push_back({p});

        for (size_t i=0;i<v2d.size();i++) {
            for_each(v2d[i].begin(),v2d[i].end(),[](parent<T>*_n){
                _n->func();
            });
        }

        os<<"out <<"<<endl;
        return os;
    }
}


namespace test_template_design_pattern {

class parent{
public:
    void run(){
        fun1();
        fun2();
        fun3();
    }
private:
    virtual void fun2(){
        cout<<"parent private fun1"<<endl;
    }
    void fun1(){
        cout<<"parent private fun1"<<endl;
    }
    void fun3(){
        cout<<"parent private fun1"<<endl;
    }

};

class child:public parent{
public:
    void fun2(){
        cout<<"child public fun2"<<endl;
    }
};


}


int main(){
    {
#if 1
#endif
    }
    {
#if 0
        AVLNode<int> a(1);
        AVLNode<int> b(2,&a);
        AVLNode<int> c(3,&b);
        AVLNode<int> d(4,&c);
        AVLNode<int> e(5);
        c.right_node(&e);
        cout<<&d;
#endif
    }
    {
#if 1
        AVLTree<int> tree;
        for(int i=0;i<32-1;i++){
            cout<<i<<" insert : "<<tree.insert(i)<<endl;
        }
        cout<<tree.get_root();
        cout<<"remove(26) : "<<tree.remove(26)<<endl;
        cout<<tree.get_root();
        cout<<"remove(27) : "<<tree.remove(27)<<endl;
        cout<<tree.get_root();
        cout<<"remove(15) : "<<tree.remove(15)<<endl;
        cout<<tree.get_root();
        cout<<"remove(0) : "<<tree.remove(0)<<endl;
        cout<<tree.get_root();
        cout<<"remove(2) : "<<tree.remove(2)<<endl;
        cout<<tree.get_root();
        cout<<"remove(1) : "<<tree.remove(1)<<endl;
        cout<<tree.get_root();
        cout<<"remove(7) : "<<tree.remove(7)<<endl;
        cout<<tree.get_root();
        cout<<"remove(16) : "<<tree.remove(16)<<endl;
        cout<<tree.get_root();

//        AVLTree<int> tree;
//        for(int i=0;i<3;i++){
//            cout<<i<<" insert : "<<tree.insert(i)<<endl;
//        }
//        cout<<tree.get_root();
//        cout<<"remove(2) : "<<tree.remove(2)<<endl;
//        cout<<tree.get_root();


//        cout<<7<<" insert : "<<tree.insert(7)<<endl;
//        cout<<tree.get_root();
//        cout<<5<<" insert : "<<tree.insert(5)<<endl;
//        cout<<tree.get_root();
//        cout<<5<<" insert : "<<tree.insert(5)<<endl;
//        cout<<tree.get_root();
//        cout<<5<<" insert : "<<tree.insert(5)<<endl;
//        cout<<tree.get_root();
//        cout<<"before destory"<<endl;
//        tree.preorder_print();
//        tree.inorder_print();
//        tree.postorder_print();
//        tree.destory();
//        cout<<"after destory"<<endl;
//        cout<<tree.get_root();
#endif
    }

    {
#if 0
        using namespace test1;
        vector<parent<int>*> v;
        child<int> a;
        a.func();
        v.push_back(&a);
        v[0]->func();
        auto f=[](parent<int>& e){
            e.func();
        };
        f(a);

        auto f2=[](parent<int>* node){
            vector<vector<parent<int>*>> v2d;
            v2d.push_back({node});

            for (size_t i=0;i<v2d.size();i++) {
                for_each(v2d[i].begin(),v2d[i].end(),[](parent<int>*_n){
                    _n->func();
                });
            }
        };
        f2(&a);
        cout<<&a;
#endif
    }
    {
#if 0
        using namespace test_template_design_pattern;
        child a;
        a.run();
#endif
    }
    return 0;
}



















