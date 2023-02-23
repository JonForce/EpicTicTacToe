#include "Move.h"

Move::Move(Move* previous, int location) {
	this->previous = previous;
	this->location = location;
}