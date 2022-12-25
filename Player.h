#ifndef PLAYER_H
#define PLAYER_H

#include "Node.h"
#include "wet2util.h"

class Team;
//class permutation_t;

class Player{

    int playerId;
    Team* team;
    permutation_t spirit;
    int gamesPlayed;
    int games_before_joining;
    int ability;
    int cards;
    bool goalkeeper;

    //pointer to place in array of elements in union find

    public:

    Player(int playerId, Team* team, const permutation_t &spirit, int gamesPlayed, int games_before_joining,
                                             int ability, int cards, bool goalKeeper);
    ~Player()=default;

    Player(const Player& player) = default;

    Player& operator=(const Player& other_player);
    
    bool operator<(const Player& other_player) const;

    bool operator==(const Player& other_player) const;

    bool operator>(const Player& other_player) const;

    
    // getId: returns local player id
    int getID() const;

    Team* getPlayersTeam() const;
    
    permutation_t getSpirit() const;

    int getGamesPlayed() const;

    int getGamesPlayedBeforeJoin() const;
    
    int getAbility() const;
    
    //getCards: return the cards of the local player
    int getCards() const;
    
    /** getGoalKeeper: checks whether the local player is a goalkeeper or not 
     * 
     * @return true, in case the local employee is a goalkeeper
     *         Otherwise, false.
     */
    bool getGoalkeeper() const;


    // setTeam: set the local player team into the team given as a param
    void setPLayersTeam(Team* new_team);

    // setcards: set the local player cards field to the param given.
    void setCards(int cards);


    void setSpirit(permutation_t spirit);

    // setGamesPlayed: set the local player games_played field to the param given.
    void setGamesPlayed(int games_added);

    void setGamesPlayedBeforeJoin(int games_before_joining);

    // updateGamesPlayed: add one to the local player gameplayed field
    void updateGamesPlayed();

    // updateGoalKeeper: switch the player to be a goalkeeper if he isnt,
    //                  and if he is a goalkeeper make him a regular player and not a goalkeeper
    void updateGoalkeeper();

    void setTeam(Team* new_team)

};


#endif