#ifndef NODE_H
#define NODE_H

#include <QPainter>

using NodePtr = std::shared_ptr<class Node>;

class Node
{
public:
	Node(int val = -1);
	Node(const QPointF& p, int val = -1);

	void setValue(int val);
	void setPosition(const QPointF& p);

	QPointF getPosition() const;
	int getValue() const;

	bool operator==(const Node& n);
	bool operator>(const Node& n) const;
	bool operator<(const Node& n) const;

	float getEulerDistance(const Node& OtherPoint) const;

private:
	int value;
	QPointF position;
};

#endif // NODE_H
