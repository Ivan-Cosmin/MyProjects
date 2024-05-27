#include "Node.h"

Node::Node()
: m_value{ 0 }
,m_selected{false}
,m_verified{false}
{}
Node::Node(const QPoint& c, const uint8_t& v, const bool& verified, const bool& selected )
    :coordinates{ c }
    , m_value{ v }
    , m_selected{ selected }
    , m_verified{ verified }
{}
Node::Node(Node* n)
    :coordinates{ n->coordinates}
    , m_value{ n->m_value }
    , m_selected{ n->m_selected }
    ,m_verified{n->m_verified}
{}
Node::~Node()
{}

void Node::setCoord(const QPoint& p)
{
    coordinates = p;
}
void Node::setNode(Node* val)
{
    setCoord(val->coordinates);
}
void Node::setValue(const uint8_t& value)
{
    m_value = value;
}
void Node::setSelected(bool selcted)
{
    m_selected = selcted;
}
void Node::setVerified(bool verified)
{
	m_verified = verified;
}

QPoint Node::getCoord() const
{
    return coordinates;
}
int Node::getX() const
{
    return coordinates.x();
}
int Node::getY() const
{
    return coordinates.y();
}
uint8_t Node::getValue() const
{
    return m_value;
}
bool Node::getSelected() const
{
    return m_selected;
}
bool Node::getVerified() const
{
	return m_verified;
}