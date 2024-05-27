#include "SecondWindow.h"

SecondWindow::SecondWindow(std::vector<Node*> nodes, std::vector<Edge*> edges, QWidget* parent)
{
	m_nodes = nodes;
	m_edges = edges;
}

SecondWindow::~SecondWindow()
{

}
void drawArrow(QPoint Q1, QPoint Q2, QPainter& p)
{
	qreal arrowSize = Node::DimNODE / 2.0;
	p.setBrush(Qt::black);
	QLineF line(Q2, Q1);

	double angle = std::atan2(-line.dy(), line.dx());
	QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

	QPolygonF arrowHead;
	arrowHead.clear();
	arrowHead << line.p1() << arrowP1 << arrowP2;
	p.drawPolygon(arrowHead);

	p.setBrush(Qt::white);
}

void drawLine(Node* N1, Node* N2, int radius, QPainter& p)
{
	p.setPen(Qt::black);
	qreal dx = N2->GetX() - N1->GetX();
	qreal dy = N2->GetY() - N1->GetY();
	qreal distance = qSqrt(dx * dx + dy * dy);
	qreal x1_intersec = N1->GetX() + (dx * radius / distance);
	qreal y1_intersec = N1->GetY() + (dy * radius / distance);
	qreal x2_intersec = N2->GetX() - (dx * radius / distance);
	qreal y2_intersec = N2->GetY() - (dy * radius / distance);

	p.drawLine(x1_intersec, y1_intersec, x2_intersec, y2_intersec);
	drawArrow(QPoint(x1_intersec, y1_intersec), QPoint(x2_intersec, y2_intersec), p);
}


void paintNode(QPainter& p, Node* n)
{
	if (n->getIsSelected())
		p.setPen(Qt::red);
	else
		p.setPen(Qt::black);


	QRect r(n->GetX() - Node::DimNODE / 2, n->GetY() - Node::DimNODE / 2, Node::DimNODE, Node::DimNODE);
	p.drawEllipse(r);
	QString s;
	s.setNum(n->GetValue());
	p.drawText(r, Qt::AlignCenter, s);
}


void SecondWindow::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	for (Node* n : m_nodes)
		paintNode(p, n);

	for (Edge* ed : m_edges)
		drawLine(ed->getFirstNode(), ed->getSecondNode(), Node::DimNODE / 2, p);
}