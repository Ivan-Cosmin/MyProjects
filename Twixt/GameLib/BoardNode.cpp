#include "BoardNode.h"

BoardNode::BoardNode(const BoardPtr board, IPlayerPtr maximizingPlayer, IPlayerPtr minimizingPlayer)
	: Board(*board.get())
    , m_maximizingPlayer{maximizingPlayer}
    , m_minimizingPlayer{minimizingPlayer}
{
	// Empty
}

BoardNode::BoardNode(const BoardNode& other)
	:Board(other)
    , m_maximizingPlayer{ other.m_maximizingPlayer }
    , m_minimizingPlayer{ other.m_minimizingPlayer }
{
    for (const auto& child : other.m_children)
    {
        m_children.push_back(std::make_shared<BoardNode>(*child));
    }
}

std::vector<std::shared_ptr<BoardNode>> BoardNode::GetChildren()
{
    return m_children;
}

void BoardNode::InsertChildren(std::shared_ptr<BoardNode> children)
{
    m_children.push_back(children);
}

bool BoardNode::GameOver() const
{
    if (CheckWinner(0) || CheckWinner(1))
    {
        return true;
    }
    return false;
}

int16_t BoardNode::Evaluate() const
{
    return 0;
}

BoardNode& BoardNode::operator=(const BoardNode& rhs)
{
    if (this != &rhs) // Check for self-assignment
    {
        static_cast<Board&>(*this) = rhs;

        m_children.clear();

        for (const auto& child : rhs.m_children)
        {
            m_children.push_back(std::make_shared<BoardNode>(*child));
        }
    }

    return *this;
}
