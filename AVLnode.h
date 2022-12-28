#ifndef AVLnode_H
#define AVLnode_H

#include <stdbool.h>
#include <iostream>
#include <memory>


template <class T>
class AVLnode{
    

public:
    T* info;  
    AVLnode<T>* left; 
    AVLnode<T>* right;  
    AVLnode<T>* parent; 
    int height;
    bool visited;
    int tree_size;
    AVLnode()=default;
    explicit AVLnode(T* info);
    ~AVLnode() = default;
    AVLnode(const AVLnode<T>& node);
    T Info();
    T* InfoPtr();
    void ClearNode();
    AVLnode<T>* Left() const;
    AVLnode<T>* Right() const;
    AVLnode<T>* Parent() const;
    int Height() const;
    int TreeSize() const;
    void setInfo(const T* info);
    
    void setTreeSize(int nodes_inSubtree);
    void setRight(AVLnode<T>* right);
    void setLeft(AVLnode<T>* left);
    void setParent(AVLnode<T>* parent);
    void setHeight(int height);
    bool isVisited() const;
    void setVisited(bool flag);
    
};


template <class T>
AVLnode<T>::AVLnode(T* info): info(info)
{
   right=nullptr;
   left=nullptr;
   parent=nullptr;
   height=0;
   visited=false;
   tree_size=1;
}

template <class T>
AVLnode<T>::AVLnode(const AVLnode<T>& node)
{
    this->info=node.info;
    this->parent=node.parent;
    this->left=node.left;
    this->right=node.right;
    this->height=node.height;
    this->tree_size=node.tree_size;
    this->visited=node.visited;


}
template <class T>
void AVLnode<T>::ClearNode()
{
    delete info;
    right=nullptr;
    left=nullptr;
    parent=nullptr;
}

template <class T>
bool AVLnode<T>::isVisited() const
{
    return visited;
}

template <class T>
void AVLnode<T>::setVisited(bool flag) 
{
    this->visited=flag;
}

template <class T>
T AVLnode<T>::Info() 
{
    return *info;
}

template <class T>
T* AVLnode<T>::InfoPtr() 
{
    return info;
}


template <class T>
AVLnode<T>*AVLnode<T>::Left() const
{
    return this->left;
}

template <class T>
AVLnode<T>* AVLnode<T>::Right() const
{
    return this->right;
}

template <class T>
AVLnode<T>* AVLnode<T>::Parent() const
{
    return this->parent;
}

template <class T>
int AVLnode<T>::Height() const
{
    return this->height;
}

template <class T>
int AVLnode<T>::TreeSize() const
{
    return this->tree_size;
}
template <class T>
void AVLnode<T>::setTreeSize(int nodes_inSubtree)
{
    this->tree_size=nodes_inSubtree;
}

template <class T>
void AVLnode<T>::setInfo(const T* info)
{
    this->info=info;
}

template <class T>
void AVLnode<T>::setLeft(AVLnode<T>* left)
{
    this->left=left;
}

template <class T>
void AVLnode<T>::setRight(AVLnode<T>* right)
{
    this->right=right;
}


template <class T>
void AVLnode<T>::setParent(AVLnode<T>* parent)
{
    this->parent=parent;
}

template <class T>
void AVLnode<T>::setHeight(int height)
{
    this->height=height;
}   


#endif /* AVLnode_H_ */