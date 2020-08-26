#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <sstream>
#include <cassert>
#include <iomanip>
using namespace std;


template<typename T>
struct INode{
    virtual INode* parent()const{return nullptr;}
    virtual void parent(INode*){}
    virtual INode* left_node()const{return nullptr;}
    virtual void left_node(INode*){}
    virtual INode* right_node()const{return nullptr;}
    virtual void right_node(INode*){}
    virtual T data()const{return T();}
    virtual void data(T){}
    virtual ~INode();
};

template<typename T>
INode<T>::~INode(){}

template<typename T>
struct BaseNode:INode<T>{
    BaseNode():left(nullptr),right(nullptr){}
    BaseNode(T data,BaseNode *l=nullptr,BaseNode *r=nullptr):left(l),right(r),d(data){}
    ~BaseNode(){}
    inline INode<T>* left_node() const{
        return left;
    }
    inline INode<T>* right_node() const{
        return right;
    }

    inline T data() const{
        return d;
    }

    BaseNode *left;
    BaseNode *right;
    T d;
};



template<typename T>
class CBinarySearchTree{
public:
    CBinarySearchTree():root(nullptr){}
    CBinarySearchTree& insert(T value);
    bool remove(T value);
    BaseNode<T>* get_root()const{
        return root;
    }
    BaseNode<T>* get_parent(BaseNode<T>* n);
    int find_node_level(BaseNode<T>* n);
    int find_node_level(T n);
protected:
    CBinarySearchTree& _insert_recurve(BaseNode<T>* &n,T value);
    BaseNode<T> *_get_parent_recurve(BaseNode<T>* r,BaseNode<T>* n);
    int _find_node_level(INode<T> *src,INode<T>* n);
    int _find_node_level(INode<T> *src, T n);
private:
    BaseNode<T> *root;
};


template<typename T>
CBinarySearchTree<T> &CBinarySearchTree<T>::insert(T value)
{

    return _insert_recurve(root,value);
}


template<typename T>
CBinarySearchTree<T> &CBinarySearchTree<T>::_insert_recurve(BaseNode<T>* &n,T value)
{
    if(n==nullptr){
        n=new BaseNode<T>(value);
        return *this;
    }
    if(n->d>value){
        return _insert_recurve(n->left,value);
    }
    else if(n->d<value){
        return _insert_recurve(n->right,value);
    }
    else{
        return *this;
    }
}


#define INTERVAL 2
#define LAYER_LINKER        '|'
#define NODE_TOP            ' '
#define BETEWEEN_TOP        '-'
#define BETWEEN_NODE        ' '
#define NULL_NODE_TOP       ' '
#define BETWEEN_NODE_TOP    ' '
#define NULL_NODE           ' '
#define BETWEEN_LINKER      ' '
template<typename T>
ostream& operator<<(ostream& os,CBinarySearchTree<T>& tree){
    vector<vector<INode<T>*>> v2d;
    v2d.push_back({tree.get_root()});

    for (size_t i=0;;i++) {
        vector<INode<T>*> next_l;
        for_each(v2d[i].begin(),v2d[i].end(),[&next_l](INode<T>* _n){
            if(_n!=nullptr){
                next_l.push_back(_n->left_node());
                next_l.push_back(_n->right_node());
            }
            else{
                next_l.push_back(nullptr);
                next_l.push_back(nullptr);
            }
        });
        if(all_of(next_l.begin(),next_l.end(),[](INode<T>* _n){return _n==nullptr?true:false;})==true){
            break;
        }
        else{
            v2d.push_back(next_l);
        }
    }
    assert(INTERVAL%2==0);
    size_t total_l=v2d.size();

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
                    node<<setw(INTERVAL)<<(*it)->data();
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
                    node<<setw(INTERVAL)<<(*it)->data();
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


template<typename T>
bool CBinarySearchTree<T>::remove(T value)
{
    BaseNode<T>* parent_node=nullptr;
    BaseNode<T>* del_node=root;
    while(del_node!=nullptr){
        if(value<del_node->d){
            parent_node=del_node;
            del_node=del_node->left;
        }
        else if(value>del_node->d){
            parent_node=del_node;
            del_node=del_node->right;
        }
        else{
            break;
        }
    }
    if(del_node==nullptr){
        return false;
    }
    if(del_node->left==nullptr){
        if(parent_node==nullptr){   //说明要删除的是根节点
            root=del_node->right;
        }
        if(parent_node->right==del_node){
            parent_node->right=del_node->right;
        }
        else{
            parent_node->left=del_node->right;
        }
        delete del_node;
    }
    else if(del_node->right==nullptr){
        if(parent_node==nullptr){   //说明要删除的是根节点
            root=del_node->left;
        }
        if(parent_node->right==del_node){
            parent_node->right=del_node->left;
        }
        else{
            parent_node->left=del_node->left;
        }
        delete del_node;
    }
    else{
        parent_node=del_node;
        BaseNode<T>* right_min=del_node->right;
        while(right_min->left!=nullptr){
            parent_node=right_min;
            right_min=right_min->left;
        }
        if(parent_node->left==right_min){
            parent_node->left=right_min->right;
        }
        else{   //没有进while循环的情况
            parent_node->right=right_min->right;
        }
        del_node->d=right_min->d;
        delete right_min;
    }
    return true;
}

template<typename T>
inline BaseNode<T> *CBinarySearchTree<T>::get_parent(BaseNode<T> *n)
{
    return _get_parent_recurve(root,n);
}

template<typename T>
BaseNode<T> *CBinarySearchTree<T>::_get_parent_recurve(BaseNode<T> *r, BaseNode<T> *n)
{
    BaseNode<T> *parent=nullptr;
    if(r->left_node()==n||r->right_node()==n){
        parent= r;
    }
    else{
        _get_parent_recurve(r->left_node(),n);
        _get_parent_recurve(r->right_node(),n);
    }
    return parent;
}

template<typename T>
int CBinarySearchTree<T>::find_node_level(BaseNode<T> *n)
{
    if(root==nullptr||n==nullptr){
        return -1;
    }
    return _find_node_level(root,n);
}

template<typename T>
int CBinarySearchTree<T>::find_node_level(T n)
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
int CBinarySearchTree<T>::_find_node_level(INode<T> *src, INode<T> *n)
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
int CBinarySearchTree<T>::_find_node_level(INode<T> *src,T n)
{
    if(src==nullptr){
        return -1;
    }
    else if(src->data()==n){
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



#endif // BINARY_SEARCH_TREE_H
