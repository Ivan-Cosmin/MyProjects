#pragma once
#include <QPainter>
#include <string>

class Node
{
public:
	//Constructors && Destructors
	Node();
	Node(const int label, const QPoint& coordinates, QColor color = Qt::white, const bool& isSelected = false);
	
	//Getters
	const int getLabel() const noexcept;
	const int getX() const noexcept;
	const int getY() const noexcept;
	const QColor getColor() const noexcept;
	const QPoint getCoordinates() const noexcept;
	
	//Setters
	void setColor(const QColor& color);
	void setLabel(const int& label);
	void setCoordinates(const QPoint& coordinates);
	
	//Conditions
	bool isSelected() const noexcept;
	void select();
	void deselect();

	static const int m_kDimNode = 40;

private:
	int m_label;
	QPoint m_coordinates;
	QColor m_color;
	bool m_isSelected;
};

