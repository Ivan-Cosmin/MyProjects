#include "AG3.h"
#include<fstream>

AG3::AG3(QWidget* parent)
	: QMainWindow{ parent }
	, m_firstNode{ nullptr }
	, m_secondNode{ nullptr }
	, isMousePressed{ false }
{
	ui.setupUi(this);
	
}

AG3::~AG3()
{}

void AG3::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{
		if (m_graf.ExistNode(e))
			m_graf.addNode(e->pos());
		else
		{
			for (Node* n : m_graf.GetNodes())
			{
				if (fabs(n->GetX() - e->pos().x()) < Node::DimNODE / 2.0 &&
					fabs(n->GetY() - e->pos().y()) < Node::DimNODE / 2.0)
					if (m_firstNode == nullptr)
					{
						m_firstNode = n;
						m_firstNode->SetIsSelected(true);
					}
					else
					{
						m_secondNode = n;
						if (m_firstNode->GetValue() != m_secondNode->GetValue())
						{
							Edge* ed = new Edge(m_firstNode, m_secondNode);
							if (m_graf.ExistEdge(ed))
								m_graf.AddEdge(ed);
							else
								delete ed;
						}
						m_firstNode->SetIsSelected(false);
						m_firstNode = nullptr;
						m_secondNode = nullptr;
					}
			}
		}
	}
	else
		if (e->button() == Qt::LeftButton)
		{
			for (Node* n : m_graf.GetNodes())
			{
				if (fabs(n->GetX() - e->pos().x()) < Node::DimNODE / 2.0 &&
					fabs(n->GetY() - e->pos().y()) < Node::DimNODE / 2.0)
				{
					n->SetIsSelected(true);
					isMousePressed = true;
					break;
				}
			}
		}
	update();
}
void AG3::mouseMoveEvent(QMouseEvent* e)
{
	if (isMousePressed)
		if (Qt::LeftButton)
		{
			for (Node* n : m_graf.GetNodes())
				if (n->getIsSelected())
				{
					if (m_graf.ExistNode(e))
						n->setCoord(e->pos());
				}
			update();
		}
}
void AG3::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		isMousePressed = false;
		for (Node* n : m_graf.GetNodes())
		{
			n->SetIsSelected(false);
		}
	}
}
void AG3::paintNode(QPainter& p, Node* n)
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
void AG3::TopologicalSort()
{
	if (ui.pushButton->isDown())
	{
		if (!m_graf.hasCycles())
		{
			m_graf.WriteInFile(m_graf.topologicalSort(resultEdgeUsed));
			secondWindow = new SecondWindow(m_graf.GetNodes(), resultEdgeUsed, this);
			secondWindow->resize(900, 400);
			secondWindow->show();
			
		}
		else
			qDebug() << "Has cycles";
	}

}
void AG3::RootButton()
{
	if (ui.pushButton_2->isDown())
	{	
		if(m_graf.isTree())
		{
			m_graf.FindRoot();
			if (m_graf.GetRoot() != nullptr)
			{
				qDebug() << "Root is " << m_graf.GetRoot()->GetValue() << "\n";
			}
			else
			{
				qDebug() << "There is not a root\n";
			}
		}
		else
		{

			qDebug() << "That is not a tree\n";
		}
	}
}

void AG3::drawLine(Node* N1, Node* N2, int radius, QPainter& p)
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
void AG3::drawArrow(QPoint Q1, QPoint Q2, QPainter& p)
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

void AG3::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	for (Node* n : m_graf.GetNodes())
		paintNode(p, n);

	for (Edge* ed : m_graf.getEdges())
		drawLine(ed->getFirstNode(), ed->getSecondNode(), Node::DimNODE / 2, p); 
	
	RootButton();
	TopologicalSort();
}
