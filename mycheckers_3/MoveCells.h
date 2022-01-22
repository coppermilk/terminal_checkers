#pragma once
#include "Cell.h"
class MoveCells
{
public:
	MoveCells() = default;
	MoveCells(int start_x, int start_y, int enemy_x, int enemy_y, int finish_x, int finish_y);
	struct Move_cells {
		Cell start;
		Cell enemy;
		Cell finish;
	};
	 Move_cells move_cells;
};

