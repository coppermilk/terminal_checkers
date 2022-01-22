#pragma once
#include "Cell.h"
#include "MoveCells.h"
class Board
{
public:
	Board();
	void resetCall();
	void showCells();
	void moveCells(MoveCells& move_cells);
	bool getWinner();
	Cell::State getCellState(size_t x, size_t y);
	Cell::Type getCellType(size_t x, size_t y);
	const enum { BOARD_SIZE = 8, FIGURE_ROWS = 3 };

	

private:
	Cell cells[BOARD_SIZE][BOARD_SIZE];

	

};

