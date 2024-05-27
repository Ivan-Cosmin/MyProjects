#include "Node.h"

Node::Node()
	:value{ -1 }
	, isSelected{ false }
{}
Node::Node(QPoint c, int v)
	:coordinates{ c }
	, value{ v }
	, isSelected{ false }
{}
Node::Node(Node* n)
	:coordinates{ n->getCoord() }
	, value{ n->GetValue() + 1 }
	, isSelected{ n->isSelected }
{}
Node::~Node()
{}

void Node::setCoord(QPoint p)
{
	coordinates = p;
}
void Node::setValue(int val)
{
	value = val;
}
void Node::setNode(Node* val)
{
	setCoord(val->getCoord());
	setValue(val->GetValue());
}

void Node::SetIsSelected(bool is)
{
	isSelected = is;
}


QPoint Node::getCoord()
{
	return coordinates;
}
int Node::GetX()
{
	return coordinates.x();
}
int Node::GetY()
{
	return coordinates.y();
}
int Node::GetValue()
{
	return value;
}

bool Node::getIsSelected()
{
	return isSelected;
}

