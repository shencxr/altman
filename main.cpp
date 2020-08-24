//#include <iostream>
//#include <vector>
//#include <array>
//#include <algorithm>
//#include <ctime>
//#include <iomanip>
//using namespace std;

//#define SIZE    500000

//class Itest_base{
//public:
//    virtual ~Itest_base();
//    virtual void run()=0;
//};

//class test_driver:public Itest_base{
//public:
//    test_driver(){}
//    test_driver(Itest_base &test);
//    ~test_driver(){}
//    void set_case(Itest_base &&test);
//    void set_case(Itest_base &test);
//    void run();
//private:
//    Itest_base * ptest;
//};

//class test_case:public Itest_base{
//public:
//    template<class func>
//    test_case(func tcase=nullptr):p(tcase){
//        cout<<"test_case ctor"<<endl;}
//    test_case(const test_case& ){
//        cout<<"i am test_case copy ctor"<<endl;
//    }
//    ~test_case(){
//        cout<<"test_case dector"<<endl;
//    }
//    void run();
//    int v;
//private:
//    void (*p)(void);

//};

//void print(int n){
//    cout<<n<<endl;
//}

//test_case& ret_copy_ctor_test(test_case& a){
//    test_case &c=a;
//    cout<<"xxx"<<endl;
////    return test_case([](){cout<<"temp"<<endl;});
//    return c;
//}

//void hahaha(void){
//    cout<<"i am hahaha"<<endl;
//}


//int test_main()
//{
//    cout << "Hello World!" << endl;
//    {

//        array<int,SIZE> a;
//        vector<int> b(SIZE);
////        cout<<"size = "<<b.size()<<endl;
////        cout<<"capacity = "<<b.capacity()<<" "<<b.max_size()<<endl;
////        cout<<"size = "<<a.size()<<endl;
//        auto x=[](int &n){n=8;};
////        cout<<a.empty()<<" "<<a.max_size()<<endl;
//        for_each(a.begin(),a.end(),x);
////        for_each(a.begin(),a.end(),[](int n){cout<<n<<endl;});
//        for(size_t i=0;i<SIZE;i++){
//            int r=rand();
//            b[i]=a[i]=r;
//        }
//        clock_t t1,t2;
//        t1=clock();
//        sort(a.begin(),a.end());
//        t2=clock();
//        cout<<setw(15)<<left<<"array sort "<<SIZE<<" elements : "<<double(float(t2-t1)/CLOCKS_PER_SEC)<<"s"<<endl;
//        cout<<"array is sorted : "<<is_sorted(a.begin(),a.end())<<endl;;
//        t1=clock();
//        sort(b.begin(),b.end());
//        t2=clock();
//        cout<<setw(15)<<left<<"vector sort "<<SIZE<<" elements : "<<double(float(t2-t1)/CLOCKS_PER_SEC)<<"s"<<endl;
//        cout<<"vector is sorted : "<<is_sorted(b.begin(),b.end())<<endl;;
//    }
//    {
//        vector<int> a{1,2,3,4,5};
//        for_each(a.rbegin(),a.rend(),print);
//    }
//    {
////        auto func=;
//        cout << "-------------  test case  -------------"<<endl;
////        auto f=test_case([](){cout<<"arg"<<endl;});
//        test_driver a;

//        test_case l=test_case(hahaha);
//        a.set_case(l);
////        a.set_case(test_case([](){cout<<"arg"<<endl;}));
//        cout<<"after set"<<endl;
//        a.run();
//        cout << "-------------  test case  -------------"<<endl;
//    }
//    {
//        cout << "-------------  test case 2  -------------"<<endl;
//        test_case a([](){});
////        test_case c=ret_copy_ctor_test(a);
//        cout<<ret_copy_ctor_test(a).v<<endl;
//        cout << "-------------  test case 2  -------------"<<endl;
//    }
//    {
//        cout << "-------------  test case 3  -------------"<<endl;

//        cout << "-------------  test case 3  -------------"<<endl;
//    }
//    return 0;
//}

//test_driver::test_driver(Itest_base &test)
//{
//    cout<<"in test_driver ctor"<<endl;
//    test.run();
//}

//void test_driver::set_case(Itest_base &&test){
//    cout<<"in test_driver ctor,&arg = "<<&test<<endl;
//    this->ptest=&test;
//    cout<<"out test_driver ctor"<<endl;
//}

//void test_driver::set_case(Itest_base &test)
//{
//    cout<<"in test_driver ctor,&arg = "<<&test<<endl;
//    this->ptest=&test;
//    cout<<"out test_driver ctor"<<endl;
//}

//void test_driver::run(){
//    cout<<"in  test_driver run"<<endl;
//    clock_t t=clock();
//    ptest->run();
//    cout<<"test Total time : "<<double(3.145)/*double(double(clock()-t)/CLOCKS_PER_SEC)*/<<"s"<<endl;
//    cout<<"out test_driver run"<<endl;
//}

//Itest_base::~Itest_base()
//{

//}

//void test_case::run(){
//    if(p!=nullptr){
//        p();
//    }
//}
