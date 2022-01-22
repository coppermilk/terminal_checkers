#pragma once
class Cell
{
private:


public:
	enum class State { BLANK, WHITE, BLACK, HIGHLIGHT };
	enum class Type { BLANK, COMMON, KING };

	struct Possition {
		size_t x;
		size_t y;
	};

	Cell();
	Cell(Possition& possition);
	Cell(State& state, Type& type, Possition & possition);
	 
	State getState();
	Type getType();
	Possition getPossition();

	void setCall(const State& state, const Type& type, const Possition& possition);
	void setState(const State &state);
	void setType(const Type &type);
	void setPossition(const Possition &possition);

	Cell stateInvert();

	State state;
	Type type;
	Possition possition;

	friend bool operator ==(const Possition& p1, const Possition& p2);


};

