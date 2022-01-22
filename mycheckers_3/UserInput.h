#pragma once
#include "Board.h"
#include "MoveCells.h"
#include "Cell.h"
#include <vector>

class UserInput
{
public:
	Cell getMove(Board& board, Cell &player, MoveCells& move_cells, Cell& last_move);
	std::vector<MoveCells> countObligatoryMovesCommon(int x, int y, Board& board, Cell& plaayer, std::vector<MoveCells> obligatory_moves);
	std::vector<MoveCells> countObligatoryMovesKing(int x, int y, Board& board, Cell& plaayer, std::vector<MoveCells> obligatory_moves);
	
private:

	std::vector<MoveCells> countObligatoryMoves(Board& board, Cell& plaayer);
	//std::vector<MoveCells> countObligatoryMovesCommon(int x, int y, Board& board, Cell& plaayer, std::vector<MoveCells> obligatory_moves);
	MoveCells* findÎbligatoryÌoves(int count_obligatory_moves);

	bool isObligatoryMoves(MoveCells & move_cells, int count_obligatory_moves, MoveCells* p_obligatory_moves);
	  
	bool chekInput(Board& board, MoveCells& move_cells)
	{
		bool is_move_single, is_move_double, is_move_king;
		is_move_single = is_move_double = is_move_king = false;

		int delta_x = move_cells.move_cells.finish.possition.x - move_cells.move_cells.start.possition.x;
		int delta_y = move_cells.move_cells.finish.possition.y - move_cells.move_cells.start.possition.y;

		int quadrant = getQuadrantOfCoordinateSystem(delta_x, delta_y);

		if (abs(delta_x) == 1 && abs(delta_y) == 1) {
			if (board.getCellType(move_cells.move_cells.start.possition.x, move_cells.move_cells.start.possition.y) == Cell::Type::COMMON)
			{
				if (board.getCellState(move_cells.move_cells.start.possition.x, move_cells.move_cells.start.possition.y) == Cell::State::WHITE)
				{
					if (quadrant == 3 || quadrant == 4)
					{
						is_move_single = true;

						return is_move_single;

					}
				}
				else if (board.getCellState(move_cells.move_cells.start.possition.x, move_cells.move_cells.start.possition.y) == Cell::State::BLACK)
				{
					if (quadrant == 1 || quadrant == 2)
					{
						is_move_single = true;

						return is_move_single;
					}
				}

			}

		}

		if (abs(delta_x) == 2 && abs(delta_y) == 2) {

			int enemy_cell_x = shift_X_To_1_InQuadrant(move_cells.move_cells.start.possition.x, quadrant, 1);
			int enemy_cell_y = shift_Y_To_1_InQuadrant(move_cells.move_cells.start.possition.y, quadrant, 1);

			if (board.getCellState(move_cells.move_cells.start.possition.x, move_cells.move_cells.start.possition.y) == Cell::State::WHITE)
			{
				if ((board.getCellState(enemy_cell_x, enemy_cell_y) == Cell::State::BLACK)) {
					move_cells.move_cells.enemy.possition.x = enemy_cell_x;
					move_cells.move_cells.enemy.possition.y = enemy_cell_y;
					is_move_double = true;

					return is_move_double;

				}


			}
			else if (board.getCellState(move_cells.move_cells.start.possition.x, move_cells.move_cells.start.possition.y) == Cell::State::BLACK) {
				if ((board.getCellState(enemy_cell_x, enemy_cell_y) == Cell::State::WHITE)) {
					move_cells.move_cells.enemy.possition.x = enemy_cell_x;
					move_cells.move_cells.enemy.possition.y = enemy_cell_y;
					is_move_double = true;

					return is_move_double;
				}
			}

		}

		if (isPossibleKingMove(move_cells.move_cells.start.possition.x, move_cells.move_cells.start.possition.y,
			move_cells.move_cells.finish.possition.x, move_cells.move_cells.finish.possition.y, board, move_cells)) {
			
			
			is_move_king = true;
			// to do enemy cell
			return is_move_king;
		}


		return false;
	}
	
	int abs(int number);
	int normal(int number);
	int getQuadrantOfCoordinateSystem(int delta_x, int delta_y);

	int shift_X_To_1_InQuadrant(int x, int quadrant, int n);
	int shift_Y_To_1_InQuadrant(int y, int quadrant, int n);

	bool isPossibleKingMove(int start_x, int start_y, int finish_x, int finish_y, Board& board, MoveCells& move_cells);

	

	
};

