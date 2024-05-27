#pragma once
#include "Node.h"

class Edge
{
public:
	Edge();
	~Edge();
	Edge(Node*, Node*);
	Node* getFirstNode();
	Node* getSecondNode();

private:
	Node* firstNode, * secondNode;
};

