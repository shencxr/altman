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
        AVLTree<int> tree;
        for(int i=0;i<5;i++){
            cout<<i<<" insert : "<<tree.insert(i)<<endl;
            cout<<tree.get_root();
        }
        cout<<7<<" insert : "<<tree.insert(7)<<endl;
        cout<<tree.get_root();
        cout<<5<<" insert : "<<tree.insert(5)<<endl;
        cout<<tree.get_root();
        cout<<5<<" insert : "<<tree.insert(5)<<endl;
        cout<<tree.get_root();
        cout<<5<<" insert : "<<tree.insert(5)<<endl;
        cout<<tree.get_root();
        cout<<"before destory"<<endl;
        tree.preorder_print();
        tree.inorder_print();
        tree.postorder_print();
        tree.destory();
        cout<<"after destory"<<endl;
        cout<<tree.get_root();
    }

    return 0;
}
