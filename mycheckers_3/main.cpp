#include <iostream>
#include <vector>
#include "Board.h"
#include "UserInput.h"
#include "Cell.h"
#include "MoveCells.h"

using namespace std;

int main()
{
	Board board;
	UserInput userinput;
	Cell player;

	MoveCells move_cells;
	std::vector<MoveCells> obligatory_moves;

	player.setState(Cell::State::WHITE);

	while (1) {
		Cell last_cell;
		board.showCells();
		last_cell = userinput.getMove(board, player, move_cells, last_cell);
		board.moveCells(move_cells);

		while (!(userinput.countObligatoryMovesCommon(move_cells.move_cells.finish.possition.x,
			move_cells.move_cells.finish.possition.y,
			board, player, obligatory_moves).empty())) {
			board.showCells();
			last_cell = userinput.getMove(board, player, move_cells, last_cell);
			board.moveCells(move_cells);
		}

		player.stateInvert();
		if ((board.getWinner())) {
			break;
		}
	}
	std::cout << "Game Over. Thank you." << std::endl;
	return 0;
}