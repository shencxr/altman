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

#include <exception>
#include <algorithm>
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



template<typename T>
struct node{
    node():left(nullptr),right(nullptr){}
    node(T data,node *l=nullptr,node *r=nullptr):left(l),right(r),d(data){}

    inline node<T>* left_node() const{
        return left;
    }
    inline node<T>* right_node() const{
        return right;
    }
    node *left;
    node *right;
    T d;
};


template<typename T>
class Btree{
public:
    Btree():root(nullptr){}
    Btree& insert(T value);
    node<T>* get_root()const{
        return root;
    }
    int find_node_level(node<T>* n);
    int find_node_level(int n);
protected:
    Btree& _insert_recurve(node<T>* n,T value);
    int _find_node_level(node<T> *src,node<T>* n);
    int _find_node_level(node<T> *src,int n);
private:
    node<T> *root;
};



template<typename T>
Btree<T> &Btree<T>::insert(T value)
{
    if(root==nullptr){
//        cout<<value<<" add to root"<<endl;
        root=new node<T>(value);
        return *this;
    }
    return _insert_recurve(root,value);
}


template<typename T>
Btree<T> &Btree<T>::_insert_recurve(node<T>* n,T value)
{
    if(n->d>value){
        if(n->left!=nullptr){
            return _insert_recurve(n->left,value);
        }
        else{
//            cout<<value<<" add to "<<n->d<<" left"<<endl;
            n->left=new node<T>(value);
            return *this;
        }
    }
    else if(n->d<value){
        if(n->right!=nullptr){
            return _insert_recurve(n->right,value);
        }
        else{
//            cout<<value<<" add to "<<n->d<<" right"<<endl;
            n->right=new node<T>(value);
            return *this;
        }
    }
    else{
        return *this;
    }
}

#include <map>
#include <queue>
#include <cmath>

template<typename T>
ostream& operator<<(ostream& os,node<T>* n){
    vector<vector<node<T>*>> v2d;
    v2d.push_back({n});

    for (size_t i=0;;i++) {
        vector<node<T>*> next_l;
        for_each(v2d[i].begin(),v2d[i].end(),[&next_l](node<T>* _n){
            if(_n!=nullptr){
                next_l.push_back(_n->left_node());
                next_l.push_back(_n->right_node());
            }
            else{
                next_l.push_back(nullptr);
                next_l.push_back(nullptr);
            }
        });
        if(all_of(next_l.begin(),next_l.end(),[](node<T>* _n){return _n==nullptr?true:false;})==true){
            break;
        }
        else{
            v2d.push_back(next_l);
        }
    }
    size_t LEFT_INTERVAL=2;
    size_t NODE_INTERVAL=2;
    int NODE_WIDTH=2;
    size_t max_node_num=v2d.back().size();
    size_t total_l=v2d.size();

    for(size_t l=0;l<total_l;l++){
        stringstream vertical_line;
        stringstream horizontal_line;
        stringstream node;
        size_t _interval=size_t(pow(2,total_l-l-1));
        size_t node_interval=size_t(pow(2,total_l-l)-1);
        for(int i=0;i<int(_interval*LEFT_INTERVAL);i++){
            horizontal_line<<" ";
            vertical_line<<" ";
            node<<" ";
        }
        int c=0;
        int node_num=int(v2d[l].size());
        for(auto it=v2d[l].begin();it!=v2d[l].end();it++,c++){
            char linker=(*it)==nullptr?' ':'|';
            auto f=[](stringstream& func_os,int length,char token){
                for(int i=0;i<length;i++){
                    func_os<<token;
                }
            };
            if(c%2){
                //right child
                f(node,int(node_interval*NODE_INTERVAL)/2,'*');
                if((*it)==nullptr){
                    node<<setw(NODE_WIDTH)<<"$";
                    f(horizontal_line,int(node_interval*NODE_INTERVAL)/2,'/');
                    f(horizontal_line,int(NODE_WIDTH),'=');
                }
                else{
                    node<<setw(NODE_WIDTH)<<(*it)->d;
                    f(horizontal_line,int(node_interval*NODE_INTERVAL)/2,'-');
                    f(horizontal_line,int(NODE_WIDTH),'-');
                }
                if(c+1!=node_num){
                    f(node,int(node_interval*NODE_INTERVAL)/2,'*');
                    f(horizontal_line,int(node_interval*NODE_INTERVAL)/2,'/');
                }
            }
            else{
                //left child
                if(c!=0){
                    f(node,int(node_interval*NODE_INTERVAL)/2,'*');
                    f(horizontal_line,int(node_interval*NODE_INTERVAL)/2,'/');
                }
                if((*it)==nullptr){
                    node<<setw(NODE_WIDTH)<<"$";
                    f(horizontal_line,int(NODE_WIDTH),'=');
                    f(horizontal_line,int(node_interval*NODE_INTERVAL)/2,'/');

                }
                else{
                    node<<setw(NODE_WIDTH)<<(*it)->d;
                    f(horizontal_line,int(NODE_WIDTH),'-');
                    f(horizontal_line,int(node_interval*NODE_INTERVAL)/2,'-');
                }
                if(c+1!=node_num){
                    f(node,int(node_interval*NODE_INTERVAL)/2,'*');
                }
            }
            f(vertical_line,int(NODE_WIDTH),linker);

            if(c+1!=node_num){
                f(vertical_line,int(node_interval*NODE_INTERVAL),'+');
            }
        }
        if(l!=0){
            os<<horizontal_line.str()<<endl;
        }
        os<<node.str()<<endl;
        if(l+1!=total_l){
            os<<vertical_line.str()<<endl;
        }
    }
    return os;
}


template<typename T>
ostream& operator<<(ostream& os,Btree<T>& tree){
    vector<node<T>*> vec1;
    vec1.push_back(tree.get_root());
    size_t index=0;
    while (index!=vec1.size()) {
        if(vec1[index]!=nullptr){
            vec1.push_back(vec1[index]->right_node());
            vec1.push_back(vec1[index]->left_node());
        }
        index++;
    }

    int l=-1;
    auto kk=vec1.rbegin();
    for(;kk!=vec1.rend();kk++){
        if(*kk!=nullptr){
            l=tree.find_node_level(*kk);
            break;
        }
    }

    int total_l=l;
    stack<string> tree_str;
    string line;
    stringstream lines;
    lines.clear();
    cout<<"vec1.size = "<<vec1.size()<<endl;;
    while(!vec1.empty()){
        node<T>* it=vec1.back();
        if(it!=nullptr){
            if(l-1==tree.find_node_level(it)){
                lines<<endl;
                l--;
                lines<<setw((total_l-l)*5)<<"";
            }
            lines<<setw(5)<<it->d;
        }else{
            lines<<setw(5)<<"";
        }
        lines<<setw(5)<<"";
        vec1.pop_back();
    }

    os<<lines.str();
    return os;
}

template<typename T>
int Btree<T>::find_node_level(node<T> *n)
{
    if(root==nullptr||n==nullptr){
        return -1;
    }
    return _find_node_level(root,n);
}

template<typename T>
int Btree<T>::find_node_level(int n)
{
    if(root==nullptr){
        return -1;
    }
    if(root->d==n){
        return 0;
    }
    return _find_node_level(root,n);
}


template<typename T>
int Btree<T>::_find_node_level(node<T> *src,node<T> *n)
{
    if(src==nullptr){
        return -1;
    }
    else if(src->d==n->d){
        return 0;
    }
    int h=_find_node_level(src->left_node(),n);
    if(h==-1){
        h=_find_node_level(src->right_node(),n);
        return h==-1?-1:h+1;
    }
    else{
        return h+1;
    }
}

template<typename T>
int Btree<T>::_find_node_level(node<T> *src,int n)
{
    if(src==nullptr){
        return -1;
    }
    else if(src->d==n){
        return 0;
    }
    int h=_find_node_level(src->left_node(),n);
    if(h==-1){
        h=_find_node_level(src->right_node(),n);
        return h==-1?-1:h+1;
    }
    else{
        return h+1;
    }
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


int main(){
    Btree<int>  testTree;
//    for(int i=0;i<5;i++){
//        testTree.insert(i);
//    }
    testTree.insert(7);
    testTree.insert(45);
    testTree.insert(6);
    testTree.insert(3);
    testTree.insert(1);
    testTree.insert(9);/*
    testTree.insert(2);
    testTree.insert(10);
    testTree.insert(9);
    testTree.insert(4);
    testTree.insert(8);*/
//    cout<<testTree<<endl;
    cout<<testTree.get_root();

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
    return 0;
}





























