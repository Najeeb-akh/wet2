#include "worldcup23a2.h"
#include "Team.h"
#include "RankTree.h"
#include "HashTable.h"
#include "UnionFind.h"
#include "Player.h"


//Najeeb
world_cup_t::world_cup_t()
{
	this->teamsId = RankTree<Team>();
	this->teamsAbilities= RankTree<Team>();
	this->allPlayers = HashTable();
	this->unionfind = UF() ;

}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

//Asaad
StatusType world_cup_t::add_team(int teamId)
{
	
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
	if(playerId <= 0 || teamId<= 0 || spirit.isvalid() == false || gamesPlayed < 0 || cards <0)
	{
		return StatusType::INVALID_INPUT;
	}

	//find player's team
	Team tmp_team = Team(teamId);
	if(teamsId.Find(tmp_team) == nullptr)
	{
		return StatusType::FAILURE;
	}

	//insertion into the hash table
	Player* new_player = new Player(playerId, spirit, gamesPlayed, 0, ability, cards,goalKeeper);
	if(allPlayers.Insert(new_player) == false)
	{
		return StatusType::FAILURE;
	}
	
	//insertion into the union find structure
	
	//save the previos mult_spirit
	int last_index = unionfind.getIndex();
	permutation_t last_mult = (teamsId.Find(tmp_team)->InfoPtr()->getMultSpirits());

	PlayerInUF* new_player_inUF = new PlayerInUF(playerId, last_mult, teamsId.Find(tmp_team)->InfoPtr());

	return StatusType::SUCCESS;
}

//Asaad
output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
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
	if(playerId <= 0 || cards < 0)
	{
		return StatusType::INVALID_INPUT;
	}
	if(allPlayers.Find(playerId) == false)
	{
		return StatusType::FAILURE;	
	}
	else
	{
		allPlayers.GetPlayer(playerId)->setCards(cards);
	}

	return StatusType::SUCCESS;
}

//Najeeb
output_t<int> world_cup_t::get_player_cards(int playerId)
{
	if(playerId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

	if(allPlayers.Find(playerId) == false)
	{
		return StatusType::FAILURE;	
	}
	else
	{
		return (allPlayers.GetPlayer(playerId)->getCards());
	}

	
	return StatusType::SUCCESS;
}

//Najeeb
output_t<int> world_cup_t::get_team_points(int teamId)
{
	if(teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	if(teamsId.Find(teamId) == false)
	{
		return StatusType::FAILURE;
	}

	Team tmp_team = Team(teamId);
	return (teamsId.Find(tmp_team)->InfoPtr()->getTotalPoints());
	
	//return 30003;
}

//Asaad
output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

//Asaad
output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
