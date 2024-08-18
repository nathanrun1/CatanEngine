#pragma once

#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include "map.h"
#include "player.h"
#include "bank.h"
#include "buildings.h"
#include "agent.h"
#include "gamestate.h"

class Player;



class Game {
private:
	GameState game_state;

	std::random_device m_rd;
	std::mt19937 m_gen;

public: // temp

	/// <summary>
	/// Initialize up to 4 players
	/// </summary>
	void GetPlayers();

	/// <summary>
	/// Runs a player setup turn, where they place one initial settlement and an adjacent road
	/// </summary>
	/// <param name="player">- Player who currently has action</param>
	void SetupTurn(Player& player);

	/// <summary>
	/// Run the Catan setup phase, where players place initial settlements and roads.
	/// </summary>
	void SetupPhase();

	/// <summary>
	/// Run a given player's turn
	/// </summary>
	/// <param name="player">- Player who currently has action</param>
	void PlayerTurn(Player& player);

	/// <summary>
	/// Declares player as winner and that the game is over.
	/// </summary>
	/// <param name="player">- Player that will be declared as winner</param>
	void Win(Player& player);

	/// <summary>
	/// Attempts to build a settlement for given player at given pos.
	/// Will fail if the given position is an invalid placement.
	/// </summary>
	/// <param name="pos">- Desired settlement position on map</param>
	/// <param name="is_initial">- Whether or not the settlement is one of the player's initial settlements</param>
	/// <returns>True if successful, false otherwise.</returns>
	bool BuildSettlement(Player& player, std::pair<int, int> pos, bool is_initial = false);

	/// <summary>
	/// Attempts to build a road for given player between two given nodes
	/// </summary>
	/// <returns>True if successful, false otherwise</returns>
	bool BuildRoad(Player& player, std::pair<int, int> node_pos1, std::pair<int, int> node_pos2);

	/// <summary>
	/// Attempts to build a city for given player at given pos.
	/// Will fail if the given position is an invalid placement, i.e. player does not have a settlement in that spot.
	/// </summary>
	/// <param name="pos">- Desired city position on map</param>
	/// <returns>True if successful, false otherwise.</returns>
	bool BuildCity(Player& player, std::pair<int, int> pos);

	/// <summary>
	/// Determines and updates current holder of longest road, reassigns VPs as necessary.
	/// Assumes that only one person has the longest road.
	/// </summary>
	void UpdateLongestRoad();

	/// <summary>
	/// Determines and updates current holder of largest army, reassigns VPs as necessary.
	/// Assumes that only one person has the largest army
	/// </summary>
	void UpdateLargestArmy();
public:
	std::vector<Player> players;
	Map map;
	Bank bank;
	Player* longest_road_plr;
	Player* largest_army_plr;

	const int vp_to_win;
	
	static const int MIN_ARMY_SIZE = 3; // Minimum army size for largest army
	static const int MIN_ROAD_SIZE = 5; // MInimum road length for longest road

	/// <summary>
	/// Constructs a Game instance
	/// </summary>
	/// <param name="vp_to_win">- Amount of victory points to win the game. Default is 10.</param>
	Game(int vp_to_win = 10);

	/// <summary>
	/// Rolls a 2d6
	/// </summary>
	/// <returns>Result of a 2d6 roll</returns>
	int DiceRoll();

	/// <summary>
	/// Starts the Catan game. Will continue to run until there is a winner.
	/// </summary>
	void Start();
};

