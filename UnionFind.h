#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <iostream>
#include "wet2util.h"
#include "Team.h"

class Team;

class PlayerInUF
{
    public:
    //friend class Team;
    int playerId;
    int games_played;
    int initial_team_games;
    int delta_games;
    permutation_t spirit;
    permutation_t multspirit;
    int parent;
    int tree_size;
    Team* team; ///null for most elements, only the head of the group points to the team
    permutation_t to_mult;

    PlayerInUF(int playerId, int games_player, permutation_t spirit, permutation_t multspirit, 
                int initial_team_games = 0, int delta_games = 0, Team* team = nullptr, int parent = 0, int tree_size = 0,
                permutation_t to_mult = permutation_t(new int[0,1,2,3,4])):playerId(playerId), games_played(games_played), spirit(spirit),
                 multspirit(multspirit), initial_team_games(initial_team_games), delta_games(delta_games),team(team),
                parent(parent), tree_size(0){}

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
    
    public:
    //friend class Team;
    PlayerInUF** elements;
    int max_size;
    int index;
    
    
    
    UF();
    /// mult_before might change to spirit of player
    void Insert(int PlayerId, permutation_t spirit, int games_played, Team* team);
    int getSize() const;
    int getIndex() const;
    void setSize(int new_size);
    PlayerInUF* getElement(int n);
    int Find(int n);
    bool JoinTeam(int n, int m);
    void Union(int buyer, int bought);
    permutation_t getToMult(int n, permutation_t res, int* last_node);
    permutation_t getToDevide(int n, permutation_t res, int* last_node);
    void ShrinkPath(int root, int son);
    permutation_t calcMultSpirit(int index);
    int Findaux(int a);
};


#endif