#include "Node.h"

Node::Node(int val)
{
	value = val;
}

Node::Node(const QPointF& n, int val)
{
	position = n;
	value = val;
}

void Node::setValue(int val)
{
	value = val;
}

void Node::setPosition(const QPointF& p)
{
	position = p;
}

QPointF Node::getPosition() const { return position; }
int Node::getValue()const { return value; }

bool Node::operator>(const Node& n) const
{
	return value > n.value;
}

bool Node::operator<(const Node& n) const
{
	return value < n.value;
}


bool Node::operator==(const Node& n)
{
	return n.value == this->value;
}

float Node::getEulerDistance(const Node& OtherPoint) const
{
	return sqrt(pow(position.y() - OtherPoint.position.y(), 2) + pow(position.x() - OtherPoint.position.x(), 2));
}

