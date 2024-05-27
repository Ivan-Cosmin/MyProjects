#include "Edge.h"

Edge::Edge()
	:firstNode{ nullptr },
	secondNode{ nullptr }
{
}
Edge::~Edge()
{
}
Edge::Edge(Node* n1, Node* n2)
	:firstNode{ n1 }
	, secondNode{n2}
{
}
Edge::Edge(Edge* otherEdge)
{
	firstNode = new Node(otherEdge->firstNode);
	secondNode = new Node(otherEdge->secondNode);
}

Node* Edge::getFirstNode()
{
	return firstNode;
}
Node* Edge::getSecondNode()
{
	return secondNode;
}

