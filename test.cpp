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

class UsCounter{
public:
//    UsCounter():
    void start(void){
        LARGE_INTEGER frq;
        QueryPerformanceFrequency(&frq);
        _frq=frq;
        QueryPerformanceCounter(&_n);
    }
    double end(void){
        LARGE_INTEGER tmp;
        QueryPerformanceCounter(&tmp);
        return double(tmp.QuadPart-_n.QuadPart)/_frq.QuadPart*1000000;
    }
private:
    LARGE_INTEGER _frq,_n;
};

int main1(){
    test_case func;
    test_driver driver;
    {
        driver(func([](){
            deque<int> deque1{1,2,3,4,5};
            deque<int> deque2{21,23,23,24,25};
            for_each(deque1.begin(),deque1.end(),[](int i){cout<<i<<" ";});
            cout<<endl;

            deque1.insert(deque1.end()-1,deque2.begin(),deque2.end()-1);

            for_each(deque1.begin(),deque1.end(),[](int i){cout<<i<<" ";});
            cout<<endl;
        }));
    }
    {
        UsCounter  tmonitor;
#define ASIZE   1000000
#define ORDER   1
        vector<int> vec1;
        multiset<int>    set1;
//        for(int i=0;i<1000000;i++){
//            try {
//                int r=rand();
//                vec1.push_back(r);
//                set1.insert(r);
//            } catch (exception &e) {
//                cout<<"exception : "<<e.what()<<endl;
//                abort();
//            }
//        }
        clock_t t=clock();
#if(ORDER==1)
        for(int i=0;i<ASIZE;i++){
            vec1.push_back(i);
        }
#else
        for(int i=ASIZE;i>0;i--){
            vec1.push_back(i);
        }
#endif
        t=clock()-t;
        cout<<"vec  init "<<ASIZE<<" elements need "<<double(t)/CLOCKS_PER_SEC<<"s"<<endl;
//        t=clock();
        tmonitor.start();
#if(ORDER==1)
        for(int i=0;i<ASIZE;i++){
            set1.insert(i);
        }
#else
        for(int i=ASIZE;i>0;i--){
            set1.insert(i);
        }
#endif
//        t=clock()-t;
        double times=tmonitor.end();
//        cout<<"set  init "<<ASIZE<<" elements need "<<double(t)/CLOCKS_PER_SEC<<"s"<<endl;
        cout<<"set  init "<<ASIZE<<" elements need "<<times<<"us"<<endl;
        cout<<"vector size : "<<vec1.size()<<endl;
        cout<<"set    size : "<<set1.size()<<endl;
#define FIND_NUM    30856
        vector<int>::iterator n=find(vec1.begin(),vec1.end(),FIND_NUM);
        t=clock()-t;
        cout<<"vector find "<<FIND_NUM<<" need "<<double(t)/CLOCKS_PER_SEC<<"s,result : "<<*n<<endl;
        t=clock();
        tmonitor.start();
        auto s=set1.find(FIND_NUM);
        times=tmonitor.end();
        t=clock()-t;
//        cout<<"set   .find "<<FIND_NUM<<" need "<<double(t)/CLOCKS_PER_SEC<<"s,result : "<<*s<<endl;
        cout<<"set   .find "<<FIND_NUM<<" need "<<times<<"us,result : "<<*s<<endl;
//        t=clock();
        tmonitor.start();
//        auto s2=find(set1.begin(),set1.end(),FIND_NUM);
        times=tmonitor.end();
//        t=clock()-t;
//        cout<<"set  ::find "<<FIND_NUM<<" need "<<double(t)/CLOCKS_PER_SEC<<"s,result : "<<*s2<<endl;
        cout<<"set   .find "<<FIND_NUM<<" need "<<times<<"us,result : "<<*s<<endl;

//        cout<<<<endl;
    }
    return 0;
}













class test_loop{
public:
    size_t size(){
        cout<<"i am size()"<<endl;
        return v.size();
    }
    void push_back(int n){
        v.push_back(n);
    }
    int operator[](size_t index){
        return v[index];
    }
private:
    vector<int> v;
};


int bmain(){
    {
        CBinarySearchTree<int>  testTree;
//        for(int i=0;i<5;i++){
//            testTree.insert(i);
//        }
        testTree.insert(7);
        testTree.insert(45);
        testTree.insert(6);
        testTree.insert(3);
        testTree.insert(1);
        testTree.insert(9);
        testTree.insert(2);
        testTree.insert(10);
        testTree.insert(9);
        testTree.insert(4);
        testTree.insert(8);
//        cout<<testTree<<endl;
        cout<<testTree;

//        cout<<"8 parent = "<<testTree.get_parent()

        cout<<"4 in level : "<<testTree.find_node_level(4)<<endl;

        vector<int> vec1;
        vec1.push_back(0);
        size_t i=0;
        vector<int>::iterator it=vec1.begin();
        for(;it!=vec1.end()&&i<5;it++,i++){
            vec1.push_back(int(i+1));
            cout<<*it<<"  "<<vec1[i]<<"  "<<vec1.size()<<endl;;

        }
        cout<<vec1.size()<<endl;
    }
    {
        map<pair<int,int>,string> m;
        m.insert(pair<pair<int,int>,string>(pair<int,int>(3,3),"n"));
        cout<<m.size()<<endl;
        auto it=m.find(pair<int,int>(3,3));
        if(it!=m.end()){
            cout<<(it)->second<<endl;
        }
        else{
            cout<<"no find"<<endl;
        }
    }


    {
        vector<vector<int>> v2d;
        v2d.push_back({3});
        cout<<v2d[0].size()<<" "<<v2d[0][0]<<endl;
    }
    {
        //测试loop的结束条件是函数时，会不会每循环一次后都被执行
        //结论：v_adpt.size()每次都会被执行
        test_loop v_adpt;
        for(int i=0;i<5;i++){
            v_adpt.push_back(i);
        }
        cout<<"v_adpt.size = "<<v_adpt.size()<<endl;
        for(size_t i=0;i<v_adpt.size();i++){
            cout<<v_adpt[i]<<" ";
        }
        cout<<endl;
    }
    system("cls");
    {
        CBinarySearchTree<int>  testTree;
        testTree.insert(7);
        testTree.insert(45);
        testTree.insert(6);
        testTree.insert(3);
        testTree.insert(1);
        testTree.insert(9);
        testTree.insert(2);
        testTree.insert(10);
        testTree.insert(9);
        testTree.insert(4);
        testTree.insert(8);
        cout<<endl<<testTree;
        cout<<"del 2 : "<<testTree.remove(2)<<endl;
        cout<<endl<<testTree;
        cout<<"del 45 : "<<testTree.remove(45)<<endl;
        cout<<endl<<testTree;
        cout<<"del 9 : "<<testTree.remove(9)<<endl;
        cout<<endl<<testTree;
        system("cls");
        cout<<"del 7 : "<<testTree.remove(7)<<endl;
        cout<<endl<<testTree;
        cout<<"del 3 : "<<testTree.remove(3)<<endl;
        cout<<endl<<testTree;
        cout<<"del 10 : "<<testTree.remove(10)<<endl;
        cout<<endl<<testTree;
        cout<<"del 18 : "<<testTree.remove(18)<<endl;
        cout<<endl<<testTree;
    }
//    system("pause");
    system("cls");
    {

        srand(static_cast<unsigned int>(rand()));
        CBinarySearchTree<int>  testTree;
        for(int i=0;i<10;i++){
            testTree.insert(rand()%13);
        }
        cout<<endl<<testTree;
            system("pause");
        cout<<"del 8 : "<<testTree.remove(8)<<endl;
        cout<<endl<<testTree;
    }
    {
        AVLNode<int> a(3);
        AVLNode<int> b(4,&a);
    }
    return 0;
}





























