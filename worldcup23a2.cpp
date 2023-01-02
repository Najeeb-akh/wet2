#include "worldcup23a2.h"
#include "Team.h"
#include "RankTree.h"
#include "HashTable.h"
#include "UnionFind.h"
#include "Player.h"


//Najeeb
world_cup_t::world_cup_t()
{
	RankTree<Team> teamsId;
	RankTree<Team> teamsAbilities;
	HashTable allPlayers;

}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here.
}

//Asaad
StatusType world_cup_t::add_team(int teamId)
{
	if(teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

	Team team_to_find = Team(teamId);
	if(this->teams_tree->Find(team_to_find))
	{
		return StatusType::FAILURE;
	}

	Team* team_to_insert = new Team(teamId);
	this->teams_tree.Insert(team_to_insert);
	return StatusType::SUCCESS;
}

//Asaad
StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

//Najeeb
StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

//Asaad
output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if(teamId1 <= 0 || teamId2 <=0 || teamId1 == teamId2)
	{
		return StatusType::INVALID_INPUT;
	}

	Team team1_to_find = Team(teamId1);
	Team team2_to_find = Team(teamId2);

	AVLnode<Team>* team1 = this->teams_tree.Find(team1_to_find);
	AVLnode<Team>* team2 = this->teams_tree.Find(team2_to_find);
	if(team1 == nullptr || team2 == nullptr)
	{
		return StatusType::FAILURE;
	}

	team1->Info().bumpGamesCounter();
	team2->Info().bumpGamesCounter();

	



	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

//Najeeb
StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

//Najeeb
output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

//Najeeb
output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

//Asaad
output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	if(i < 0)
	{
		return StatusType::INVALID_INPUT;
	}

	if(this->teams_by_abilities == NULL || this->teams_by_abilities->NumOfElements() < i)
	{
		return StatusType::FAILURE;
	}

	return this->teams_by_abilities->Select(i)->info->getTeamId();
}

//Asaad
output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	if()
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
