#pragma once
#include <memory>

#include "Board.h"
#include "IPlayer.h"

class BoardNode : public Board
{
public:
	BoardNode(const BoardPtr board, IPlayerPtr maximizingPlayer, IPlayerPtr minimizingPlayer);
	BoardNode(const BoardNode& other);
	~BoardNode() = default;

	std::vector<std::shared_ptr<BoardNode>> GetChildren();

	void InsertChildren(std::shared_ptr<BoardNode> children);
	bool GameOver() const;
	int16_t Evaluate() const;

	BoardNode& operator=(const BoardNode& rhs);

private:
	std::vector<std::shared_ptr<BoardNode>> m_children;
	IPlayerPtr m_maximizingPlayer;
	IPlayerPtr m_minimizingPlayer;
};