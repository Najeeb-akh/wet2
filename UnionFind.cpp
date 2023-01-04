#include "UnionFind.h"

UF::UF():index(0), max_size(0)
{
    PlayerInUF* dummy = new PlayerInUF(0,0,permutation_t(),permutation_t());
    PlayerInUF** tmp = new PlayerInUF*[1];
    tmp[0] = dummy;
    elements = tmp;
    tmp = nullptr;
}

void UF::Insert(int PlayerId, permutation_t spirit, int games_played, Team* team)
{
    if(elements[0]->playerId == 0)
    {
        *elements = new PlayerInUF(PlayerId, games_played, spirit, spirit, team->getGamesCounter(), 0, team, index, 1);
        team->setHeadOfTeam(0);
        max_size = 1;
        index++;

        int head_of_group = index - 1;
        team->setHeadOfTeam(elements[head_of_group]);
        elements[index - 1]->team = team;
        
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
    
    elements[index] = new PlayerInUF(PlayerId, games_played, spirit, team->getMultSpirits() * spirit, team->getGamesCounter());
    index++;

    if(team->getHeadOfTeam() != nullptr)
    {
        int head_of_group = team->getHeadOfTeam()->parent;
        JoinTeam(head_of_group, index);
        ///might need to update the head
    }
    else
    {
        int head_of_group = index - 1;
        team->setHeadOfTeam(elements[head_of_group]);
        elements[index - 1]->team = team;
    }
}

int UF::Find(int a)
{
    int root = Findaux(a);

    int zero = 0;
    int* last_node = &zero;
    permutation_t toMult = this->getToMult(a, permutation_t(new int[1,2,3,4,5]), last_node);
    permutation_t toDevide = permutation_t(new int[1,2,3,4,5]);

    int tmp = a;
    while(tmp != root)
    {
        elements[tmp]->to_mult = toMult * toDevide.inv();
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
    return true;
}

void UF::Union(int buyer, int bought)
{
    int buyer_size = elements[buyer]->tree_size;
    int bought_size = elements[bought]->tree_size;
    

    //updating the spirit mult
    if(bought_size <= buyer_size)
    {
        elements[buyer]->to_mult = elements[buyer]->to_mult * elements[bought]->multspirit * elements[bought]->to_mult.inv();
    }
    else
    {
        elements[buyer]->to_mult = elements[buyer]->to_mult * elements[bought]->multspirit;
        elements[bought]->to_mult = elements[bought]->to_mult * elements[buyer]->to_mult.inv();
    }

    //updating the games played and delta games
    if(bought_size <= buyer_size)
    {
        elements[bought]->delta_games = elements[bought]->team->getGamesCounter() - elements[buyer]->team->getGamesCounter();
    }
    else
    {
        elements[bought]->delta_games = elements[bought]->team->getGamesCounter() - elements[buyer]->team->getGamesCounter();
        elements[buyer]->delta_games = elements[buyer]->team->getGamesCounter() - elements[bought]->team->getGamesCounter();
    }

    //uniting the 2 groups
    if(bought_size <= buyer_size)
    {
        elements[bought]->parent = buyer;
        elements[bought]->team->setHeadOfTeam(nullptr);
        elements[bought]->team = nullptr;
        elements[buyer]->tree_size += elements[bought]->tree_size;
    }
    else
    {
        elements[buyer]->parent = bought;
        elements[bought]->tree_size += elements[buyer]->tree_size;

        elements[buyer]->team->setHeadOfTeam(elements[bought]);
        elements[bought]->team->setHeadOfTeam(nullptr);
        elements[bought]->team = elements[buyer]->team;
        elements[buyer]->team = nullptr;
    }
    
}

permutation_t UF::calcMultSpirit(int index)
{
    permutation_t res = permutation_t(new int[1,2,3,4,5]);
    while(elements[index]->parent != index)
    {
        res = res * elements[index]->to_mult;
    }
    return res;
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

int UF::getIndex() const
{
    return this->index;
}