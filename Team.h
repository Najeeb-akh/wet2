#ifndef TEAM_H
#define TEAM_H

#include "wet2util.h"
#include "UnionFind.h"

class PlayerInUF;

typedef enum{
    TEAM_ID = 0,
    ABILITIES = 1,
} SortByInfo;

class Team
{


    public:
    int TeamId;
    int total_points;
    int players_num;
    bool has_goalKeeper;
    int total_abilities;
    permutation_t mult_spirits;
    int games_counter;
    int goalKeepersCtr;
    SortByInfo sortingType;
    bool is_active;
    PlayerInUF* head_of_team;
    /**
     * @brief Construct a new Team object
     * 
     * @param TeamId 
     * @param points 
     */
        // Team(int TeamId, int points);

        Team(int TeamId, int total_points= 0, int player_num = 0, bool has_goalkeeper=false,
                         int total_abilities = 0, permutation_t mult_spirits = permutation_t(), int games_counter = 0, int goalKeeperCtr = 0,
                         SortByInfo sortingType = TEAM_ID, bool is_active = true, PlayerInUF* head_of_team = nullptr);
        /**
         * @brief Destroy the Team object
         * 
         */
        ~Team()=default;

        /**
         * @brief copy constructor for Team
         * 
         * @param team 
         */
        Team(const Team& other_team);



        //--------------operators--------------



        /**
         * @brief assignment operator for team
         * 
         * @param other_team 
         * @return Team& 
         */
        Team& operator=(const Team& other_team);

        /**
         * @brief operator < for team
         * 
         * @param other_team 
         * @return true 
         * @return false 
         */
        bool operator<(const Team& other_team) const;

        /**
         * @brief operator > for team
         * 
         * @param other_team 
         * @return true 
         * @return false 
         */
        bool operator>(const Team& other_team) const;

        //bool operator<=(const Team& other_team);
        //bool operator>=(const Team& other_team);

        /**
         * @brief operator == for Team
         * 
         * @param other_team 
         * @return true 
         * @return false 
         */
        bool operator==(const Team& other_team) const;



        //---------get functions----------


        /**
         * @brief Get the Team Id
         * 
         * @return int 
         */
        int getTeamId();
        

        /**
         * @brief Get the Total Goals in Team
         * 
         * @return int 
         */
        int getAbilities();


        /**
         * @brief Get the Total Cards in Team
         * 
         * @return int 
         */
        permutation_t getMultSpirits();

        /**
         * @brief Get the Total Points in Team
         * 
         * @return int 
         */
        int getTotalPoints();

        /**
         * @brief Get the Score object
         * 
         * @return int 
         */
        int getScore();
        
        /**
         * @brief Get the Num Of Players in Team
         * 
         * @return int 
         */
        int getNumOfPlayers();


        /**
         * @brief Get the Goalkeepers Ctr object
         * 
         * @return int 
         */
        int getGoalkeepersCtr();


        /**
         * @brief get the Total Cards for the team
         * 
         */
        int getGamesCounter();

        SortByInfo getSortingType();

        PlayerInUF* getHeadOfTeam();

        bool isActive();

        
        //-------------set functions-------------

        /**
         *
         * @brief Set the id field for the team
         * @param new_id
         */
        void setId(int new_id);
        /**
         * @brief Add/subtract points to/from the team
         * 
         * @param points_added 
         */
        void setPoints(int points_added);


        /**
         * @brief Set the Total Players for the team
         * 
         * @param new_players_num 
         */
        void setPlayerNum(int new_players_num);


        /**
         * @brief Set the Total Goals for the team
         * 
         * @param goals_added 
         */
        void setAbiliteis(int ability_added);


        void setGoalkeeperCtr(int goalkeepers);
        

        /**
         * @brief Set the Total Cards for the team
         * 
         * @param cards_added 
         */
        void setMultSpirits(permutation_t spirit_to_multiply);

        
        /**
         * @brief changes the 'hasGoalKeeper' to the given parameter
         * 
         * 
         */
        void setHasGoalKeeper(bool changed_value);


        void setHeadOfTeam(PlayerInUF* new_head);

        
        /**
         * @brief adds the goalKeepers counter by 1
         * 
         */
        void addGoalKeepersCtr();


        /**
         * @brief subtract the goalkeepers counter by 1
         * 
         */
        void subtractGoalKeepersCtr();


        /**
         * @brief add 1 to the Total Cards for the team
         * 
         */
        void bumpGamesCounter();

        void setSortingType(SortByInfo new_info);

        void deactivateTeam();
        

        //-------------helper functions-----------


        /**
         * @brief check if the team can participate in the games
         * 
         * @return true if there is a goal keeper
         * @return false if there isnt a goal keeper
         */
        bool canParticipate();
};

#endif