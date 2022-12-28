#include "Team.h"
#include "Player.h"


Player::Player(int playerId, const permutation_t &spirit, int gamesPlayed, int games_before_joining,
    int ability, int cards, bool goalKeeper, int index_in_uf): playerId(playerId), spirit(spirit), gamesPlayed(gamesPlayed), games_before_joining(games_before_joining),
    ability(ability), cards(cards), goalkeeper(goalkeeper), index_in_uf(index_in_uf){}


Player& Player::operator=(const Player& other_player)
{
    if(this == &other_player)
    {
        return *this;
    }

    this->playerId = other_player.playerId;
    this->gamesPlayed = other_player.gamesPlayed;
    this->cards = other_player.cards;
    this->games_before_joining = other_player.games_before_joining;
    this->cards = other_player.cards;
    this->goalkeeper = other_player.goalkeeper;
    this->ability = other_player.ability;
    this->spirit = other_player.spirit;

    return *this;
}


bool Player::operator<(const Player& other_player) const
{
    if(this->playerId < other_player.getID())
    {
        return this->playerId;
    }
    
    return other_player.getID();
}


bool Player::operator==(const Player& other_player)const
{
    return (this->playerId == other_player.playerId);
}


bool Player::operator>(const Player& other_player) const
{
    if(this->playerId > other_player.getID())
    {
        return this->playerId;
    }
    
    return other_player.getID();
}

int Player::getID() const
{
    return this->playerId;
}

permutation_t Player::getSpirit() const
{
    return this->spirit;
}

int Player::getIndexInUF() const
{
    return this->index_in_uf;
}

int Player::getGamesPlayed() const
{
    return this->gamesPlayed;
}

int Player::getGamesPlayedBeforeJoin() const
{
    return this->games_before_joining;
}

int Player::getAbility() const
{
    return this->ability;
}

int Player::getCards() const
{
    return this->cards;
}

bool Player::getGoalkeeper() const
{
    return this->goalkeeper;
}




void Player::setCards(int cards_added)
{
    this->cards += cards_added;
}

void Player::setIndexInUF(int new_index)
{
    this->index_in_uf= new_index;
}

void Player::setSpirit(permutation_t spirit)
{
    this->spirit = spirit;
}

void Player::setGamesPlayed(int games_added)
{
    this->gamesPlayed = games_added;
}

void Player::setGamesPlayedBeforeJoin(int games_before_joining)
{
    this->games_before_joining = games_before_joining;
}

void Player::updateGoalkeeper()
{
    if(this->goalkeeper == true)
    {
        this->goalkeeper = false;
    }
    else
    {
        this->goalkeeper = true;
    }
}


