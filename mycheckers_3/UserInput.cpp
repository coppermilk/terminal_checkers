#include "UserInput.h"
#include "MoveCells.h"
#include <stdio.h>
#include <iostream>
#include <vector>

// For #include <cstring>.
#pragma warning(disable : 4996)

Cell UserInput::getMove(Board& board, Cell& player, MoveCells& move_cells, Cell& last_move)
{
	bool is_move_get = false;
	bool is_end_null = true;
	while (!is_move_get) {
		if (Cell::State::WHITE == player.getState()) {
			std::cout << "Pleyer W >";
		}
		else if (Cell::State::BLACK == player.getState()) {
			std::cout << "Pleyer B >";
		}

		// a1 b2
		bool is_num_ok = false;
		bool is_char_ok = false;
		bool is_cord_ok = false;
		bool is_takes_own_figure_ok = false;
		bool is_assignment_field_empty_ok = false;

		//________________________________________________________
		__int32 _x1, _y1, _x2, _y2;
		if (scanf("%u %u %u %u", &_x1, &_y1, &_x2, &_y2) != 4) {
			std::cout << "Bad input. Use format like \'a1 b2\'. " << std::endl;
		}
		else {
			if (!((_x1 >= 0 && _x1 < board.BOARD_SIZE) &&
				(_x2 >= 0 && _x2 < board.BOARD_SIZE))) {
				std::cout << "Bad input. Letters must be in range from a to " << (char)(board.BOARD_SIZE + 'a' - 1) << "." << std::endl;
			}
			else {
				is_char_ok = true;
			}

			if (!((_y1 >= 0) && (_y1 <= (board.BOARD_SIZE)) &&
				(_y2 >= 0) && (_y2 <= (board.BOARD_SIZE)))) {
				std::cout << "Bad input. Numbers must be in range from 1 to " << board.BOARD_SIZE << "." << std::endl;
			}
			else {
				is_num_ok = true;
			}

			if (!((((_x1 % 2 != 0) && (_y1 % 2 == 0)) || ((_x1 % 2 == 0) && (_y1 % 2 != 0))) &&
				(((_x2 % 2 != 0) && (_y2 % 2 == 0)) || ((_x2 % 2 == 0) && (_y2 % 2 != 0))))) {
				std::cout << "Bad input. Check coordinates" << std::endl;
			}
			else {
				is_cord_ok = true;
			}

			if (((player.getState() == Cell::State::WHITE) && (board.getCellState(_x1, _y1) == Cell::State::WHITE))) {
				is_takes_own_figure_ok = true;
			}
			else if (((player.getState() == Cell::State::BLACK) && (board.getCellState(_x1, _y1) == Cell::State::BLACK))) {
				is_takes_own_figure_ok = true;
			}
			else {
				std::cout << "Bad input. Check figure" << std::endl;
				is_takes_own_figure_ok = false;
			}

			if (!(board.getCellState(_x2, _y2) == Cell::State::BLANK)) {
				std::cout << "Bad input. Òhe destination field must be empty." << std::endl;
			}
			else {
				is_assignment_field_empty_ok = true;
			}

			if (is_char_ok && is_num_ok && is_cord_ok && is_takes_own_figure_ok && is_assignment_field_empty_ok) {
				move_cells.move_cells.start.possition.x = _x1;
				move_cells.move_cells.start.possition.y = _y1;
				move_cells.move_cells.start.state = board.getCellState(_x1, _y1);
				move_cells.move_cells.start.type = board.getCellType(_x1, _y1);

				move_cells.move_cells.finish.possition.x = _x2;
				move_cells.move_cells.finish.possition.y = _y2;
				move_cells.move_cells.finish.state = board.getCellState(_x2, _y2);
				move_cells.move_cells.finish.type = board.getCellType(_x2, _y2);

				if (chekInput(board, move_cells)) {
					std::cout << "ok" << std::endl;
					std::vector<MoveCells> îbligatory_moves = countObligatoryMoves(board, player);
					std::vector<MoveCells> single_obligaroty_moves;
					int obligatory = îbligatory_moves.size();
					if ((last_move.possition.x == move_cells.move_cells.start.possition.x != 0) &&
						(last_move.possition.y == move_cells.move_cells.start.possition.y != 0))
					{
						single_obligaroty_moves = countObligatoryMovesCommon(last_move.possition.x, last_move.possition.y,
							board, player, single_obligaroty_moves);
						obligatory = single_obligaroty_moves.size();
						if (obligatory)
						{
							for (int i = 0; i < obligatory; i++)
							{
								if ((single_obligaroty_moves[i].move_cells.start.possition.x == move_cells.move_cells.start.possition.x) &&
									(single_obligaroty_moves[i].move_cells.start.possition.y == move_cells.move_cells.start.possition.y) &&
									(single_obligaroty_moves[i].move_cells.finish.possition.y == move_cells.move_cells.finish.possition.y) &&
									(single_obligaroty_moves[i].move_cells.finish.possition.x == move_cells.move_cells.finish.possition.x))
								{
									is_move_get = true;
								}
							}
						}
						else if (obligatory == 0)
						{
							is_move_get = true;
							is_end_null = true;
						}
						else {
							std::cout << "Bad input. Invalid move." << std::endl;
						}
					}
					if (obligatory)
					{
						for (int i = 0; i < obligatory; i++)
						{
							if ((îbligatory_moves[i].move_cells.start.possition.x == move_cells.move_cells.start.possition.x) &&
								(îbligatory_moves[i].move_cells.start.possition.y == move_cells.move_cells.start.possition.y) &&
								(îbligatory_moves[i].move_cells.finish.possition.y == move_cells.move_cells.finish.possition.y) &&
								(îbligatory_moves[i].move_cells.finish.possition.x == move_cells.move_cells.finish.possition.x))
							{
								is_move_get = true;
							}
						}
					}
					else if (obligatory == 0)
					{
						is_move_get = true;
						is_end_null = true;
					}
					else {
						std::cout << "Bad input. Invalid move." << std::endl;
					}
				}
				else
				{
					std::cout << "Bad input. Invalid move." << std::endl;
				}
			}
		}
		// error debag
		char ch;
		ch = getchar();
	}
	if (is_end_null) {
		last_move.possition.x = 0;
		last_move.possition.y = 0;
	}
	else {
		last_move.possition.x = move_cells.move_cells.finish.possition.x;
		last_move.possition.y = move_cells.move_cells.finish.possition.y;
	}

	return last_move;
}

std::vector<MoveCells> UserInput::countObligatoryMoves(Board& board, Cell& player)
{
	//int count = 0;
	std::vector<MoveCells> obligatory_moves;
	for (size_t i = 0; i < board.BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < board.BOARD_SIZE; j++)
		{
			if (board.getCellState(i, j) == player.getState()) {
				if (board.getCellType(i, j) == Cell::Type::COMMON) {
					obligatory_moves = countObligatoryMovesCommon(i, j, board, player, obligatory_moves);
				}

				else if (board.getCellType(i, j) == Cell::Type::KING)
				{
					obligatory_moves = countObligatoryMovesKing(i, j, board, player, obligatory_moves);
				}
			}
		}
	}
	return obligatory_moves;
}

std::vector<MoveCells> UserInput::countObligatoryMovesCommon(int i, int j, Board& board, Cell& player, std::vector<MoveCells> obligatory_moves)
{
	for (int q = 1; q <= 4; q++) {
		int required_enemy_cell_x = shift_X_To_1_InQuadrant(i, q, 1);
		int required_enemy_cell_y = shift_Y_To_1_InQuadrant(j, q, 1);

		int required_empty_cell_x = shift_X_To_1_InQuadrant(required_enemy_cell_x, q, 1);
		int required_empty_cell_y = shift_Y_To_1_InQuadrant(required_enemy_cell_y, q, 1);

		if ((required_empty_cell_x >= 0 && required_empty_cell_x < board.BOARD_SIZE) &&
			(required_empty_cell_y >= 0 && required_empty_cell_y < board.BOARD_SIZE))
		{
			if (board.getCellState(required_empty_cell_x, required_empty_cell_y) == Cell::State::BLANK)
			{
				if ((board.getCellState(required_enemy_cell_x, required_enemy_cell_y) != player.getState()) &&
					(board.getCellState(required_enemy_cell_x, required_enemy_cell_y) != Cell::State::BLANK) &&
					(board.getCellState(required_enemy_cell_x, required_enemy_cell_y) != Cell::State::HIGHLIGHT))
				{
					std::cout << (player.getState() == Cell::State::BLACK ? "Black " : " White")
						<< "(" << i << "; " << j << ") -> ("
						<< required_enemy_cell_x << "; " << required_enemy_cell_y << ") -> ("
						<< required_empty_cell_x << "; " << required_empty_cell_y << ")" << std::endl;
					obligatory_moves.push_back(MoveCells(i, j, required_enemy_cell_x, required_enemy_cell_y,
						required_empty_cell_x, required_empty_cell_y));
					//count++;
				}
			}
		}
	}
	return obligatory_moves;
}

std::vector<MoveCells> UserInput::countObligatoryMovesKing(int i, int j, Board& board, Cell& player, std::vector<MoveCells> obligatory_moves)
{
	int tmp_shift_x_enemy = 0;
	int tmp_shift_y_enemy = 0;

	int tmp_shift_x_space = 0;
	int tmp_shift_y_space = 0;

	int count_enemy = 0;
	int count_friend = 0;

	for (int quadrant = 1; quadrant <= 4; quadrant++) {
		for (int q = 1; q <= board.BOARD_SIZE; q++) {
			tmp_shift_x_enemy = shift_X_To_1_InQuadrant(i, quadrant, q);
			tmp_shift_y_enemy = shift_Y_To_1_InQuadrant(j, quadrant, q);

			int tmp_shift_x_space = shift_X_To_1_InQuadrant(i, quadrant, q + 1);
			int tmp_shift_y_space = shift_Y_To_1_InQuadrant(j, quadrant, q + 1);

			if (!((tmp_shift_x_space >= 0 && tmp_shift_x_space < board.BOARD_SIZE) &&
				(tmp_shift_y_space >= 0 && tmp_shift_y_space < board.BOARD_SIZE))) {
				continue;
			}

			if (player.state == Cell::State::BLACK) {
				if ((board.getCellState(tmp_shift_x_enemy,
					tmp_shift_y_enemy) == Cell::State::WHITE) &&
					(board.getCellState(tmp_shift_x_space, tmp_shift_y_space) == Cell::State::BLANK)) {
					count_enemy++;
					std::cout << "enemy " << count_enemy << std::endl;
					std::cout << "x " << tmp_shift_x_enemy << "y " << tmp_shift_y_enemy << std::endl;

					std::cout << (player.getState() == Cell::State::BLACK ? "Black " : " White")
						<< "(" << i << "; " << j << ") -> ("
						<< tmp_shift_x_enemy << "; " << tmp_shift_y_enemy << ") -> ("
						<< tmp_shift_x_space << "; " << tmp_shift_y_space << ")" << std::endl;
					obligatory_moves.push_back(MoveCells(i, j, tmp_shift_x_enemy, tmp_shift_y_enemy,
						tmp_shift_x_space, tmp_shift_y_space));
				}
				else if (board.getCellState(tmp_shift_x_enemy,
					tmp_shift_y_enemy) == Cell::State::BLACK) {
					count_friend++;
					std::cout << "frient " << count_friend << std::endl;
					std::cout << "x " << tmp_shift_x_enemy << "y " << tmp_shift_y_enemy << std::endl;

					continue;
				}
			}
			else if (player.state == Cell::State::WHITE) {
				if ((board.getCellState(tmp_shift_x_enemy,
					tmp_shift_y_enemy) == Cell::State::BLACK) &&
					(board.getCellState(tmp_shift_x_space, tmp_shift_y_space) == Cell::State::BLANK)) {
					count_enemy++;
					std::cout << "enemy " << count_enemy << std::endl;
					std::cout << "x " << tmp_shift_x_enemy << "y " << tmp_shift_y_enemy << std::endl;

					std::cout << (player.getState() == Cell::State::BLACK ? "Black " : " White")
						<< "(" << i << "; " << j << ") -> ("
						<< tmp_shift_x_enemy << "; " << tmp_shift_y_enemy << ") -> ("
						<< tmp_shift_x_space << "; " << tmp_shift_y_space << ")" << std::endl;
					obligatory_moves.push_back(MoveCells(i, j, tmp_shift_x_enemy, tmp_shift_y_enemy,
						tmp_shift_x_space, tmp_shift_y_space));
				}
				else if (board.getCellState(tmp_shift_x_enemy,
					tmp_shift_y_enemy) == Cell::State::WHITE) {
					count_friend++;
					std::cout << "frient " << count_friend << std::endl;
					std::cout << "x " << tmp_shift_x_enemy << "y " << tmp_shift_y_enemy << std::endl;

					continue;
				}
			}
		}
	}
	return obligatory_moves;
}

int UserInput::abs(int number)
{
	return number < 0 ? number * -1 : number;
}

int UserInput::normal(int number)
{
	if (number == 0) {
		return 0;
	}
	else {
		return number / abs(number);
	}
}

int UserInput::getQuadrantOfCoordinateSystem(int delta_x, int delta_y)
{
	delta_x = normal(delta_x);
	delta_y = normal(delta_y);

	// The four quadrants of a Cartesian coordinate system.
	// 2 | 1
	//-- 0 --
	// 3 | 4

	if (delta_x == 1 && delta_y == -1)
	{
		return 1;
	}
	else if (delta_x == -1 && delta_y == -1)
	{
		return 2;
	}
	else if (delta_x == -1 && delta_y == 1)
	{
		return 3;
	}
	else if (delta_x == 1 && delta_y == 1)
	{
		return 4;
	}
	else {
		return 0;
	}
}

int UserInput::shift_X_To_1_InQuadrant(int x, int quadrant, int n = 1)
{
	// The four quadrants of a Cartesian coordinate system.
	//   0 1 2 3
	// 0  - | +
	// 1 -- 0 --
	// 2  - | +
	if (quadrant == 1) {
		return x + (1 * n);
	}
	else if (quadrant == 2) {
		return x - (1 * n);
	}
	else if (quadrant == 3) {
		return x - (1 * n);
	}
	else if (quadrant == 4) {
		return x + (1 * n);
	}
	else {
		std::cout << "Error shift_X_To_1_InQuadrant";
		return 0;
	}
}

int UserInput::shift_Y_To_1_InQuadrant(int y, int quadrant, int n = 1)
{
	// The four quadrants of a Cartesian coordinate system.
	//   0 1 2 3
	// 0  - | -
	// 1 -- 0 --
	// 2  + | +
	if (quadrant == 1) {
		return y - (1 * n);
	}
	else if (quadrant == 2) {
		return y - (1 * n);
	}
	else if (quadrant == 3) {
		return y + (1 * n);
	}
	else if (quadrant == 4) {
		return y + (1 * n);
	}
	else {
		std::cout << "Error shift_Y_To_1_InQuadrant";
		return 0;
	}
}

bool UserInput::isPossibleKingMove(int start_x, int start_y, int finish_x, int finish_y, Board& board, MoveCells& move_cells)
{
	int delta_x = finish_x - start_x;
	int delta_y = finish_y - start_y;
	int tmp_shift_x = 0;
	int tmp_shift_y = 0;

	int quadrant = getQuadrantOfCoordinateSystem(delta_x, delta_y);

	if (abs(delta_x) != abs(delta_y)) {
		return false;
	}

	int abs_delta_x_and_y = abs(delta_x);

	int count_enemy = 0;
	int count_friend = 0;

	for (int i = 1; i <= abs_delta_x_and_y; i++) {
		if (board.getCellState(start_x, start_y) == Cell::State::BLACK) {
			if (board.getCellState(shift_X_To_1_InQuadrant(start_x, quadrant, i),
				shift_Y_To_1_InQuadrant(start_y, quadrant, i)) == Cell::State::WHITE) {
				count_enemy++;
				std::cout << "enemy " << count_enemy << std::endl;

				if (count_enemy <= 1 && count_friend == 0) {
					move_cells.move_cells.enemy.possition.x = shift_X_To_1_InQuadrant(start_x, quadrant, i);
					move_cells.move_cells.enemy.possition.y = shift_Y_To_1_InQuadrant(start_y, quadrant, i);
					return true;
				}
			}

			else if (board.getCellState(shift_X_To_1_InQuadrant(start_x, quadrant, i),
				shift_Y_To_1_InQuadrant(start_y, quadrant, i)) == Cell::State::BLACK) {
				count_friend++;
				std::cout << "frient " << count_friend << std::endl;
			}
		}
		else if (board.getCellState(start_x, start_y) == Cell::State::WHITE) {
			if (board.getCellState(shift_X_To_1_InQuadrant(start_x, quadrant, i),
				shift_Y_To_1_InQuadrant(start_y, quadrant, i)) == Cell::State::BLACK) {
				count_enemy++;
				std::cout << "enemy " << count_enemy << std::endl;
				if (count_enemy <= 1 && count_friend == 0) {
					move_cells.move_cells.enemy.possition.x = shift_X_To_1_InQuadrant(start_x, quadrant, i);
					move_cells.move_cells.enemy.possition.y = shift_Y_To_1_InQuadrant(start_y, quadrant, i);
					return true;
				}
			}
			else if (board.getCellState(shift_X_To_1_InQuadrant(start_x, quadrant, i),
				shift_Y_To_1_InQuadrant(start_y, quadrant, i)) == Cell::State::WHITE) {
				count_friend++;
				std::cout << "frient " << count_friend << std::endl;
			}
		}
	}

	if (count_enemy <= 1 && count_friend == 0) {
		return true;
	}
	else {
		return false;
	}
}