#pragma once

#include "BoardNode.h"
#include "IGame.h"

class Minimax 
{
public:
	Minimax(BoardPtr board, int16_t depth, IPlayerPtr firstPlayer, IPlayerPtr secondPlayer);
	~Minimax() = default;

	std::pair<BridgeVector, Position> GetHint(int16_t depth, IPlayerPtr player);

private:
	void GenerateTree(BoardPtr board, int16_t depth, std::shared_ptr<BoardNode> currentHead, IPlayerPtr firstPlayer, IPlayerPtr secondPlayer);
	bool GameOver() const;
	int16_t Evaluate() const;
	std::shared_ptr<BoardNode> GetBoardNodeHint(int16_t depth, IPlayerPtr player);
	int16_t minimax(std::shared_ptr<BoardNode> boardNode, int16_t depth, IPlayerPtr maximizingPlayer,
		int16_t alpha = std::numeric_limits<int16_t>::lowest(),
		int16_t beta = std::numeric_limits<int16_t>::infinity());

private:
	std::shared_ptr<BoardNode> m_treeHead;
	IPlayerPtr m_firstPlayer;
	IPlayerPtr m_secondPlayer;
	int16_t m_initialDepth;
};