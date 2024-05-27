#include "Node.h"
//De facut Destructor si constructor pentru pointeri

Node::Node()
    :value{-1}
    ,isSelected{false}
{}
Node::Node(QPoint c, int v)
    :coordinates{ c }
    , value{ v }
    , isSelected{ false }
{}
Node::Node(Node* n)
    :coordinates{ n->getCoord() }
    ,value{ n->getValue() + 1 }
    , isSelected{ false }
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
    setValue(val->getValue());
}

void Node::setIsSelected(bool is)
{
    isSelected = is;
}


QPoint Node::getCoord()
{
    return coordinates;
}
int Node::getX()
{
    return coordinates.x();
}
int Node::getY()
{
    return coordinates.y();
}
int Node::getValue()
{
    return value;
}

bool Node::getIsSelected()
{
    return isSelected;
}
