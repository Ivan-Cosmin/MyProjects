#include "SecondWindow.h"

SecondWindow::SecondWindow(std::vector<Node*> nodes, std::vector<Edge*> edges, QWidget* parent)
{
	m_nodes = nodes;
	m_edges = edges;
}

SecondWindow::~SecondWindow()
{
	for (Edge* edge : m_edges)
		if (edge)
			delete edge;
	m_edges.clear();

	for (Node* node : m_nodes)
		if (node)
			delete node;
	m_nodes.clear();
}

void SecondWindow::paintNode(QPainter& painter, Node* node)
{
	if (node->isSelected())
		painter.setPen(QPen(Qt::red));
	else
		painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(node->getColor()));
	QRect rect(node->getX() - Node::m_kDimNode / 2, node->getY() - Node::m_kDimNode / 2, Node::m_kDimNode, Node::m_kDimNode);
	painter.drawEllipse(rect);
	QString text;
	text.setNum(node->getLabel());
	painter.drawText(rect, Qt::AlignCenter, text);

	painter.setBrush(QBrush(Qt::white));
}
void SecondWindow::drawLine(QPainter& painter, Edge* edge)
{
	int radius = Node::m_kDimNode / 2;
	painter.setPen(QPen(Qt::black));

	Node* eFirstNode = edge->getFirstNode(), * eSecondNode = edge->getSecondNode();

	qreal dx = eSecondNode->getX() - eFirstNode->getX();
	qreal dy = eSecondNode->getY() - eFirstNode->getY();
	qreal distance = qSqrt(dx * dx + dy * dy);
	qreal x1_intersec = eFirstNode->getX() + (dx * radius / distance);
	qreal y1_intersec = eFirstNode->getY() + (dy * radius / distance);
	qreal x2_intersec = eSecondNode->getX() - (dx * radius / distance);
	qreal y2_intersec = eSecondNode->getY() - (dy * radius / distance);

	painter.drawLine(x1_intersec, y1_intersec, x2_intersec, y2_intersec);
}
void SecondWindow::drawCost(QPainter& painter, Edge* edge)
{
	Node* firstNode = edge->getFirstNode();
	Node* secondNode = edge->getSecondNode();

	if (firstNode && secondNode)
	{
		QPoint middlePoint(firstNode->getCoordinates() / 2 +
			secondNode->getCoordinates() / 2 -
			QPoint(squareSize.height() / 2 + 1,
				squareSize.width() / 2 + 1));

		QString costString = QString::number(edge->getCost());
		QRect rect(middlePoint, squareSize);
		painter.drawRect(rect);

		painter.drawText(rect, Qt::AlignCenter, costString);
	}

	firstNode = nullptr;
	secondNode = nullptr;

}
void SecondWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	for (Node* node : m_nodes)
		paintNode(painter, node);
	for (Edge* edge : m_edges)
	{
		drawLine(painter, edge);
		drawCost(painter, edge);
	}
	update();
}
