//
// Created by Joseph on 4/4/2016.
//

#include <iomanip>
#include <vector>
#include "Simple.h"

namespace Gaming{

	const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) {
        //TODO
    }

    Simple::~Simple() {
        //todo
    }

    void Simple::print(std::ostream &os) const {
		os << this->SIMPLE_ID << std::left << std::setw(4) << this->__id;
		os << std::setw(0);
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
		std::vector<int> resources;
		std::vector<int> empties;
		Position currentPosition(1, 1);
		for (int count = 0; count < s.array.size(); ++count) {
			if (s.array[count] == FOOD || s.array[count] == ADVANTAGE)
				resources.push_back(count);
			else if (s.array[count] == EMPTY)
				empties.push_back(count);
		}

		if (resources.size() > 0)
			return __game.reachSurroundings(currentPosition, Game::randomPosition(resources));
		else if (empties.size() > 0)
			return __game.reachSurroundings(currentPosition, Game::randomPosition(empties));
		else
			return STAY;

    }
}


