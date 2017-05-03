//
// Created by Joseph on 4/4/2016.
//

#include "DefaultAgentStrategy.h"
#include "Game.h"
namespace Gaming{

    DefaultAgentStrategy::DefaultAgentStrategy() {}

    DefaultAgentStrategy::~DefaultAgentStrategy() {}

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
		std::vector<int> advantages;
		std::vector<int> foods;
		std::vector<int> empties;
		std::vector<int> simples;
		std::vector<int> strategics;
		Position piecePos(1, 1);

		for (unsigned int count = 0; count < s.array.size(); ++count) {
			if (s.array[count] == ADVANTAGE)
				advantages.push_back(count);
			else if (s.array[count] == FOOD)
				foods.push_back(count);
			else if (s.array[count] == EMPTY)
				foods.push_back(count);
			else if (s.array[count] == SIMPLE)
				simples.push_back(count);
			else if (s.array[count] == STRATEGIC)
				strategics.push_back(count);
		}

		if (advantages.size() > 0)
			return Game::reachSurroundings(piecePos, Game::randomPosition(advantages));
		else if (foods.size() > 0)
			return Game::reachSurroundings(piecePos, Game::randomPosition(foods));
		else if (empties.size() > 0)
			return Game::reachSurroundings(piecePos, Game::randomPosition(empties));
		if (simples.size() > 0)
			return Game::reachSurroundings(piecePos, Game::randomPosition(simples));
		else
			return STAY;
	}
}

