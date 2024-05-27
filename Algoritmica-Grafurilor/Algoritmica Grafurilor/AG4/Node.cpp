#include "Node.h"

//Constructors && Destructors
Node::Node() : m_isSelected{false}, m_label{NULL} {}
Node::Node(const int label, const QPoint& coordinates, QColor color, const bool& isSelected) 
:m_label{ label }, m_color{ color }, m_coordinates{ coordinates }, m_isSelected{ isSelected } {}

//Getters
const int Node::getLabel() const noexcept
{
	return m_label;
}
const int Node::getX() const noexcept
{
	return m_coordinates.x();
}
const int Node::getY() const noexcept
{
	return m_coordinates.y();
}
const QPoint Node::getCoordinates() const noexcept
{
	return m_coordinates;
}
const QColor Node::getColor() const noexcept
{
	return m_color;
}

//Setters
void Node::setLabel(const int& label)
{
	m_label = label;
}
void Node::setColor(const QColor& color)
{
	m_color = color;
}
void Node::setCoordinates(const QPoint& coordinates)
{
	m_coordinates = coordinates;
}

//Conditions
bool Node::isSelected() const noexcept
{
	return m_isSelected;
}
void Node::select()
{
	m_isSelected = true;
}
void Node::deselect()
{
	m_isSelected = false;
}