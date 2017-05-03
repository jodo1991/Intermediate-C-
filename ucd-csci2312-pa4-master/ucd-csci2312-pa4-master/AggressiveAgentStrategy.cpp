//
// Created by Joseph on 4/4/2016.
//
#include "Game.h"
#include "AggressiveAgentStrategy.h"

namespace Gaming{

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY*.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
		__agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {
        //TODO
    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
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
				empties.push_back(count);
			else if (s.array[count] == SIMPLE)
				simples.push_back(count);
			else if (s.array[count] == STRATEGIC)
				strategics.push_back(count);
		}

		if (simples.size() > 0 && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
			return Game::reachSurroundings(piecePos, Game::randomPosition(simples));
		else if(advantages.size() > 0)
			return Game::reachSurroundings(piecePos, Game::randomPosition(advantages));
		else if (foods.size() > 0)
			return Game::reachSurroundings(piecePos, Game::randomPosition(foods));
		else
			return STAY;
    }
}

