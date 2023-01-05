#ifndef PLAYER_H
#define PLAYER_H

#include "AVLnode.h"
#include "wet2util.h"

//class permutation_t;

class Player{

    int playerId;
    //Team* team;
    permutation_t spirit;
    int index_in_uf;
    int gamesPlayed;
    int games_before_joining;
    int ability;
    int cards;
    bool goalkeeper;
    

    //pointer to place in array of elements in union find

    public:

    Player(int playerId, permutation_t spirit, int gamesPlayed = 0, int games_before_joining = 0,
                                             int ability = 0, int cards = 0, bool goalKeeper = false, int index_in_uf = -1);

    
    Player():playerId(0){};

    ~Player()=default;

    Player(const Player& player) = default;

    Player& operator=(const Player& other_player);
    
    bool operator<(const Player& other_player) const;

    bool operator==(const Player& other_player) const;

    bool operator>(const Player& other_player) const;

    
    // getId: returns local player id
    int getID() const;
    
    permutation_t getSpirit() const;

    int getGamesPlayed() const;

    int getGamesPlayedBeforeJoin() const;
    
    int getAbility() const;

    int getIndexInUF() const;
    
    //getCards: return the cards of the local player
    int getCards() const;
    
    /** getGoalKeeper: checks whether the local player is a goalkeeper or not 
     * 
     * @return true, in case the local employee is a goalkeeper
     *         Otherwise, false.
     */
    bool getGoalkeeper() const;

    // setcards: set the local player cards field to the param given.
    void setCards(int cards);


    void setSpirit(permutation_t spirit);

    void setIndexInUF(int new_index);

    // setGamesPlayed: set the local player games_played field to the param given.
    void setGamesPlayed(int games_added);

    void setGamesPlayedBeforeJoin(int games_before_joining);

    // updateGamesPlayed: add one to the local player gameplayed field
    void updateGamesPlayed();

    // updateGoalKeeper: switch the player to be a goalkeeper if he isnt,
    //                  and if he is a goalkeeper make him a regular player and not a goalkeeper
    void updateGoalkeeper();

};


#endif