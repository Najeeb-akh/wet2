#ifndef UnionFind
#define UnionFind

#include <iostream>
#include "Team.h"

class PlayerInUF
{
    public:
    int playerId;
    permutation_t spirit;
    permutation_t multspirit;
    int parent;
    int tree_size;
    Team* team; ///null for most elements, only the head of the group points to the team
    permutation_t to_mult;

    PlayerInUF(int playerId, permutation_t spirit, permutation_t multspirit, Team* team = nullptr, int parent = 0, int tree_size = 0,
                 permutation_t to_mult = permutation_t(new int[1,1,1,1,1])):playerId(playerId), spirit(spirit), multspirit(multspirit),team(team), parent(parent), tree_size(0){}
    PlayerInUF():playerId(0), multspirit(), team(nullptr), parent(0), tree_size(1){};
    ~PlayerInUF()
    {
       team = nullptr;
    };
};

/*class Group
{
    public:
    Team* team;
    int num_of_elements;
    int spirit_mult;
    int actual_parent;

    Group(Team* team):team(team), num_of_elements(1), spirit_mult(1), actual_parent(-1){}
    ~Group()
    {
        delete team;
    };
};*/



class UF
{
    
    PlayerInUF** elements;
    int max_size;
    int index;

    public:
    UF();
    /// mult_before might change to spirit of player
    void Insert(int PlayerId, permutation_t mult_before, Team* team = nullptr);
    int getSize() const;
    int getIndex() const;
    void setSize(int new_size);
    PlayerInUF* getElement(int n);
    int Find(int n);
    bool JoinTeam(int n, int m);
    bool Union(int n, int m);
    permutation_t getToMult(int n, permutation_t res, int* last_node);
    permutation_t getToDevide(int n, permutation_t res, int* last_node);
    void ShrinkPath(int root, int son);
    int Findaux(int a);
};

UF::UF():index(0), max_size(0),elements(nullptr){};

void UF::Insert(int PlayerId, permutation_t mult_before,Team* team1)
{
    if(elements == nullptr)
    {
        elements = new PlayerInUF(PlayerId, mult_before, team, index);
        team->setHeadOfTeam(elements);
        max_size = 1;
        index++;
        return;
    }

    if(index == max_size)
    {
       PlayerInUF** new_arr = new PlayerInUF*[max_size*2]; 
       for(int i=0 ; i < max_size ; i++)
       {
          new_arr[i] = elements[i];  
       }

       PlayerInUF** old_uf_to_delete = elements;
       elements = new_arr;
       new_arr = nullptr;
       max_size = 2*max_size;

       delete[] old_uf_to_delete;
       delete new_arr;

    }
    
    elements[index] = PlayerInUF(PlayerId, mult_before, team, index);
    index++;

    if(team1->getHeadOfTeam() != nullptr)
    {
        int head_of_group = team->getHeadOfTeam()->parent;
        JoinTeam(head_of_group, index);
        ///might need to update the head
    }

}

int UF::Find(int a)
{
    int root = Findaux(a);

    int zero = 0;
    int* last_node = &zero;
    permutation_t toMult = this->getToMult(a, permutation_t(new int[1,1,1,1,1]), last_node);
    permutation_t toDevide = permutation_t(new int[1,1,1,1,1]);

    int tmp = a;
    while(tmp != root)
    {
        elements[tmp]->to_mult = toMult * elements[tmp]->to_mult;
        toDevide = toDevide * elements[tmp]->to_mult;
        tmp = elements[tmp]->parent;
    }

    ShrinkPath(root,a);
    return root;
    
    
}

int UF::Findaux(int a)
{
    if (elements[a]->parent == a) 
    {
        return a;
    }

    return Find(elements[a]->parent);
}

void UF::ShrinkPath(int root, int son)
{
    while(son != root)
    {
        int tmp = elements[son]->parent;
        elements[son]->parent = root;
        son = tmp;
    }
}

PlayerInUF* UF::getElement(int n)
{
    return elements[n];
}

bool UF::JoinTeam(int n, int m)
{
    elements[m]->parent = n;
    elements[n]->tree_size += elements[m]->tree_size;
}

bool UF::Union(int n, int m)
{
    if(elements[n]->tree_size > elements[m]->tree_size)
    {
        elements[m]->parent = n;
        elements[n]->tree_size += elements[m]->tree_size;
    }
    else
    {
        elements[n]->parent = m;
        elements[m]->tree_size += elements[n]->tree_size;
    }
}

permutation_t UF::getToMult(int n, permutation_t res, int* last_node)
{
    if(elements[n]->parent = n)
    {
        *last_node = n;
        return res;
    }
    
    return getToMult(elements[n]->parent, elements[n]->to_mult * res, last_node);
}

permutation_t UF::getToDevide(int n, permutation_t res, int* last_node)
{
    if(elements[n]->parent == *last_node)
    {
        return res;
    }

    return getToDevide(elements[n]->parent, elements[n]->to_mult * res, last_node);
}

//     UF(int initial_size = 0)
//     {
//         groups = nullptr; 
//         parent = nullptr; 
//         next = 1;
//     }


//     void Union(int a, int b)
//     {
//         int A=Find(a);
//         int B=Find(b);
//         if(groups[A].num_of_elements < groups[B].num_of_elements){
//             parent[A]=B;
//             groups[B].num_of_elements += groups[A].num_of_elements;
//             groups[A].num_of_elements = 0;
//         }
//         else{
//             parent[B]=A;
//             groups[A].num_of_elements += groups[B].num_of_elements;
//             groups[B].num_of_elements = 0;
//         }
//     }

//     double FindValue(int target)
//     {
//         int root;
//         double value = FindValueAux(target, &root);
//         value += groups[target].value;
//         return value;
//     }


//     double calcValue (int target)
//     {
//         return  groups[target].to_add - groups[target].to_deduct;
//     }

//     int findActualParent (int a)
//     {
//        int root = Find(a);
//        ShrinkPath(root,a);
//        return groups[root].actual_parent;
//     }
    
//     Group* getGroup(int a)
//     {
//         return &groups[a];
//     }
// };


#endif