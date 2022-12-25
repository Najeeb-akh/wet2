#include "Team.h"
#include "wet2util.h"

Team::Team(int TeamId, int points, int player_num, bool has_goalkeeper,
           int total_abilities, permutation_t mult_spirits, int games_counter , int goalkeeper_ctr,
           SortByInfo sortingType, bool is_active)
{
    this->TeamId = TeamId;
    this->total_points = points;
    this->players_num = player_num;
    this->has_goalKeeper = has_goalkeeper;
    this->total_abilities = total_abilities;
    this->mult_spirits = mult_spirits;
    this->games_counter = games_counter;
    this->goalKeepersCtr = goalkeeper_ctr;
    this->sortingType = sortingType;
    this->is_active = is_active;
}


Team::Team(const Team& other_team)
{
    this->TeamId = other_team.TeamId;
    this->total_points = other_team.total_points;
    this->players_num = other_team.players_num;
    this->has_goalKeeper = other_team.has_goalKeeper;
    this->total_abilities = other_team.total_abilities;
    this->mult_spirits = other_team.mult_spirits;
    this->games_counter = other_team.games_counter;
    this->goalKeepersCtr = other_team.goalKeepersCtr;
    this->sortingType = other_team.sortingType;
    this->is_active = other_team.is_active;
}

Team& Team::operator= (const Team& other_team)
{
    if(this == &other_team)
    {
        return *this;
    }

    this->TeamId = other_team.TeamId;
    this->total_points = other_team.total_points;
    this->players_num = other_team.players_num;
    this->has_goalKeeper = other_team.has_goalKeeper;
    this->total_abilities = other_team.total_abilities;
    this->mult_spirits = other_team.mult_spirits;
    this->games_counter = other_team.games_counter;
    this->goalKeepersCtr = other_team.goalKeepersCtr;
    this->sortingType = other_team.sortingType;
    this->is_active = other_team.is_active;
    return *this;
}


bool Team::operator<(const Team& other_team) const
{
    if(this->sortingType == TEAM_ID)
    {
        return this->TeamId < other_team.TeamId;
    }

    if(this->sortingType == ABILITIES)
    {
        if(this->total_abilities < other_team.total_abilities)
        {
            return true;
        }

        if(this->total_abilities == other_team.total_abilities && this->TeamId < other_team.TeamId)
        {
            return true;
        }
    }
    return false;
}


bool Team::operator>(const Team& other_team) const
{
    if(this->sortingType == TEAM_ID)
    {
        return this->TeamId > other_team.TeamId;
    }

    if(this->sortingType == ABILITIES)
    {
        if(this->total_abilities > other_team.total_abilities)
        {
            return true;
        }

        if(this->total_abilities == other_team.total_abilities && this->TeamId > other_team.TeamId)
        {
            return true;
        }
    }
    return false;
}


bool Team::operator==(const Team& other_team) const
{
    if(this->sortingType == TEAM_ID)
    {
        if(this->TeamId == other_team.TeamId)
       {
          return true;
       }
    }
    
    if(this->sortingType == ABILITIES)
    {
        if(this->total_abilities == other_team.total_abilities)
       {
          return true;
       }
    }
    return false;
    
}

void Team::addGoalKeepersCtr()
{
    this->goalKeepersCtr++;
}

int Team::getTeamId()
{
    return this->TeamId;
}

int Team::getAbilities()
{
    return this->total_abilities;
}

permutation_t Team::getMultSpirits()
{
    return this->mult_spirits;
}

int Team::getTotalPoints()
{
    return this->total_points;
}

int Team::getScore()
{
    return this->total_points + this->total_abilities;
}

int Team::getNumOfPlayers()
{
    return this->players_num;
}

int Team::getGoalkeepersCtr()
{
    return this->goalKeepersCtr;
}

int Team::getGamesCounter()
{
    return this->games_counter;
}






void Team::setId(int new_id)
{
    this->TeamId = new_id;
}

void Team::setPoints(int points_added)
{
    this->total_points = this->total_points + points_added;
}

void Team::setPlayerNum(int new_player_num)
{
    this->players_num = new_player_num;
}

void Team::setAbiliteis(int ablities_added)
{
    this->total_abilities += ablities_added;
}

void Team::setMultSpirits(permutation_t spirit_to_multiply)
{
    this->mult_spirits = this->mult_spirits * spirit_to_multiply;
}

void Team::setGoalkeeperCtr(int goalkeepers)
{
    this->goalKeepersCtr = goalkeepers;
}

void Team::subtractGoalKeepersCtr()
{
    this->goalKeepersCtr--;

}

void Team::bumpGamesCounter()
{
    this->games_counter += 1;
}


bool Team::canParticipate()
{
    return this->has_goalKeeper;
}
