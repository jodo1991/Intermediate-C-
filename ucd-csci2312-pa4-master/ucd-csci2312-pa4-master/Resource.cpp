//
// Created by Joseph on 4/4/2016.
//


#include "Gaming.h"
#include "Game.h"
#include "Piece.h"
#include "Resource.h"
#include "Agent.h"

namespace Gaming{

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p){
        __capacity = capacity;
    }

    Resource::~Resource() {}

    double Resource::consume() {
		finish();
		return __capacity;
    }

    void Resource::age() {
		__capacity /= RESOURCE_SPOIL_FACTOR;
		if (__capacity < .01)
			this->finish();
    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
		return STAY;
    }

    Piece &Resource::interact(Agent *agent) {
		agent->addEnergy(consume());
		return *this;
    }

    Piece &Resource::interact(Resource *resource) {
		return *resource;
    }

    Piece &Resource::operator*(Piece &other) {
		return other.interact(this);
    }
}
