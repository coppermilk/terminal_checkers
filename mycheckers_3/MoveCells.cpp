#include "MoveCells.h"
#include "Board.h"
#include "Cell.h"

MoveCells::MoveCells(int start_x, int start_y, int enemy_x, int enemy_y, int finish_x, int finish_y)
{
	move_cells.start.possition = { (size_t)start_x, (size_t)start_y };
	move_cells.enemy.possition = { (size_t)enemy_x, (size_t)enemy_y };
	move_cells.finish.possition = { (size_t)finish_x, (size_t)finish_y };
	move_cells.finish.possition = { (size_t)finish_x, (size_t)finish_y };



}
