#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


//template <typename T>
class Counter{
public:
    typedef int Count_t;
    static int order;
    Counter():_use_count(1),_order(++Counter::order){
        cout<<setw(_order*5)<<" "<<"/Counter ctor\n";
    }
    ~Counter(){
        cout<<setw(_order*5)<<" "<<"/~Counter dctor\n";
    }
    Count_t get_use_count()const{
        return _use_count;
    }
    void increase_count(){
        _use_count++;
    }
    void decrease_count(){
        _use_count--;
    }
private:
    Count_t _use_count;
    int _order;
};

template <typename T>
class SharedPoint{
public:
    typedef T* Point;
    typedef T& Reference;

    SharedPoint(Point p=nullptr):_ptr(p){
        _counter=new Counter();
    }

    SharedPoint(const SharedPoint& p):_counter(p._counter),_ptr(p._ptr){
//        cout<<"SharedPoint"<<endl;
        _counter->increase_count();
    }

    SharedPoint& operator=(const SharedPoint& p){
        _counter->decrease_count();
        if(_counter->get_use_count()==0){
            delete _counter;
            delete _ptr;
        }

        _counter=p._counter;
        _counter->increase_count();
        _ptr=p._ptr;
        return *this;
    }

    ~SharedPoint(){
        _counter->decrease_count();
        if(_counter->get_use_count()==0){
            delete _counter;
            delete _ptr;
        }
    }

    Reference operator* ()const{
        return *_ptr;
    }

    Point operator-> ()const{
        return _ptr;
    }

    Counter::Count_t used_count()const{
        return _counter->get_use_count();
    }

private:
    Counter* _counter;
    Point _ptr;
};


class test{
public:
    static int order;
    test(const string& s):_str(s),_order(++test::order){
        cout<<setw(_order*5)<<" "<<"|test ctor : "<<_str<<endl;
    }
    test(const char *s):_str(string(s)),_order(++test::order){
        cout<<setw(_order*5)<<" "<<"|test ctor : "<<_str<<endl;
    }
    test(const test& t) = delete ;
    ~test(){
        cout<<setw(_order*5)<<" "<<"|~test dctor : "<<_str<<endl;
    }
    void show()const{
        cout<<_str<<endl;
    }
private:
    string _str;
    int _order;
};

int Counter::order = 0;
int test::order = 0;




#include <hashtable.h>
#include <utility>

namespace hash_test {
    typedef pair<const string,string> Value;
    typedef const string Key;
};


struct _hash{
    size_t operator()(hash_test::Key& str)const{
        return hash<const char*>()(str.c_str());
    }
};


struct get_first{
    hash_test::Key& operator()(const hash_test::Value&p)const{
        return p.first;
    }
};

struct equal_string{
    bool operator()(hash_test::Key& str1,hash_test::Key& str2)const{
        return str2.compare(str1)==0?true:false;
    }
};



#include <unordered_map>
int fmain(int ,char** ){
    {
#if 0
        SharedPoint<test> p1(new test("hello"));
        SharedPoint<test> p2=new test("world");
        p2=p1;
        cout<<"p2.used_count = "<<p2.used_count()<<endl;


        const SharedPoint<test> p3(new test("const"));

        p3->show();
        (*p3).show();
        cout<<endl<<"-----------------saprator-----------------"<<endl;
        SharedPoint<test> p4(move(p3));
#endif
    }
    {
#if 1
        using namespace __gnu_cxx;
//        vector<int> v1;



        //,std::allocator<pair<string,string

        hashtable<hash_test::Value,hash_test::Key,_hash,get_first,equal_string> h_test(50,_hash(),equal_string());
        h_test.clear();
//        auto ret=h_test.insert_unique(pair<string,string>("1","hahahaha"));
//        cout<<"insert_unique : "<<boolalpha<<ret.second<<endl;
//        cout<<"key = "<<(*ret.first).first<<",value = "<<(*ret.first).second<<endl;
//        ret=h_test.insert_unique(pair<string,string>("2","balabala"));
//        cout<<"insert_unique : "<<boolalpha<<ret.second<<endl;
//        cout<<"key = "<<(*ret.first).first<<",value = "<<(*ret.first).second<<endl;

        h_test.insert_equal(pair<string,string>("1","hahahaha"));
        h_test.insert_equal(pair<string,string>("32","balabala"));

//        hashtable<hash_test::Value,hash_test::Key,_hash,get_first,equal_string>::const_iterator it=h_test.find("1");

//        auto it=h_test.begin();
//        cout<<"key = "<<(*it).first<<" : "<<(*it).second<<endl;
//        auto it2=h_test.find(string("2"));
//        cout<<"key = "<<(*it2).first<<" : "<<(*it2).second<<endl;

        cout<<"h_test.size() = "<<h_test.size()<<endl;
        auto bucket_size=h_test.bucket_count();
        cout<<"h_test.bucket_count() = "<<bucket_size<<endl;
        for (size_t i=0;i<bucket_size;i++) {
            cout<<"bucket "<<i<<" has "<<h_test.elems_in_bucket(i)<<" elements"<<endl;
        }
//        auto find1=h_test.find("32");
//        cout<<"key = "<<(*find1).first<<" : "<<(*find1).second<<endl;
//        for_each(h_test.begin(),h_test.end(),[](const hash_test::Value v){
//            cout<<"key = "<<v.first<<",value = "<<v.second<<endl;
//        });

#endif
    }
    {
#if 1
        unordered_map<string,string> umap(50);
        umap.insert(pair<string,string>("1","hahahaha"));
        umap.insert(pair<string,string>("32","balabala"));
        auto bucket_size=umap.bucket_count();
        cout<<"h_test.bucket_count() = "<<bucket_size<<endl;
        for (size_t i=0;i<bucket_size;i++) {
            cout<<"bucket "<<i<<" has "<<umap.bucket_size(i)<<" elements"<<endl;
        }
        auto it1=umap.find("1");
        cout<<"it1.key = "<<it1->first<<",it1.second = "<<it1->second<<endl;
#endif
    }

    {
#if 1
//        _Hashtable
#endif
    }



    return 0;
}









































