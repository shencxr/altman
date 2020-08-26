#ifndef AVL_H
#define AVL_H

#include "binary_search_tree.h"




template<typename T>
struct AVLNode:public INode<T>{
public:
    AVLNode(T data=T(),AVLNode<T> *l=nullptr,AVLNode<T> *r=nullptr):_left(l),_right(r),_data(data),_depth(0){
        if(l!=nullptr){
            l->parent(this);
        }
        if(r!=nullptr){
            r->parent(this);
        }
    }

    AVLNode<T>* parent()const{return _parent;}
    AVLNode<T>* left_node()const{return _left;}
    void left_node(AVLNode<T>*l){_left=l;}
    AVLNode<T>* right_node()const{return _right;}
    void right_node(AVLNode<T>*r){_right=r;}
    T data()const{return _data;}
    void data(T d){_data=d;}
    int depth(void)const{return _depth;}
    void depth(int d){_depth=d;}

private:
    void parent(AVLNode<T>* p){_parent=p;}
    AVLNode<T> *_parent;
    AVLNode<T> *_left;
    AVLNode<T> *_right;
    T _data;
    int _depth;
};



template<typename T>
class AVLTree{
public:
    bool insert(T value);
    bool remove(T value);
    AVLNode<T>* get_root() const{
        return root;
    }

private:
    AVLNode<T>* root;
};


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
ostream& operator<<(ostream& os,INode<T>* node){
    vector<vector<INode<T>*>> v2d;
    v2d.push_back({node});

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


#endif // AVL_H
