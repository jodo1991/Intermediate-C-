//
// Created by Joseph on 4/4/2016.
//

#include <iomanip>
#include "Gaming.h"
#include "Food.h"

namespace Gaming {

    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {
       __capacity = capacity;
    }

    Gaming::Food::~Food() {}

    void Food::print(std::ostream &os) const {
		os << this->FOOD_ID << std::left << std::setw(4) << this->__id;
		os << std::setw(0);
    }
}
