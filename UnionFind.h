#ifndef UnionFind
#define UnionFind

#include <iostream>
#include <memory>
#include "Team.h"

class PlayerInUF
{
    public:
    int playerId;
    permutation_t multspirit;
    PlayerInUF* parent;
    Team* team;

    PlayerInUF(int playerId, permutation_t multspirit, Team* team = nullptr, PlayerInUF* parent = nullptr):playerId(playerId), multspirit(multspirit), PlayerInUF(PlayerInUF),
                                                                                                            team(team){}
    
    ~PlayerInUF()
    {
        delete team;
        delete parent;
    };

};

class Group
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
};



class UF
{
    public:
    PlayerInUF* elements;
    Group* teams;
    int index_players;
    int index_teams;

    UF(): index_players(0), index_teams(0)
    {
        elements = nullptr;
        teams = nullptr;
    }

    //~UnionFind() = default;
    // void AddMember(Team* team_to_add)
    // {
    //     teams[index_teams].= next;
    //     teams[index].num_of_elements = 1;
    //     teams[index].actual_parent = next;
    //     teams[index];
    //     next++;
    // }




};


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

//     int Find(int a)
//     {
//        int root = Find_Aux(a);
//        ShrinkPath(root,a);
//        return root;
//     }

//     int Find_Aux(int a)
//     {
//         if (parent[a] == a) {
//             return a;
//         }

//         return Find(parent[a]);
//     }

//     void ShrinkPath(int root, int son)
//     {
//         while(parent[son] != root)
//         {
//             int tmp = son;
//             groups[son].to_add += groups[parent[tmp]].to_add;
//             groups[son].to_deduct += groups[parent[tmp]].to_deduct;
//             parent[son] = root;
//             son = parent[tmp];
//         }
//     }

//     double FindValue(int target)
//     {
//         int root;
//         double value = FindValueAux(target, &root);
//         value += groups[target].value;
//         return value;
//     }

//     double FindValueAux(int target, int* root)
//     {
//         if (parent[target] == target) 
//         {
//             *root = target;
//             return calcValue(target);
//         }

//         return calcValue(target) + FindValueAux(parent[target], root);
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