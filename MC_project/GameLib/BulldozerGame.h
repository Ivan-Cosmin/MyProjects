#pragma once
#include "Board.h"
#include "BulldozerColumn.h"


class BulldozerGame
{
public:
	BulldozerGame(BoardPtr& rhs);
	
	Position DestroyOrMove(PlayerPtr firstPlayer, PlayerPtr secondPlayer);
	
	

private:
	void DestroyRandomColumn(PlayerPtr firstPlayer, PlayerPtr secondPlayer);
	void MoveToRandomEmptyPlace();
	bool CoinFlip();
	void PlaceBulldozer(const Position& position);
	BoardPtr m_board;
	float m_epsilon;
	Position m_currentPosition;
	


};

