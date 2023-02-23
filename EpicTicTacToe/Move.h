#pragma once
#include "Board.h"

class Move {

	public: 
		Move(Move* previous, int location);

		Move* previous;
		int location;
};