//
// Created by Joseph on 4/4/2016.
//

#include <iomanip>
#include "Advantage.h"

namespace Gaming {

    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
    const char Advantage::ADVANTAGE_ID = 'D';

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity*ADVANTAGE_MULT_FACTOR) {

    }

    Advantage::~Advantage() {
    }

    void Advantage::print(std::ostream &os) const {
		os << this->ADVANTAGE_ID << std::left << std::setw(4) << this->__id;
		os << std::setw(0);
    }

    double Advantage::getCapacity() const {
        return __capacity;
    }

    double Advantage::consume() {
		finish();
		return __capacity*ADVANTAGE_MULT_FACTOR;
    }
}
