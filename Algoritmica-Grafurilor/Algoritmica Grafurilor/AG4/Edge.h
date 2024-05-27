#pragma once
#include "Node.h"

static const QSize squareSize{ 35, 35 };

class Edge
{
public:

	//Constructors && Destructors
	Edge();
	Edge(Node* firstNode, Node* secondNode, const uint16_t& cost);
	~Edge() = default;

	//Getters
	Node* getFirstNode() const noexcept;
	Node* getSecondNode() const noexcept;
	uint16_t getCost() const noexcept;

	//Setters
	void setEdge(Node* firstNode, Node* secondNode);
	void setCost(const uint16_t& cost);


private:
	Node* m_firstNode, * m_secondNode;
	uint16_t m_cost;
};

