#include "Edge.h"

Edge::Edge()
	:firstNode{nullptr},
	secondNode{nullptr}
{
}
Edge::~Edge()
{
}
Edge::Edge(Node* n1, Node* n2)
{
	firstNode = n1;
	secondNode = n2;
}

Node* Edge::getFirstNode()
{
	return firstNode;
}
Node* Edge::getSecondNode()
{
	return secondNode;
}

