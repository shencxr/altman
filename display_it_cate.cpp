#include <iostream>
#include <iterator>
#include <iomanip>

using namespace std;

template<typename T>
void _display_it_category_tag(const T&){}


template<>
void _display_it_category_tag(const input_iterator_tag&){cout<<"input_iterator_tag";}
template<>
void _display_it_category_tag(const output_iterator_tag&){cout<<"output_iterator_tag";}
template<>
void _display_it_category_tag(const forward_iterator_tag&){cout<<"forward_iterator_tag";}
template<>
void _display_it_category_tag(const bidirectional_iterator_tag&){cout<<"bidirectional_iterator_tag";}
template<>
void _display_it_category_tag(const random_access_iterator_tag&){cout<<"random_access_iterator_tag";}

template<typename T>
string display_it_category_tag(const T&)
{
    typename iterator_traits<T>::iterator_category category;
    _display_it_category_tag(category);
    return "";
}

#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>

#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#if __WIN32
#endif

struct testxxx{

};

struct child:public testxxx{
    int a;
    void printa(){
        cout<<"printa : "<<a<<endl;
    }
};

int main(int,char**){
    {
#if 1
        cout<<setw(40)<<"array::iterator = "<<display_it_category_tag(array<int,10>::iterator())<<endl;
        cout<<setw(40)<<"vector::iterator = "<<display_it_category_tag(vector<int>::iterator())<<endl;
        cout<<setw(40)<<"list::iterator = "<<display_it_category_tag(list<int>::iterator())<<endl;
        cout<<setw(40)<<"forward_list::iterator = "<<display_it_category_tag(forward_list<int>::iterator())<<endl;
        cout<<setw(40)<<"deque::iterator = "<<display_it_category_tag(deque<int>::iterator())<<endl;
//        display_it_category_tag(queue<int>::iterator());
//        display_it_category_tag(stack<int>::iterator());


        cout<<setw(40)<<"set::iterator = "<<display_it_category_tag(set<int>::iterator())<<endl;
        cout<<setw(40)<<"map::iterator = "<<display_it_category_tag(map<int,int>::iterator())<<endl;
        cout<<setw(40)<<"multiset::iterator = "<<display_it_category_tag(multiset<int>::iterator())<<endl;
        cout<<setw(40)<<"multimap::iterator = "<<display_it_category_tag(multimap<int,int>::iterator())<<endl;



        cout<<setw(40)<<"unordered_set::iterator = "<<display_it_category_tag(unordered_set<int>::iterator())<<endl;
        cout<<setw(40)<<"unordered_map::iterator = "<<display_it_category_tag(unordered_map<int,int>::iterator())<<endl;
        cout<<setw(40)<<"unordered_multiset::iterator = "<<display_it_category_tag(unordered_multiset<int>::iterator())<<endl;
        cout<<setw(40)<<"unordered_multimap::iterator = "<<display_it_category_tag(unordered_multimap<int,int>::iterator())<<endl;
#endif
    }
//    cout<<sizeof (testxxx)<<endl;
//    cout<<sizeof (child)<<endl;
//    bind2nd(less<int>(),40);
//    cout<<__cplusplus<<endl;

    child t;
    t.a=5;

    auto obj=bind(&child::printa,t);
//    cout<<typeid (obj).name()<<endl;
    obj();

    auto obj2=bind(&child::a,t);
    cout<<obj2()<<endl;
    return 0;
}









































