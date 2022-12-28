#ifndef RANKTREE_H
#define RANKTREE_H

#include "AVLnode.h"

#define ILLEGAL_BF 2
using std::shared_ptr;

template <class T>
class RankTree
{
    AVLnode<T> *root;
    int numOfElemets;

public:
    explicit RankTree();
    RankTree(AVLnode<T> *root, int n)
    {
        this->root = root;
        this->numOfElemets = n;
    }
    ~RankTree() = default;
    RankTree(const RankTree &tree);
    void ClearTree(AVLnode<T> *root);
    void clear();
    int calcHeight(AVLnode<T> *root) const;
    int calcTreeSize(AVLnode<T> *root) const;
    int BalanceFactor(AVLnode<T> *node) const;

    AVLnode<T> *Select(int k) const;
    AVLnode<T> *Select(int k, AVLnode<T> *root) const;

    int NumOfElements() const;
    void setNumOfElements(int num_of_elements);

    AVLnode<T> *LL_Rotation(AVLnode<T> *root);
    AVLnode<T> *RR_Rotation(AVLnode<T> *root);
    AVLnode<T> *LR_Rotation(AVLnode<T> *root);
    AVLnode<T> *RL_Rotation(AVLnode<T> *root);

    void Insert(T *info);
    AVLnode<T> *Insert(T *info, AVLnode<T> *root);
    void DeleteNode(T *info);
    AVLnode<T> *deleteNode(AVLnode<T> *node, T *info, bool flag, int counter);
    void ClearTreeNoDelete(AVLnode<T> *root);
    void ClearTreeNoDeleteAux(AVLnode<T> *root);
    void DeleteActiveNode(const T *info);
    AVLnode<T> *deleteActiveNode(AVLnode<T> *node, const T *info);

    AVLnode<T> *FindMaxElement(AVLnode<T> *node);
    AVLnode<T> *FindMinElement(AVLnode<T> *node);
    AVLnode<T> *Find(AVLnode<T> *root, const T &value) const;
    AVLnode<T> *Find(const T &value) const;
    int Rank(AVLnode<T>* root,const T &value) const;

    AVLnode<T> *getRoot() const;
    void setRoot(AVLnode<T> *new_root);
    bool operator<(const RankTree<T> &tree) const;
    bool operator==(const RankTree<T> &tree) const;
    bool operator>(const RankTree<T> &tree) const;
};


template <class T>
void RankTree<T>::ClearTreeNoDelete(AVLnode<T> *root)
{
    ClearTreeNoDeleteAux(root);

    this->numOfElemets = 0;
    this->root = nullptr;
}

template <class T>
void RankTree<T>::clear()
{
    ClearTree(this->root);

    this->num_of_elements = 0;
    this->root = nullptr;
}

template <class T>
void RankTree<T>::DeleteActiveNode(const T *info)
{
    this->root = deleteActiveNode(this->root, info);
    numOfElemets--;
}

template <class T>
AVLnode<T> *RankTree<T>::deleteActiveNode(AVLnode<T> *node, const T *info)
{

    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->right == nullptr && node->left == nullptr)
    {
        if (*(node->info) == *info)
        {
            delete node;
        }
        return nullptr;
    }

    if (*(node->info) > *info)
    {
        node->left = deleteActiveNode(node->left, info);
        if (node->left != nullptr)
        {
            node->left->parent = node;
        }
    }

    else if (*(node->info) < *info)
    {
        node->right = deleteActiveNode(node->right, info);
        if (node->right != nullptr)
        {
            node->right->parent = node;
        }
    }

    else
    {
        if (node->right != nullptr)
        {
            AVLnode<T> *leaf = node->right;
            while (leaf->left != nullptr)
            {
                leaf = leaf->left;
            }

            node->info = leaf->info;

            node->right = deleteActiveNode(node->right, leaf->info);

            if (node->right != nullptr)
            {
                node->right->parent = node;
            }
        }

        else
        {
            AVLnode<T> *leaf = node->left;
            while (leaf->right != nullptr)
            {
                leaf = leaf->right;
            }

            node->info = leaf->info;

            node->left = deleteActiveNode(node->left, leaf->info);

            if (node->left != nullptr)
            {
                node->left->parent = node;
            }
        }
    }

    node->height = calcHeight(node);
    node->setTreeSize(calcTreeSize(node));

    int bf = BalanceFactor(node);
    if (bf == 2 && BalanceFactor(node->left) >= 0)
    {
        node = LL_Rotation(node);
    }
    if (bf == 2 && BalanceFactor(node->left) == -1)
    {
        node = LR_Rotation(node);
    }
    if (bf == -2 && BalanceFactor(node->right) <= 0)
    {
        node = RR_Rotation(node);
    }
    if (bf == -2 && BalanceFactor(node->right) == 1)
    {
        node = RL_Rotation(node);
    }

    return node;
}

template <class T>
RankTree<T>::RankTree()
{
    this->root = nullptr;
    this->numOfElemets = 0;
}

template <class T>
void RankTree<T>::ClearTree(AVLnode<T> *root)
{
    if (root == nullptr)
    {
        return;
    }

    ClearTree(root->Left());
    ClearTree(root->Right());
    root->ClearNode();
    delete root;
    root = nullptr;
}

template <class T>
void RankTree<T>::ClearTreeNoDeleteAux(AVLnode<T> *root)
{
    if (root == nullptr)
    {
        return;
    }

    ClearTreeNoDeleteAux(root->Left());
    ClearTreeNoDeleteAux(root->Right());

    delete root;
    root = nullptr;
}

template <class T>
RankTree<T>::RankTree(const RankTree &tree)
{
    this->root = tree.root;
    this->numOfElemets = tree.numOfElemets;
}

template <class T>
AVLnode<T> *RankTree<T>::Select(int k) const
{
    return Select(k, this->root);
}

template <class T>
int RankTree<T>::Rank(AVLnode<T>* root, const T &value) const
{
    if (root != nullptr)
    {
        if (value > root->Info())
        {
            if(root->left)
            {
                return 1 + root->left->tree_size + Rank(root->Right(), value);
            }
            else
            {
                return 1 + Rank(root->Right(), value);
            }
        }
        else if (value < root->Info())
        {
            return Rank(root->Left(), value);
        }
        else
        {
            if(root->left)
            {
                return 1 + root->left->tree_size;
            }
            else
            {
                return 1;
            }
        }
    }

    return 0;
}

template <class T>
AVLnode<T> *RankTree<T>::Select(int k, AVLnode<T> *root) const
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->Left() == nullptr)
    {
        if (k == 1)
        {
            return root;
        }
        else if (k > 1)
        {
            return Select(k - 1, root->Right());
        }
        else
        {
            return nullptr; //not supposed to get here
        }
    }
    if (root->Left()->TreeSize() > k - 1)
    {
        return Select(k, root->Left());
    }

    if (root->Left()->TreeSize() == k - 1)
    {
        return root;
    }

    return Select(k - root->Left()->TreeSize() - 1, root->Right());
}

template <class T>
int RankTree<T>::NumOfElements() const
{
    return numOfElemets;
}

template <class T>
void RankTree<T>::setNumOfElements(int num_of_elements)
{
    this->numOfElemets = num_of_elements;
}

template <class T>
int RankTree<T>::calcHeight(AVLnode<T> *node) const
{
    if (node->Left() && node->Right())
    {
        int left = node->Left()->Height();
        int right = node->Right()->Height();

        return left > right ? left + 1 : right + 1;
    }
    else if (node->Left() && node->Right() == nullptr)
    {
        return node->Left()->Height() + 1;
    }
    else if (node->Left() == nullptr && node->Right())
    {
        return node->Right()->Height() + 1;
    }
    return 0;
}

template <class T>
int RankTree<T>::calcTreeSize(AVLnode<T> *node) const
{
    if (node == nullptr)
    {
        return 0;
    }

    if (node->Left() && node->Right())
    {
        return node->Left()->TreeSize() + node->Right()->TreeSize() + 1;
    }

    else if (node->Left() && node->Right() == nullptr)
    {
        return node->Left()->TreeSize() + 1;
    }
    
    else if (node->Left() == nullptr && node->Right())
    {
        return node->Right()->TreeSize() + 1;
    }
    return 1;
    
}

template <class T>
int RankTree<T>::BalanceFactor(AVLnode<T> *root) const
{
    int balance = 0;
    if (root->Left() != nullptr && root->Right() != nullptr)
    {
        balance = root->Left()->Height() - root->Right()->Height();
    }
    else if (root->Left() != nullptr && root->Right() == nullptr)
    {
        balance = root->Left()->Height() + 1;
    }
    else if (root->Right() != nullptr)
    {
        balance = -1 - (root->Right()->Height());
    }
    return balance;
}

template <class T>
AVLnode<T> *RankTree<T>::LL_Rotation(AVLnode<T> *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    AVLnode<T> *new_root = root->Left();
    AVLnode<T> *LR_sub = new_root->Right();

    // rotate
    new_root->setRight(root);
    new_root->setParent(nullptr);
    root->setParent(new_root);
    root->setLeft(LR_sub);
    if (LR_sub != nullptr)
    {
        LR_sub->setParent(root);
    }

    root->setHeight(calcHeight(root));
    root->setTreeSize(calcTreeSize(root));
    new_root->setHeight(calcHeight(new_root));
    new_root->setTreeSize(calcTreeSize(new_root));

    return new_root;
}



template <class T>
AVLnode<T> *RankTree<T>::RR_Rotation(AVLnode<T> *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    AVLnode<T> *new_root = root->Right();
    AVLnode<T> *RL_sub = new_root->Left();

    // rotate
    new_root->setLeft(root);
    new_root->setParent(nullptr);
    root->setParent(new_root);
    root->setRight(RL_sub);
    if (RL_sub != nullptr)
    {
        RL_sub->setParent(root);
    }

    root->setHeight(calcHeight(root));
    root->setTreeSize(calcTreeSize(root));
    new_root->setHeight(calcHeight(new_root));
    new_root->setTreeSize(calcTreeSize(new_root));

    return new_root;
}



template <class T>
AVLnode<T> *RankTree<T>::RL_Rotation(AVLnode<T> *root)
{

    AVLnode<T> *R_sub = root->Right();
    AVLnode<T> *RL_sub = R_sub->Left();
    root->setRight(RL_sub->Left());
    if ((RL_sub->Left()) != nullptr)
    {
        (RL_sub->Left())->setParent(root);
    }
    R_sub->setLeft(RL_sub->Right());
    if (RL_sub->Right() != nullptr)
    {
        (RL_sub->Right())->setParent(R_sub);
    }

    AVLnode<T> *new_root = RL_sub;
    new_root->setLeft(root);
    new_root->setParent(nullptr);
    root->setParent(new_root);
    new_root->setRight(R_sub);
    if (R_sub != nullptr)
    {
        R_sub->setParent(new_root);
        R_sub->setHeight(calcHeight(R_sub));
        R_sub->setTreeSize(calcTreeSize(R_sub));
    }
    root->setHeight(calcHeight(root));
    root->setTreeSize(calcTreeSize(root));
    new_root->setHeight(calcHeight(new_root));
    new_root->setTreeSize(calcTreeSize(new_root));

    return new_root;
}



template <class T>
AVLnode<T> *RankTree<T>::LR_Rotation(AVLnode<T> *root)
{

    AVLnode<T> *L_sub = root->Left();
    AVLnode<T> *LR_sub = L_sub->Right();
    root->setLeft(LR_sub->Right());
    if ((LR_sub->Right()) != nullptr)
    {
        (LR_sub->Right())->setParent(root);
    }
    L_sub->setRight(LR_sub->Left());
    if ((LR_sub->Left()) != nullptr)
    {
        (LR_sub->Left())->setParent(L_sub);
    }

    AVLnode<T> *new_root = LR_sub;
    new_root->setRight(root);
    new_root->setParent(nullptr);
    root->setParent(new_root);
    new_root->setLeft(L_sub);
    if (L_sub != nullptr)
    {
        L_sub->setParent(new_root);
        L_sub->setHeight(calcHeight(L_sub));
        L_sub->setTreeSize(calcTreeSize(L_sub));
    }

    root->setHeight(calcHeight(root));
    root->setTreeSize(calcTreeSize(root));
    new_root->setHeight(calcHeight(new_root));
    new_root->setTreeSize(calcTreeSize(new_root));
    ;

    return new_root;
}



template <class T>
void RankTree<T>::Insert(T *info)
{
    this->root = Insert(info, root);
    numOfElemets++;
}

template <class T>
AVLnode<T> *RankTree<T>::Insert(T *info, AVLnode<T> *curr_root)
{

    if (curr_root == nullptr)
    {
        AVLnode<T> *new_node = new AVLnode<T>(info);
        curr_root = new_node;
        return curr_root;
    }
    else if (*info < curr_root->Info())
    {
        AVLnode<T> *left_child = Insert(info, curr_root->Left());
        curr_root->setLeft(left_child);
        if (left_child != nullptr)
        {
            left_child->setParent(curr_root);
        }
    }
    else if (*info > curr_root->Info())
    {
        AVLnode<T> *right_child = Insert(info, curr_root->Right());
        curr_root->setRight(right_child);
        if (right_child != nullptr)
        {
            right_child->setParent(curr_root);
        }
    }

    curr_root->setHeight(calcHeight(curr_root));
    curr_root->setTreeSize(calcTreeSize(curr_root));

    // Left Left Case
    if (BalanceFactor(curr_root) == ILLEGAL_BF && BalanceFactor(curr_root->Left()) >= 0)
    {
        return LL_Rotation(curr_root);
    }

    // Right Right Case
    if (BalanceFactor(curr_root) == -ILLEGAL_BF && BalanceFactor(curr_root->Right()) <= 0)
    {
        return RR_Rotation(curr_root);
    }

    // Left Right Case
    if (BalanceFactor(curr_root) == ILLEGAL_BF && BalanceFactor(curr_root->Left()) == -1)
    {
        return LR_Rotation(curr_root);
    }

    // Right Left Case
    if (BalanceFactor(curr_root) == -ILLEGAL_BF && BalanceFactor(curr_root->Right()) == 1)
    {
        return RL_Rotation(curr_root);
    }

    return curr_root;
}


template <class T>
void RankTree<T>::DeleteNode(T *info)
{
    this->root = deleteNode(this->root, info, false, 0);
    numOfElemets--;
}

template <class T>
AVLnode<T> *RankTree<T>::deleteNode(AVLnode<T> *node, T *info, bool flag, int counter)
{

    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->right == nullptr && node->left == nullptr)
    {
        if (node == this->root)
        {
            delete node->info;
            delete node;
            return nullptr;
        }

        if (*(node->info) == *info)
        {
            if (!flag)
            {
                delete node->info;
            }
            delete node;
        }
        return nullptr;
    }

    if (*(node->info) > *info)
    {
        node->left = deleteNode(node->left, info, flag, counter);
        if (node->left != nullptr)
        {
            node->left->parent = node;
        }
    }

    else if (*(node->info) < *info)
    {
        node->right = deleteNode(node->right, info, flag, counter);
        if (node->right != nullptr)
        {
            node->right->parent = node;
        }
    }

    else
    {
        flag = true;
        if (node->right != nullptr)
        {
            AVLnode<T> *leaf = node->right;
            while (leaf->left != nullptr)
            {
                leaf = leaf->left;
            }

            if (counter == 0)
            {
                delete node->info;
            }

            node->info = leaf->info;

            counter++;
            node->right = deleteNode(node->right, leaf->info, flag, counter);

            if (node->right != nullptr)
            {
                node->right->parent = node;
            }
        }

        else
        {
            AVLnode<T> *leaf = node->left;
            while (leaf->right != nullptr)
            {
                leaf = leaf->right;
            }

            if (counter == 0)
            {
                delete node->info;
            }

            node->info = leaf->info;

            counter++;
            node->left = deleteNode(node->left, leaf->info, flag, counter);

            if (node->left != nullptr)
            {
                node->left->parent = node;
            }
        }
    }

    node->height = calcHeight(node);
    node->setTreeSize(calcTreeSize(node));
    int bf = BalanceFactor(node);
    if (bf == 2 && BalanceFactor(node->left) >= 0)
    {
        node = LL_Rotation(node);
    }
    if (bf == 2 && BalanceFactor(node->left) == -1)
    {
        node = LR_Rotation(node);
    }
    if (bf == -2 && BalanceFactor(node->right) <= 0)
    {
        node = RR_Rotation(node);
    }
    if (bf == -2 && BalanceFactor(node->right) == 1)
    {
        node = RL_Rotation(node);
    }

    return node;
}


template <class T>
AVLnode<T> *RankTree<T>::FindMaxElement(AVLnode<T> *node)
{
    AVLnode<T> *ptr = node;
    while (ptr->Right() != nullptr)
    {
        ptr = ptr->Right();
    }
    return ptr;
}

template <class T>
AVLnode<T> *RankTree<T>::FindMinElement(AVLnode<T> *node)
{
    AVLnode<T> *ptr = node;

    while (ptr->Left() != nullptr)
    {
        ptr = ptr->Left();
    }
    return ptr;
}

template <class T>
AVLnode<T> *RankTree<T>::getRoot() const
{
    return this->root;
}

template <class T>
void RankTree<T>::setRoot(AVLnode<T> *new_root)
{
    this->root = new_root;
}

template <class T>
AVLnode<T> *RankTree<T>::Find(AVLnode<T> *root, const T &value) const
{
    if (root != nullptr)
    {
        if (value > root->Info())
        {
            return Find(root->Right(), value);
        }
        else if (value < root->Info())
        {
            return Find(root->Left(), value);
        }
        else
        {
            return root;
        }
    }

    return nullptr;
}

template <class T>
AVLnode<T> *RankTree<T>::Find(const T &value) const
{
    return Find(root, value);
}

template <class T>
bool RankTree<T>::operator==(const RankTree<T> &tree) const
{
    return this->root->Info() == tree.root->Info();
}

template <class T>
bool RankTree<T>::operator<(const RankTree<T> &tree) const
{
    return this->root->Info() < tree.root->Info();
}

template <class T>
bool RankTree<T>::operator>(const RankTree<T> &tree) const
{
    return this->root->Info() > tree.root->Info();
}

#endif /*RankTree_H_*/












