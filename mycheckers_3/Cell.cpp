#include "Cell.h"

Cell::Cell()
{
	state = State::BLANK;
	type = Type::BLANK;

	possition = { 0, 0 };
}

Cell::Cell(Possition& possition)
{
	setPossition(possition);
}

Cell::Cell(State& state, Type& type, Possition& possition)
{
	setState(state);
	setType(type);
	setPossition(possition);
}


Cell::State Cell::getState()
{
	return state;
}

Cell::Type Cell::getType()
{
	return type;
}

Cell::Possition Cell::getPossition()
{
	return possition;
}

void Cell::setCall(const State& state, const Type& type, const Possition& possition)
{
	setState(state);
	setType(type);
	setPossition(possition);
}

void Cell::setState(const State& state)
{
	this->state = state;
}

void Cell::setType(const Type& type)
{
	this->type = type;
}

void Cell::setPossition(const Possition& possition)
{
	this->possition = possition;
}

Cell Cell::stateInvert()
{
	if (this->getState() == Cell::State::BLACK) {
		this->setState(Cell::State::WHITE);
	}
	else if (this->getState() == Cell::State::WHITE) {
		this->setState(Cell::State::BLACK);
	}
	return *this;
}



bool operator==(const Cell::Possition& p1, const Cell::Possition& p2)
{
	return ((p1.x == p2.x) && (p1.y == p2.y)) ? true : false;
}



