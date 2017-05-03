//
// Created by Joseph on 4/4/2016.
//

#include <iomanip>
#include <iostream>
#include "Game.h"
#include "Food.h"
#include "Advantage.h"
#include "Simple.h"
#include "Strategic.h"

namespace Gaming{

	PositionRandomizer Game::__posRandomizer = PositionRandomizer();

	const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
	const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

	Game::Game() {
		__width = 3;
		__height = 3;
		__round = 1;
		__numInitAgents = 0;
		__numInitResources = 0;
		__verbose = false;
		__grid.reserve(9);
		__status = NOT_STARTED;
		for (unsigned int count = 0; count < (__width*__height); ++count) {
			__grid.push_back(nullptr);
		}
	}

	Game::Game(unsigned width, unsigned height, bool manual) {
		if (width < MIN_WIDTH || height < MIN_HEIGHT)
			throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
		__width = width;
		__height = height;
		__round = 1;
		__numInitAgents = 0;
		__numInitResources = 0;
		__status = NOT_STARTED;
		__verbose = false;

		for (unsigned int count = 0; count < (width*height); ++count) {
			Piece* tempP = nullptr;
			__grid.push_back(tempP);
		}
		if(!manual)
			populate();
	}

	Game::~Game() {

	}

    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

		std::default_random_engine gen;
		std::uniform_int_distribution<int> d(0, __width * __height);

		while (numStrategic > 0) {
			int i = d(gen); // random index in the grid vector
			if (i != (__width * __height) && __grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
				numStrategic--;
			}
		}
		while (numSimple > 0) {
			int i = d(gen); // random index in the grid vector
			if (i != (__width * __height) && __grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
				numSimple--;
			}
		}
		while (numAdvantages > 0) {
			int i = d(gen); // random index in the grid vector
			if (i != (__width * __height) && __grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
				numAdvantages--;
			}
		}
		while (numFoods > 0) {
			int i = d(gen); // random index in the grid vector
			if (i != (__width * __height) && __grid[i] == nullptr) { // is position empty
				Position pos(i / __width, i % __width);
				__grid[i] = new Food(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
				numFoods--;
			}
		}
    }

	unsigned int Game::getNumPieces() const {
		return getNumAgents() + getNumResources();
	}

	unsigned int Game::getNumAgents() const {
		unsigned int numAgents = 0;

		for (unsigned count = 0; count < __grid.size(); ++count)
			if (__grid[count] != nullptr && (__grid[count]->getType() == SIMPLE || __grid[count]->getType() == STRATEGIC))
				numAgents++;
		return numAgents;
	}

	unsigned int Game::getNumSimple() const {
		unsigned int numAgents = 0;

		for (unsigned count = 0; count < __grid.size(); ++count)
			if (__grid[count] != nullptr && __grid[count]->getType() == SIMPLE)
				numAgents++;
		return numAgents;
	}

	unsigned int Game::getNumStrategic() const {
		unsigned int numAgents = 0;

		for (unsigned count = 0; count < __grid.size(); ++count)
			if (__grid[count] != nullptr && __grid[count]->getType() == STRATEGIC)
				numAgents++;
		return numAgents;
	}

	unsigned int Game::getNumResources() const {
		unsigned int numAgents = 0;

		for (unsigned count = 0; count < __grid.size(); ++count)
			if (__grid[count] != nullptr && (__grid[count]->getType() == ADVANTAGE || __grid[count]->getType() == FOOD))
				numAgents++;
		return numAgents;
	}

	const Piece *Game::getPiece(unsigned int x, unsigned int y) const {
		if (__grid[x*__width + y] == nullptr)
			throw PositionEmptyEx(x, y);
		else
			return __grid[x*__width + y];
	}

	void Game::addSimple(const Position &position) {
		if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
			throw OutOfBoundsEx(__width, __height, position.y, position.x);
		if (__grid[position.x*__width + position.y] != nullptr)
			throw PositionNonemptyEx(position.x, position.y);
		__grid[position.x*__width + position.y] = (new Simple(*this, *(new Position(position)), STARTING_AGENT_ENERGY));
	}

	void Game::addSimple(const Position &position, double energy) {
		if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
			throw OutOfBoundsEx(__width, __height, position.y, position.x);
		if (__grid[position.x*__width + position.y] != nullptr)
			throw PositionNonemptyEx(position.x, position.y);
		__grid[position.x*__width + position.y] = (new Simple(*this, *(new Position(position)), energy));
	}

	void Game::addSimple(unsigned x, unsigned y) {
		if (x < 0 || x >= __height || y < 0 || y >= __width)
			throw OutOfBoundsEx(__width, __height, y, x);
		if (__grid[x*__width + y] != nullptr)
			throw PositionNonemptyEx(x, y);
		__grid[x*__width + y] = (new Simple(*this, *(new Position(x, y)), STARTING_AGENT_ENERGY));
	}

	void Game::addSimple(unsigned x, unsigned y, double energy) {
		if (x < 0 || x >= __height || y < 0 || y >= __width)
			throw OutOfBoundsEx(__width, __height, y, x);
		if (__grid[x*__width + y] != nullptr)
			throw PositionNonemptyEx(x, y);
		__grid[x*__width + y] = (new Simple(*this, *(new Position(x, y)), energy));
	}

	void Game::addStrategic(const Position &position, Strategy *s) {
		if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
			throw OutOfBoundsEx(__width, __height, position.y, position.x);
		if (__grid[position.x*__width + position.y] != nullptr)
			throw PositionNonemptyEx(position.x, position.y);
		__grid[position.x*__width + position.y] = (new Strategic(*this, *(new Position(position)), STARTING_AGENT_ENERGY, s));
	}

	void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
		if (x < 0 || x >= __height || y < 0 || y >= __width)
			throw OutOfBoundsEx(__width, __height, y, x);
		if (__grid[x*__width + y] != nullptr)
			throw PositionNonemptyEx(x, y);
		__grid[x*__width + y] = (new Strategic(*this, *(new Position(x, y)), STARTING_AGENT_ENERGY, s));
	}

	void Game::addFood(const Position &position) {
		if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
			throw OutOfBoundsEx(__width, __height, position.y, position.x);
		if (__grid[position.x*__width + position.y] != nullptr)
			throw PositionNonemptyEx(position.x, position.y);
		__grid[position.x*__width + position.y] = (new Food(*this, position, STARTING_RESOURCE_CAPACITY));
	}

	void Game::addFood(unsigned x, unsigned y) {
		if (x < 0 || x >= __height || y < 0 || y >= __width)
			throw OutOfBoundsEx(__width, __height, y, x);
		if (__grid[x*__width + y] != nullptr)
			throw PositionNonemptyEx(x, y);
		__grid[x*__width + y] = (new Food(*this, *(new Position(x, y)), STARTING_RESOURCE_CAPACITY));
	}

	void Game::addAdvantage(const Position &position) {
		if (position.x < 0 || position.x >= __height || position.y < 0 || position.y >= __width)
			throw OutOfBoundsEx(__width, __height, position.y, position.x);
		if (__grid[position.x*__width + position.y] != nullptr)
			throw PositionNonemptyEx(position.x, position.y);
		__grid[position.x*__width + position.y] = (new Advantage(*this, position, STARTING_RESOURCE_CAPACITY));
	}

	void Game::addAdvantage(unsigned x, unsigned y) {
		if (x < 0 || x >= __height || y < 0 || y >= __width)
			throw OutOfBoundsEx(__width, __height, y, x);
		if (__grid[x*__width + y] != nullptr)
			throw PositionNonemptyEx(x, y);
		__grid[x*__width + y] = (new Advantage(*this, *(new Position(x, y)), STARTING_RESOURCE_CAPACITY));
	}

    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings tempSurr;
        unsigned int xPos, yPos, count;
        count = 0;
        for(int row = -1; row <= 1; ++row){
            xPos = pos.x + row;
            for(int col = -1; col <= 1; ++col){
                yPos = pos.y + col;
                if(xPos < 0 || xPos >= __height || yPos < 0 || yPos >= __width )
                    tempSurr.array[count++] = INACCESSIBLE;
                else if(__grid[xPos*__width+yPos] == nullptr)
                    tempSurr.array[count++] = EMPTY;
                else
                    tempSurr.array[count++] = getPiece(xPos,yPos)->getType();
            }
        }
		tempSurr.array[4] = SELF;
        return tempSurr;
    }
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        unsigned int xPos, yPos;
        xPos = from.x-to.x;
        yPos = from.y-to.y;

        if(xPos == 1 && yPos == 1)
            return NW;
        else if(xPos == 1 && yPos == 0)
            return N;
        else if(xPos == 1 && yPos == -1)
            return NE;
        else if(xPos == 0 && yPos == -1)
            return E;
        else if(xPos == -1 && yPos == -1)
            return SE;
        else if(xPos == -1 && yPos == 0)
            return S;
        else if(xPos == -1 && yPos == 1)
            return SW;
        else if(xPos == 0 && yPos == 1)
            return W;

        return STAY;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        unsigned int xPos, yPos;
        xPos = pos.x;
        yPos = pos.y;

        if(ac == STAY)
            return true;
        if(ac <= 2)
            xPos--;
        else if(ac >= 5)
            xPos++;

        if(ac <= 6 && ac > 0) {
            if ((ac & 1) == 0)
                yPos--;
            else
                yPos++;
        }

        return !(xPos < 0 || xPos >= __height || yPos < 0 || yPos >= __width);
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {
        Position tempPos(pos);
        if(ac == STAY)
            return tempPos;
        if(ac <= 2)
            tempPos.x--;
        else if(ac >= 5)
            tempPos.x++;

        if(ac <= 6 && ac > 0) {
            if ((ac & 1) == 0)
                tempPos.y--;
            else
                tempPos.y++;
        }
        return tempPos;
    }

	void Game::round() {
		__status = PLAYING;
		for (int count = 0; count < __grid.size(); ++count) {
			if (__grid[count] != nullptr && !(__grid[count]->getTurned())) {
				__grid[count]->setTurned(true);
				ActionType direction = __grid[count]->takeTurn(getSurroundings(__grid[count]->getPosition()));
				if(direction == STAY)
					continue;
				Position newPos = move(__grid[count]->getPosition(), direction);
				int newIndex = newPos.x * __width + newPos.y;
				if (__grid[newIndex] != nullptr) {
					__grid[count]->operator*(*(__grid[newIndex]));
					if (__grid[count]->isViable()) {
						delete __grid[newIndex];
						__grid[newIndex] = __grid[count];
						__grid[count]->setPosition(newPos);
						__grid[count] = nullptr;
					}
					else if (__grid[newIndex]->isViable()) {
						delete __grid[count];
						__grid[count] = nullptr;
					}
					else {
						delete __grid[count];
						delete __grid[newIndex];
						__grid[count] = nullptr;
						__grid[newIndex] = nullptr;
					}
				}
				else {
					__grid[count]->setPosition(newPos);
					__grid[newIndex] = __grid[count];
					__grid[count] = nullptr;
				}
			}
		}

		for (int count = 0; count < __grid.size(); ++count) {
			if (__grid[count] != nullptr) {
				__grid[count]->setTurned(false);
				__grid[count]->age();
				if (!__grid[count]->isViable()) {
					delete __grid[count];
					__grid[count] = nullptr;
				}
			}
		}
		__round++;
	}
    void Game::play(bool verbose) {
		std::cout << std::endl;
		if (verbose) {
			__verbose = true;
			while (getNumResources() > 0 && getNumAgents() > 0) {
				std::cout << *this << std::endl;
				round();
			}
			__status = OVER;
			std::cout << *this << std::endl;
		}
		else {
			while (getNumResources() > 0 && getNumAgents() > 0) {
				round();
			}
			__status = OVER;
		}
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
		unsigned column = 0;

		os << "Round " << game.__round << std::endl;
		for (auto it = game.__grid.begin(); it != game.__grid.end(); ++it) {
			os << '[';
			if (!*it)
				os << "     ";
			else {
				os << **it;
			}
			os << ']';

			column++;
			if (column == game.__width) {
				os << std::endl;
				column = 0;
			}
		}
		os << "Status: ";
		
		switch (game.__status) {
		case(Game::Status::NOT_STARTED) :
			os << "Not Started";
			break;
		case(Game::Status::PLAYING) :
			os << "Playing...";
			break;
		case(Game::Status::OVER) :
			os << "Over!";
			break;
		}
		
		os << std::endl << std::endl;
		return os;
    }
}

