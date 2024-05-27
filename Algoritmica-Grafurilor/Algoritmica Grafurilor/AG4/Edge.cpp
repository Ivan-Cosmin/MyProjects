#include "Edge.h"

//Constructors
Edge::Edge() 
	: m_firstNode{ nullptr }, m_secondNode{ nullptr }, m_cost{ NULL } {}
Edge::Edge(Node* firstNode, Node* secondNode, const uint16_t& cost) 
	: m_firstNode{ firstNode }, m_secondNode{ secondNode }, m_cost{ cost } {}

//Getters
Node* Edge::getFirstNode() const noexcept
{
	return m_firstNode;
}
Node* Edge::getSecondNode() const noexcept
{
	return m_secondNode;
}
uint16_t Edge::getCost() const noexcept
{
	return m_cost;
}

//Setters
void Edge::setEdge(Node* firstNode, Node* secondNode)
{
	m_firstNode = firstNode;
	m_secondNode = secondNode;
}
void Edge::setCost(const uint16_t& cost)
{
	m_cost = cost;
}

