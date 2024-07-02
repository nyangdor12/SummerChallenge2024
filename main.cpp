#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 //the most pressing moves has the higest value assigned to it so it will get picked first.
 //the most pressing moves are up, so least number of players get tripped
 enum Move { UP=3, LEFT=2, DOWN=1, RIGHT=0 };

 class Player {

private:
    int racetrack;
    int player_pos;


private:

    // determine if the move the player wants to make will cause the player trip
    bool TooCloseToObs(const int& obst_pos, const int& player_pos, int comm)
    {
        return obst_pos - (player_pos + comm) <= 0;
    };

public:
    Move GetRacePlayerMove(const string& racetrack, const int& player_pos)
    {
        
        Move result;
        int obstacle_pos;

        //start from where the player is in the current iteration
        for (int i = player_pos; i < racetrack.length(); ++i)
        {
            //find first the obstacle
            if (racetrack[i] == '#')
            {
                obstacle_pos = i;
                break;
            }
            
        }

        //get how far the player is from the obstacle
        int cond = obstacle_pos - player_pos;

        //while move is not picked, keep going
        while (true)
        {
            //if distance from obstacle is greater than 3
            if (cond >= 3)
            {
                //predict whether the player would trip over if player moved 3 spaces
                if (!TooCloseToObs(obstacle_pos, player_pos, 3)) 
                {
                    //if not, move 3 spaces, and end loop
                    result = Move::RIGHT;
                    break;
                }
                else {
                    //if so, try moving 2 spaces instead, and so on
                    cond = 2;
                    continue;
                }
            }
            else if (cond == 2)
            {
                if (!TooCloseToObs(obstacle_pos, player_pos, 2)) 
                {
                    result = Move::DOWN;
                    break;
                }
                else {
                    cond = 1;
                    continue;
                }
            }
            else if (cond == 1)
            {
                if (!TooCloseToObs(obstacle_pos, player_pos, 1)) 
                {
                    result = Move::LEFT;
                    break;
                }
                else {
                    result = Move::UP;
                    break;
                }
            }
            else
            {
                result = Move::RIGHT;
                break;
            }
        }
        
        return result;
    }

    Move GetArchPlayerMove(const char& firstDigit, const int& playerX, const int& playerY)
    {
        int windPower = firstDigit -'0';
        Move result;

        map<Move,float> distances;
        distances.emplace(Move::RIGHT, sqrt(pow(playerX+windPower,2)+pow(playerY,2)));
        distances.emplace(Move::LEFT, sqrt(pow(playerX-windPower,2)+pow(playerY,2)));
        distances.emplace(Move::UP, sqrt(pow(playerX,2)+pow(playerY-windPower,2)));
        distances.emplace(Move::DOWN, sqrt(pow(playerX,2)+pow(playerY+windPower,2)));

        for (auto it = distances.begin(); it != distances.end(); it++)
        {
            cerr << it->first << ": " << it->second << endl;
        }


        auto mostFrequent = std::min_element(
            distances.begin(), distances.end(),
            [] (const std::pair<Move, float>& p1, const std::pair<Move, float>& p2)->bool{ 
                    return p1.second < p2.second;
            } 
        );

        result = mostFrequent->first;

        return result;
    }
 };


int main()
{
    int player_idx;
    cin >> player_idx; cin.ignore();
    int nb_games;
    cin >> nb_games; cin.ignore();

    vector<Player> games;
    for (int i = nb_games; i < nb_games; i++)
    {
        games.push_back(Player());
    }

    // game loop
    while (1) {
        for (int i = 0; i < 3; i++) {
            string score_info;
            getline(cin, score_info);
        }

        string current_game;

        vector<int> playerStuns;
        vector<Move> allMoves;

        for (int i = 0; i < nb_games; i++) {
            string gpu;
            int reg_0;
            int reg_1;
            int reg_2;
            int reg_3;
            int reg_4;
            int reg_5;
            int reg_6;
            cin >> gpu >> reg_0 >> reg_1 >> reg_2 >> reg_3 >> reg_4 >> reg_5 >> reg_6; cin.ignore();
            current_game = gpu;

            vector<int> info{reg_0, reg_1, reg_2, reg_3, reg_4, reg_5, reg_6};

            if (i == 0){
                
                int player_pos = info[player_idx];
                int player_stun = info[player_idx + 3];

                allMoves.push_back(games[i].GetRacePlayerMove(current_game, player_pos));
                playerStuns.push_back(player_stun);
            }
 
            if (i == 1)
            {
                //cerr << current_game << endl;
                int playerX = info[player_idx];
                int playerY = info[player_idx + 1];
                allMoves.push_back((games[i].GetArchPlayerMove(current_game[0], playerX, playerY)));
                playerStuns.push_back(0);
            }



        }

        // map the output strings to the results of getting the best player move
        map<Move, string> moveString = { {Move::UP,"UP"}, {Move::LEFT, "LEFT"}, {Move::DOWN, "DOWN"}, {Move::RIGHT, "RIGHT"}};

        //chooses move if the player is not stunned
        vector<Move> capableMoves;
        for (int i = 0; i < nb_games; i++)
        {
            if (playerStuns[i] == 0)
            {
                capableMoves.push_back(allMoves[i]);
            }
        }

        // pick the element with highest value (which i previously set to most pressing move)
        auto highestPriorityMove = std::max_element(capableMoves.begin(), capableMoves.end());

        cout << moveString[*highestPriorityMove] << endl;

        
 
    }
}


