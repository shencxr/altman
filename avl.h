#ifndef AVL_H
#define AVL_H

#include "binary_search_tree.h"
#include <stack>



template<typename T>
struct AVLNode:public INode<T>{
public:
    AVLNode(T data=T(),AVLNode<T> *p=nullptr,AVLNode<T> *l=nullptr,AVLNode<T> *r=nullptr):_parent(p),_left(l),_right(r),_data(data),_height(0){
        if(l!=nullptr){
            l->parent(this);
        }
        if(r!=nullptr){
            r->parent(this);
        }
    }
    static AVLNode* maximum(AVLNode*node){
        while (node->right_node()!=nullptr) {
            node=node->right_node();
        }
        return node;
    }
    static AVLNode* minimum(AVLNode*node){
        while (node->left_node()!=nullptr) {
            node=node->left_node();
        }
        return node;
    }
    AVLNode<T>* parent()const{return _parent;}
    AVLNode* &left_node(){
        return _left;}
    void left_node(AVLNode<T>*l){
        _left=l;
        if(l!=nullptr){
            l->parent(this);
        }
    }
    AVLNode<T>* &right_node(){return _right;}
    void right_node(AVLNode<T>*r){
        _right=r;
        if(r!=nullptr){
            r->parent(this);
        }
    }
    T data()const{return _data;}
    void data(T d){_data=d;}
    int height(void)const{return _height;}
    void height(int h){_height=h;}

    AVLNode<T>* left_rotate(){
        AVLNode<T>* tmp=_right;
        _right=_right->_left;
        if(_right!=nullptr){
            _right->parent(this);
        }
        tmp->_left=this;
        tmp->parent(_parent);
        _parent=tmp;
        return tmp;
    }
    AVLNode<T>* right_rotate(){
        AVLNode<T>* tmp=_left;
        _left=_left->_right;
        if(_left!=nullptr){
            _left->parent(this);
        }
        tmp->_right=this;
        tmp->parent(_parent);
        _parent=tmp;
        return tmp;
    }

    AVLNode<T>* left_right_rotate(){
        _left=_left->left_rotate();
        _left->parent(this);
        return right_rotate();
    }

    AVLNode<T>* right_left_rotate(){
        _right=_right->right_rotate();
        _right->parent(this);
        return left_rotate();
    }


    static int height(AVLNode<T>* cur){
        if(cur==nullptr){
            return 0;
        }
        int l_h=height(cur->_left);
        int r_h=height(cur->_right);
        return max(l_h+1,r_h+1);
    }


    void parent(AVLNode<T>* p){_parent=p;}
private:
    AVLNode<T> *_parent;
    AVLNode<T> *_left;
    AVLNode<T> *_right;
    T _data;
    int _height;
};


#include <iterator>
#include <stack>
#include <vector>
template<typename T>
class MyIterator:public iterator<forward_iterator_tag,T>{
public:
    //采用中序遍历顺序，先左子树，再根，后右子树
    MyIterator(AVLNode<T>* begin){
        _init_sequence(begin);
        ptr=sequence.begin();
    }
    MyIterator(AVLNode<T>* begin,int){
        sequence.push_back(begin);
        ptr=sequence.begin();
    }

    T operator *(){
        return (*ptr)->data();
    }

    MyIterator& operator ++(){
        ++ptr;
        return *this;
    }

    MyIterator operator ++(int){
        AVLNode<T>*tmp=(*ptr);
        ++ptr;
        return MyIterator<T>(tmp,3);
    }


protected:
    void _init_sequence(AVLNode<T>*cur){
        if(cur!=nullptr){
            if(cur->left_node()!=nullptr){
                _init_sequence(cur->left_node());
            }
            sequence.push_back(cur);
            if(cur->right_node()!=nullptr){
                _init_sequence(cur->right_node());
            }
        }
    }
private:
    vector<AVLNode<T>*> sequence;
    typename vector<AVLNode<T>*>::iterator ptr;
};

template<typename T>
class AVLTree{
public:

    typedef MyIterator<T> iterator;

    AVLTree(AVLNode<T>* r=nullptr):root(r){}
    bool insert(T value);
    bool remove(T value);
    AVLNode<T>* get_root() {
        return root;
    }
    void destory(){
        _destory(root);
    }
    void preorder_print(void){
        cout<<"preorder traversal  : ";
        _preorder_print(root);
        cout<<endl;
    }
    void inorder_print(void){
        cout<<"inorder traversal   : ";
        _inorder_print(root);
        cout<<endl;
    }
    void postorder_print(void){
        cout<<"postorder traversal : ";
        _postorder_print(root);
        cout<<endl;
    }
    void inorder_print_stack(void){
        cout<<"inorder traversal   : ";
        sequence.push(root);
        _inorder_print_stack();
        cout<<endl;
    }

    iterator begin(){
        return iterator(root);
    }


    iterator end(){
        return iterator(nullptr);
    }

    stack<AVLNode<T> *> sequence;
    void _inorder_print_stack(void){
        if(!sequence.empty()){
            AVLNode<T> * cur=sequence.top();
            if(cur->left_node()!=nullptr){
                sequence.push(cur->left_node());
                _inorder_print_stack();
            }
            cout<<cur->data()<<" ";
            if(cur->right_node()!=nullptr){
                sequence.push(cur->right_node());
                _inorder_print_stack();
            }
            sequence.pop();
        }
    }
protected:
    AVLNode<T> *_remove(AVLNode<T> *&n,T value);
    AVLNode<T> *_insert_recurve(AVLNode<T> *&node, T value);
    void _preorder_print(AVLNode<T> *cur){
        if(cur!=nullptr){
            cout<<cur->data()<<" ";
            _preorder_print(cur->left_node());
            _preorder_print(cur->right_node());
        }
    }

    void _inorder_print(AVLNode<T> *cur){
        if(cur!=nullptr){
            _inorder_print(cur->left_node());
            cout<<cur->data()<<" ";
            _inorder_print(cur->right_node());
        }
    }
    void _postorder_print(AVLNode<T> *cur){
        if(cur!=nullptr){
            _postorder_print(cur->left_node());
            _postorder_print(cur->right_node());
            cout<<cur->data()<<" ";
        }
    }
    void _destory(AVLNode<T>* &n){
        if(n!=nullptr){
            _destory(n->left_node());
            _destory(n->right_node());
            delete n;
            n=nullptr;
        }
    }

private:
    AVLNode<T>* root;
};

#define PRINT_PARENT        1
#define INTERVAL            6
#define LAYER_LINKER        '|'
#define NODE_TOP            ' '
#define BETEWEEN_TOP        '-'
#define BETWEEN_NODE        ' '
#define NULL_NODE_TOP       ' '
#define BETWEEN_NODE_TOP    ' '
#define NULL_NODE           ' '
#define BETWEEN_LINKER      ' '
template<typename T>
ostream& operator<<(ostream& os,AVLNode<T>* node){
    vector<vector<AVLNode<T>*>> v2d;
    v2d.push_back({node});
    node->left_node();
    for (size_t i=0;;i++) {
        vector<AVLNode<T>*> next_l;
        for_each(v2d[i].begin(),v2d[i].end(),[&next_l](AVLNode<T>*_n){
            if(_n!=nullptr){
                next_l.push_back(_n->left_node());
                next_l.push_back(_n->right_node());
            }
            else{
                next_l.push_back(nullptr);
                next_l.push_back(nullptr);
            }
        });
        if(all_of(next_l.begin(),next_l.end(),[](void* _n){return _n==nullptr?true:false;})==true){
            break;
        }
        else{
            v2d.push_back(next_l);
        }
    }

    assert(INTERVAL%2==0);
    size_t total_l=v2d.size();
//    cout<<"total_l = "<<total_l<<endl;
    for(size_t l=0;l<total_l;l++){
        stringstream vertical_line;
        stringstream horizontal_line;
        stringstream node;
        size_t _interval=size_t(pow(2,total_l-l-1));
        size_t node_interval=size_t(pow(2,total_l-l)-1);
        for(int i=0;i<int(_interval*INTERVAL);i++){
            horizontal_line<<" ";
            vertical_line<<" ";
            node<<" ";
        }
        int c=0;
        int node_num=int(v2d[l].size());
        for(auto it=v2d[l].begin();it!=v2d[l].end();it++,c++){
            char linker=' ';
            if((*it)!=nullptr){
                if(((*it)->left_node()!=nullptr)||((*it)->right_node()!=nullptr)){
                    linker=LAYER_LINKER;
                }
            }

            auto f=[](stringstream& func_os,int length,char token){
                for(int i=0;i<length;i++){
                    func_os<<token;
                }
            };
            if(c%2){
                //right child
                f(node,int(node_interval*INTERVAL)/2,BETWEEN_NODE);
                if((*it)==nullptr){
                    node<<setw(INTERVAL)<<NULL_NODE;
                    f(horizontal_line,int(node_interval*INTERVAL)/2,BETWEEN_NODE_TOP);
                    f(horizontal_line,int(INTERVAL),NULL_NODE_TOP);
                }
                else{
#if PRINT_PARENT
                    T parent_v=9;
                    if((*it)->parent()!=nullptr){
                        parent_v=((*it)->parent())->data();
                    }
                    node<<setw(INTERVAL/2)<<(*it)->data()<<setw(INTERVAL/2)<<parent_v;
#else
                    node<<setw(INTERVAL)<<(*it)->data();
#endif
                    f(horizontal_line,int(node_interval*INTERVAL)/2,BETEWEEN_TOP);
                    f(horizontal_line,int(INTERVAL),NODE_TOP);
                }
                if(c+1!=node_num){
                    f(node,int(node_interval*INTERVAL)/2,BETWEEN_NODE);
                    f(horizontal_line,int(node_interval*INTERVAL)/2,BETWEEN_NODE_TOP);
                }
            }
            else{
                //left child
                if(c!=0){
                    f(node,int(node_interval*INTERVAL)/2,BETWEEN_NODE);
                    f(horizontal_line,int(node_interval*INTERVAL)/2,BETWEEN_NODE_TOP);
                }
                if((*it)==nullptr){
                    node<<setw(INTERVAL)<<NULL_NODE;
                    f(horizontal_line,int(INTERVAL),NULL_NODE_TOP);
                    f(horizontal_line,int(node_interval*INTERVAL)/2,BETWEEN_NODE_TOP);

                }
                else{
#if PRINT_PARENT
                    T parent_v=9;
                    if((*it)->parent()!=nullptr){
                        parent_v=((*it)->parent())->data();
                    }
                    node<<setw(INTERVAL/2)<<(*it)->data()<<setw(INTERVAL/2)<<parent_v;
#else
                    node<<setw(INTERVAL)<<(*it)->data();
#endif
                    f(horizontal_line,int(INTERVAL),NODE_TOP);
                    f(horizontal_line,int(node_interval*INTERVAL)/2,BETEWEEN_TOP);
                }
                if(c+1!=node_num){
                    f(node,int(node_interval*INTERVAL)/2,BETWEEN_NODE);
                }
            }
            vertical_line<<setw(INTERVAL)<<linker;

            if(c+1!=node_num){
                f(vertical_line,int(node_interval*INTERVAL),BETWEEN_LINKER);
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


#endif // AVL_H

template<typename T>
bool AVLTree<T>::insert(T value)
{
//    if(root==nullptr){
//        root=new AVLNode<T>(value);
//        return true;
//    }
    return _insert_recurve(root,value)==nullptr?false:true;
}


template<typename T>
bool AVLTree<T>::remove(T value)
{
#if 1
    return _remove(root,value);
#else

    AVLNode<T> *cur=root;
    AVLNode<T> *par=nullptr;
    while (cur!=nullptr) {
        if(cur->data()==value){
            break;
        }
        else if(value<cur->data()){
            par=cur;
            cur=cur->left_node();
        }
        else{
            par=cur;
            cur=cur->right_node();
        }
    }
    if(cur==nullptr){
        cout<<"not find "<<value<<endl;
        return false;
    }
    if(cur->right_node()==nullptr){
        if(par==nullptr){
            cur->left_node()->parent(nullptr);
            root=cur->left_node();
        }
        else{
            if(cur->left_node()!=nullptr){
                cur->left_node()->parent(par);
            }
            if(par->left_node()==cur){
                par->left_node(cur->left_node());
            }
            else{
                par->right_node(cur->left_node());
            }
        }
        while(par!=nullptr){
            if((AVLNode<T>::height(par->left_node())-AVLNode<T>::height(par->right_node()))==2){
                //最小失衡树的根节点的 左树比右树高
                if(AVLNode<T>::height(par->left_node()->left_node())>AVLNode<T>::height(par->left_node()->right_node())){
                    par->right_rotate();
                }
                else{
                    par->left_right_rotate();
                }
                break;
            }
            else if((AVLNode<T>::height(par->left_node())-AVLNode<T>::height(par->right_node()))==-2){
                //最小失衡树的根节点的 右树比左树高
                if(AVLNode<T>::height(par->right_node()->right_node())>AVLNode<T>::height(par->right_node()->left_node())){
                    par->left_rotate();
                }
                else{
                    par->right_left_rotate();
                }

                break;
            }
            par=par->parent();
        }
        delete cur;
        cur=nullptr;
    }
    else if(cur->left_node()==nullptr){
        if(par==nullptr){
            cur->right_node()->parent(nullptr);
            root=cur->right_node();
        }
        else{
            if(cur->right_node()!=nullptr){
                cur->right_node()->parent(par);
            }
            if(par->left_node()==cur){
                par->left_node(cur->right_node());
            }
            else{
                par->right_node(cur->right_node());
            }
        }
        while(par!=nullptr){
            if((AVLNode<T>::height(par->left_node())-AVLNode<T>::height(par->right_node()))==2){
                //最小失衡树的根节点的 左树比右树高
                if(AVLNode<T>::height(par->left_node()->left_node())>AVLNode<T>::height(par->left_node()->right_node())){
                    par->right_rotate();
                }
                else{
                    par->left_right_rotate();
                }
                break;
            }
            else if((AVLNode<T>::height(par->left_node())-AVLNode<T>::height(par->right_node()))==-2){
                //最小失衡树的根节点的 右树比左树高
                if(AVLNode<T>::height(par->right_node()->right_node())>AVLNode<T>::height(par->right_node()->left_node())){
                    par->left_rotate();
                }
                else{
                    par->right_left_rotate();
                }

                break;
            }
            par=par->parent();
        }
        delete cur;
        cur=nullptr;
    }
    else {
        par=nullptr;
        AVLNode<T> *left_in_right=cur->right_node();
        while (left_in_right->left_node()!=nullptr) {
            par=left_in_right;
            left_in_right=left_in_right->left_node();
        }
        if(par==nullptr){
            par->right_node(left_in_right->right_node());
            cur->data(left_in_right->data());
        }
        else{
            par->left_node(left_in_right->right_node());
            cur->data(left_in_right->data());
        }
        while(par!=nullptr){
            if((AVLNode<T>::height(par->left_node())-AVLNode<T>::height(par->right_node()))==2){
                //最小失衡树的根节点的 左树比右树高
                if(AVLNode<T>::height(par->left_node()->left_node())>AVLNode<T>::height(par->left_node()->right_node())){
                    par->right_rotate();
                }
                else{
                    par->left_right_rotate();
                }
                break;
            }
            else if((AVLNode<T>::height(par->left_node())-AVLNode<T>::height(par->right_node()))==-2){
                //最小失衡树的根节点的 右树比左树高
                if(AVLNode<T>::height(par->right_node()->right_node())>AVLNode<T>::height(par->right_node()->left_node())){
                    par->left_rotate();
                }
                else{
                    par->right_left_rotate();
                }

                break;
            }
            par=par->parent();
        }
        delete left_in_right;
    }
#endif
}

template<typename T>
AVLNode<T> * AVLTree<T>::_remove(AVLNode<T> *&cur, T value)
{
    if(cur!=nullptr){
        if(cur->data()==value){
            if(cur->left_node()!=nullptr&&cur->right_node()!=nullptr){
                if(AVLNode<T>::height(cur->left_node())>AVLNode<T>::height(cur->right_node())){
                    AVLNode<T> * del=AVLNode<T>::maximum(cur->left_node());
                    cur->data(del->data());
                    cur->left_node(_remove(cur->left_node(),del->data()));
                }
                else{
                    AVLNode<T> * del=AVLNode<T>::minimum(cur->right_node());
                    cur->data(del->data());
                    cur->right_node(_remove(cur->right_node(),del->data()));
                }
            }
            else{
                AVLNode<T> *tmp=cur;
                if(cur->left_node()!=nullptr){
                    cur=cur->left_node();
                }
                else{
                    cur=cur->right_node();
                }
                if(cur!=nullptr){
                    cur->parent(tmp->parent());
                }
                delete tmp;
            }
        }
        else if(value<cur->data()){
            cur->left_node(_remove(cur->left_node(),value));
            if(AVLNode<T>::height(cur->right_node())-AVLNode<T>::height(cur->left_node())==2){
                if(AVLNode<T>::height(cur->right_node()->left_node())>AVLNode<T>::height(cur->right_node()->right_node())){
                    cur=cur->right_left_rotate();
                }
                else{
                    cur=cur->left_rotate();
                }
            }
        }
        else{
            cur->right_node(_remove(cur->right_node(),value));
            if(AVLNode<T>::height(cur->right_node())-AVLNode<T>::height(cur->left_node())==-2){
                if(AVLNode<T>::height(cur->left_node()->left_node())>AVLNode<T>::height(cur->left_node()->right_node())){
                    cur=cur->right_rotate();
                }
                else{
                    cur=cur->left_right_rotate();
                }
            }

        }
        return cur;
    }
    else{
        return nullptr;
    }
}

template<typename T>
AVLNode<T>* AVLTree<T>::_insert_recurve(AVLNode<T> *&node, T value)
{
    if(node==nullptr){
        node=new AVLNode<T>(value);
    }
    else if(value<node->data()){    //add to left child
        node->left_node(_insert_recurve(node->left_node(),value));
        if(AVLNode<T>::height(node->left_node())-AVLNode<T>::height(node->right_node())==2){
            if(value<node->left_node()->data()){
                node=node->right_rotate();
            }
            else{
                node=node->left_right_rotate();
            }
        }
    }
    else if(value>node->data()){    //add to right child
//    else{
        node->right_node(_insert_recurve(node->right_node(),value));
        if(AVLNode<T>::height(node->right_node())-AVLNode<T>::height(node->left_node())==2){
            if(value>node->right_node()->data()){
                node=node->left_rotate();
            }
            else{
                node=node->right_left_rotate();
            }
        }

    }
    node->height(max(AVLNode<T>::height(node->left_node()),AVLNode<T>::height(node->right_node()))+1);
    return node;
}



























