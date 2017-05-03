//
// Created by Joseph on 4/4/2016.
//
#include "Gaming.h"
#include "Game.h"
#include "Piece.h"

namespace Gaming {

	unsigned int Piece::__idGen = 1000;

    Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p) {
		__id = __idGen++;
        __finished = false;
        __turned = false;
    }

    Piece::~Piece() {
        //TODO
    }

    std::ostream& operator<<(std::ostream &os, const Piece &piece) {
		piece.print(os);
		return os;
    }
}

