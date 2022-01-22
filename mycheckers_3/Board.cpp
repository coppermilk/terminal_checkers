#include <iostream>

#include "Board.h"
#include "Cell.h"

Board::Board()
{
	resetCall();
}

void Board::resetCall()
{
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{ 

			if (((j % 2 != 0) && (i % 2 == 0)) || ((j % 2 == 0) && (i % 2 != 0))) {
				if (i < FIGURE_ROWS) {
					cells[i][j].state = Cell::State::WHITE;
					cells[i][j].type = Cell::Type::COMMON; //     <---- reset

				}
				if (i > BOARD_SIZE - FIGURE_ROWS - 1) {
					cells[i][j].state = Cell::State::BLACK;
					cells[i][j].type = Cell::Type::COMMON;
				}
			}


		}
	}
}

void Board::showCells()
{
	// Detects the operating system and cleans up the terminal.
	//clear();

	// Draw a row of letters from 'a' to N. 
	std::cout << "  ";
	for (size_t j = 0; j < BOARD_SIZE; j++) {
	//	std::cout << (char)(j + 'a') << " ";
		std::cout << j << " ";
	}
	std::cout << std::endl;

	// We look at a row.
	for (size_t i = 0; i < BOARD_SIZE; i++)
	{
		//// Draw a row of numbers from '1' to N. 
		//std::cout << BOARD_SIZE - i << " ";
		std::cout << i << " ";

		// We look at a colls.
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			//  If a figure is empty. 
			if (cells[i][j].state == Cell::State::BLANK) {

				// If a figure can become an empty one, put a dot.
				if ((((j % 2 != 0) && (i % 2 == 0)) || ((j % 2 == 0) && (i % 2 != 0)))) {
					std::cout << ".";
				}
				// Else put a space.
				else {
					std::cout << " ";
				}

			}
			else if (cells[i][j].state == Cell::State::WHITE) {
				if (cells[i][j].type == Cell::Type::KING) {
					std::cout << "W";
				}
				else {
					std::cout << "w"; 
				}
			}
			else if (cells[i][j].state == Cell::State::BLACK) {
				if (cells[i][j].type == Cell::Type::KING) {
					std::cout << "B";
				}
				else {
					std::cout << "b";
				}
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void Board::moveCells(MoveCells& move_cells)
{
	cells[move_cells.move_cells.start.possition.y][move_cells.move_cells.start.possition.x].state = Cell::State::BLANK;
	cells[move_cells.move_cells.start.possition.y][move_cells.move_cells.start.possition.x].type = Cell::Type::BLANK;

	cells[move_cells.move_cells.enemy.possition.y][move_cells.move_cells.enemy.possition.x].state = Cell::State::BLANK;
	cells[move_cells.move_cells.enemy.possition.y][move_cells.move_cells.enemy.possition.x].type = Cell::Type::BLANK;

	cells[move_cells.move_cells.finish.possition.y][move_cells.move_cells.finish.possition.x].state = move_cells.move_cells.start.getState();
	cells[move_cells.move_cells.finish.possition.y][move_cells.move_cells.finish.possition.x].type = move_cells.move_cells.start.getType();
	// to do change
	if (move_cells.move_cells.finish.possition.y == 0 &&
		(cells[move_cells.move_cells.finish.possition.y][move_cells.move_cells.finish.possition.x].state == Cell::State::BLACK)) {
		
		cells[move_cells.move_cells.finish.possition.y][move_cells.move_cells.finish.possition.x].type = Cell::Type::KING;
	}
	else if (((move_cells.move_cells.finish.possition.y + 1) == Board::BOARD_SIZE) &&
		(cells[move_cells.move_cells.finish.possition.y][move_cells.move_cells.finish.possition.x].state == Cell::State::WHITE)) {
		
		cells[move_cells.move_cells.finish.possition.y][move_cells.move_cells.finish.possition.x].type = Cell::Type::KING;
	}
		
		
	
}

bool Board::getWinner()
{
	int count_black = 0;
	int count_white = 0;

	for (size_t i = 0; i < BOARD_SIZE; i++)
	{


		// We look at a colls.
		for (size_t j = 0; j < BOARD_SIZE; j++)
		{
			//  If a figure is empty. 
			if (cells[i][j].state == Cell::State::WHITE) {
				count_white++;
			}
			else if (cells[i][j].state == Cell::State::BLACK) {
				count_black++;
			}

		}
	}
	if (count_black == 0) {
		std::cout << "White is Winner." << std::endl;
		return true;
	}
	else if (count_white == 0) {
		std::cout << "Black is Winner." << std::endl;
		return true;
	}
	else {
		return false;
	}
}



Cell::State Board::getCellState(size_t x, size_t y)
{
	return cells[y][x].getState();
}

Cell::Type Board::getCellType(size_t x, size_t y)
{
	return cells[y][x].getType();
}
