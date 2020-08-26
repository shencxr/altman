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


int main(){
    {
        AVLNode<int> a(1);
        AVLNode<int> b(2,&a);
        AVLNode<int> c(3,&b);
        AVLNode<int> d(4,&c);
        AVLNode<int> e(5);
        c.right_node(&e);
        cout<<&d;
    }
    return 0;
}
