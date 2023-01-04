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
	if(this->teamsId.Find(team_to_find))
	{
		return StatusType::FAILURE;
	}

	Team* team_to_insert = new Team(teamId);
	this->teamsId.Insert(team_to_insert);
	return StatusType::SUCCESS;
}

//Asaad
StatusType world_cup_t::remove_team(int teamId)
{
	if(teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}

	Team tmp_team = Team(teamId);
	if(this->teamsId.Find(tmp_team) == nullptr)
	{
		return StatusType::FAILURE;
	}

	AVLnode<Team>* team_to_delete = this->teamsId.Find(tmp_team);

	Team* team_to_find = new Team(teamId, tmp_team.getTotalPoints(), tmp_team.getNumOfPlayers(), tmp_team.canParticipate(), tmp_team.getAbilities());
	team_to_find->setSortingType(SortByInfo::ABILITIES);

	AVLnode<Team>* team_by_ability_to_delete = this->teamsAbilities.Find(*team_to_find);

	delete team_to_find;
	PlayerInUF* headOfGroup = team_to_delete->InfoPtr()->getHeadOfTeam();

	team_to_delete->Info().setHeadOfTeam(nullptr);
	team_to_delete->Info().deactivateTeam();

	team_by_ability_to_delete->Info().setHeadOfTeam(nullptr);
	team_by_ability_to_delete->Info().deactivateTeam();

	Team* team_outside_of_tree = new Team(team_to_delete->InfoPtr()->getTeamId(), team_to_delete->InfoPtr()->getTotalPoints(),
										 team_to_delete->InfoPtr()->getNumOfPlayers(), true, team_to_delete->InfoPtr()->getAbilities()
										 ,team_to_delete->InfoPtr()->getMultSpirits(), team_to_delete->InfoPtr()->getGamesCounter());
										 
	
	headOfGroup->team = team_outside_of_tree;
	this->teamsId.DeleteNode(team_to_delete->InfoPtr());
	this->teamsAbilities.DeleteNode(team_by_ability_to_delete->InfoPtr());

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
	Player* new_player = new Player(playerId, spirit, gamesPlayed, 0, ability, cards,goalKeeper, this->unionfind.getIndex());
	if(allPlayers.Insert(new_player) == false)
	{
		return StatusType::FAILURE;
	}
	
	//insertion into the union find structure
	
	//save the previos mult_spirit
	int last_index = unionfind.getIndex();
	permutation_t last_mult = (teamsId.Find(tmp_team)->InfoPtr()->getMultSpirits());

	PlayerInUF* new_player_in_uf = new PlayerInUF(playerId,gamesPlayed ,spirit, last_mult * spirit, teamsId.Find(tmp_team)->InfoPtr()->getGamesCounter(), 0);

	///updating team details
	AVLnode<Team>* target_team = this->teamsId.Find(tmp_team);
	target_team->InfoPtr()->setPlayerNum(target_team->InfoPtr()->getNumOfPlayers() + 1);
	target_team->InfoPtr()->setMultSpirits(spirit);
	target_team->InfoPtr()->setAbiliteis(ability);
	if(goalKeeper)
	{
		target_team->InfoPtr()->addGoalKeepersCtr();
		target_team->InfoPtr()->setHasGoalKeeper(true);
	}


	//updating team in ability tree
	tmp_team.setAbiliteis(target_team->InfoPtr()->getAbilities() - ability);
	tmp_team.setSortingType(SortByInfo::ABILITIES);

	Team* team_to_insert = new Team(teamId, target_team->InfoPtr()->getTotalPoints(), target_team->InfoPtr()->getNumOfPlayers(),
										target_team->InfoPtr()->canParticipate(), target_team->InfoPtr()->getAbilities(), target_team->InfoPtr()->getMultSpirits());
	
	team_to_insert->setSortingType(SortByInfo::ABILITIES);

	if(this->teamsAbilities.Find(tmp_team) == nullptr)
	{
		Team* team_to_insert = new Team(teamId, target_team->InfoPtr()->getTotalPoints(), target_team->InfoPtr()->getNumOfPlayers(),
										target_team->InfoPtr()->canParticipate(), target_team->InfoPtr()->getAbilities(), target_team->InfoPtr()->getMultSpirits());
		team_to_insert->setSortingType(SortByInfo::ABILITIES);
		this->teamsAbilities.Insert(team_to_insert);
	}
	else
	{
		this->teamsAbilities.DeleteNode(this->teamsAbilities.Find(tmp_team)->InfoPtr());

		Team* team_to_insert = new Team(teamId, target_team->InfoPtr()->getTotalPoints(), target_team->InfoPtr()->getNumOfPlayers(),
										target_team->InfoPtr()->canParticipate(), target_team->InfoPtr()->getAbilities(), target_team->InfoPtr()->getMultSpirits());
		
		team_to_insert->setSortingType(SortByInfo::ABILITIES);
		this->teamsAbilities.Insert(team_to_insert);
	}

	//PlayerInUF* new_player_inUF = new PlayerInUF(playerId, last_mult, teamsId.Find(tmp_team)->InfoPtr());


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

	AVLnode<Team>* team1 = this->teamsId.Find(team1_to_find);
	AVLnode<Team>* team2 = this->teamsId.Find(team2_to_find);
	if(team1 == nullptr || team2 == nullptr || team1->InfoPtr()->canParticipate() == false || team2->InfoPtr()->canParticipate() == false)
	{
		return StatusType::FAILURE;
	}

	team1->Info().bumpGamesCounter();
	team2->Info().bumpGamesCounter();

	if(team1->Info().getScore() > team2->Info().getScore() || (team1->Info().getScore() == team2->Info().getScore() &&
												 team1->InfoPtr()->getMultSpirits().strength() > team2->InfoPtr()->getMultSpirits().strength()))
	{
		team1->InfoPtr()->setPoints(3);
	}

	if(team1->Info().getScore() < team2->Info().getScore() || (team1->Info().getScore() == team2->Info().getScore() &&
												team1->InfoPtr()->getMultSpirits().strength() < team2->InfoPtr()->getMultSpirits().strength()))
	{
		team2->InfoPtr()->setPoints(3);
	}

	if(team1->Info().getScore() == team2->Info().getScore() &&
				 team1->InfoPtr()->getMultSpirits().strength() == team2->InfoPtr()->getMultSpirits().strength())
	{
		team1->InfoPtr()->setPoints(1);
		team2->InfoPtr()->setPoints(1);
	}
	

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{

	if(playerId <= 0)
	{
		return StatusType::INVALID_INPUT; 
	}

	if(allPlayers.Find(playerId) == false)
	{
		return StatusType::FAILURE; 
	}

	int index_in_uf = allPlayers.GetPlayer(playerId)->getIndexInUF();
	int parent_index = unionfind.getElement(index_in_uf)->parent;
	int next_index= parent_index;
	int delta_sum = 0 ;
	//now we calculate by the equation
	while(unionfind.getElement(next_index)->parent != parent_index)
	{
		delta_sum +=  unionfind.getElement(next_index)->delta_games;
		next_index = unionfind.getElement(next_index)->parent;
	}

	int num = unionfind.getElement(parent_index)->team->getGamesCounter() + delta_sum - unionfind.getElement(index_in_uf)->games_played;

	return num;
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
	if(this->teamsAbilities.NumOfElements() == 0 || this->teamsAbilities.NumOfElements() < i || i < 0)
	{
		return StatusType::FAILURE;
	}

	return this->teamsAbilities.Select(i)->info->getTeamId();
}

//Asaad
output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	//invalid input
	if(playerId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	
	//player is not found
	if(allPlayers.Find(playerId) == false)
	{
		return StatusType::FAILURE;	
	}
	
	//find player inside the hash table
	int index_in_uf = allPlayers.GetPlayer(playerId)->getIndexInUF();
	//player got exceluded out of the game
	if(unionfind.getElement(index_in_uf)->team->isActive() == false)
	{
		return StatusType::FAILURE;	
	}
	
	// then find the mult spirit for the playerInUF 
	
	return unionfind.calcMultSpirit(index_in_uf);
	
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if(teamId1 <=0 || teamId2 <=0)
	{
		return StatusType::INVALID_INPUT;
	}
	
	Team tmp_team1 = Team(teamId1);
	Team tmp_team2 = Team(teamId2);
	
	if(teamsId.Find(tmp_team1) == false || teamsId.Find(tmp_team2) == false)
	{
		return StatusType::FAILURE;
	}

	Team* team1_ptr =  teamsId.Find(tmp_team1)->InfoPtr();
	Team* team2_ptr =  teamsId.Find(tmp_team2)->InfoPtr();

	this->unionfind.Union(team1_ptr->getHeadOfTeam()->parent, team2_ptr->getHeadOfTeam()->parent);
	return StatusType::SUCCESS;
}
