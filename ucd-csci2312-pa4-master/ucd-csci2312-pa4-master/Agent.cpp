//
// Created by Joseph on 4/4/2016.
//

#include "Agent.h"
#include "Resource.h"

namespace Gaming{

    const double Agent::AGENT_FATIGUE_RATE = .3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p) {
        __energy = energy;
    }

    Agent::~Agent() {
    }

    void Agent::age() {
		__energy -= Agent::AGENT_FATIGUE_RATE;
		if(!this->isViable())
			this->finish();
    }

    Piece &Agent::operator*(Piece &other) {
		return other.interact(this);
    }

    Piece &Agent::interact(Agent *agent) {
		if (__energy == agent->__energy) {
			finish();
			agent->finish();
		}
		else if (__energy > agent->__energy) {
			__energy -= agent->__energy;
			agent->finish();
		}
		else {
			agent->__energy -= __energy;
			finish();
		}
		return *this;
    }

    Piece &Agent::interact(Resource *resource) {
		if (resource->getType() == FOOD)
			__energy += resource->consume();
		if (resource->getType() == ADVANTAGE)
			__energy *= resource->consume();
		return *this;
    }
}

