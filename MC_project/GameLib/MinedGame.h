#pragma once

#include <memory>
#include <random>

#include "MinedColumn.h"
#include "Board.h"

class MinedGame
{
public:
	MinedGame(BoardPtr board);

	void DestroyArea(const Position& position, PlayerPtr firstPlayer, PlayerPtr secondPlayer);
	void AddMines();

private:
	void PlaceMine(const Position& position);
	BoardPtr m_board;
};