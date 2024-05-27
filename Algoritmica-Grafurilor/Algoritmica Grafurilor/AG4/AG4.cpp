#include "AG4.h"

//Constructor && Destructor
AG4::AG4(QWidget* parent)
	: QMainWindow(parent), isMousePressed(false), firstNode(nullptr), secondNode(nullptr), isButtonPressed(false)
{
	ui.setupUi(this);
	resize(1000, 800);
	kruskal = new QPushButton(this);
	kruskal->setText("Kruskal");
	kruskal->setFixedSize(100, 30);
	kruskal->move(this->rect().width() - 100, 10);

	prim = new QPushButton(this);
	prim->setText("Prim");
	prim->setFixedSize(100, 30);
	prim->move(this->rect().width() - 100, 40);

	reset = new QPushButton(this);
	reset->setText("RESET");
	reset->setFixedSize(100, 30);
	reset->move(this->rect().width() - 100, 70);

	connect(reset, &QPushButton::clicked, this, &AG4::on_reset_clicked);
	connect(kruskal, &QPushButton::clicked, this, &AG4::on_kruskal_clicked);
	connect(prim, &QPushButton::clicked, this, &AG4::on_prim_clicked);

	connect(&numericDialog, &NumericDialogBox::accepted, this, &AG4::onShowNumericInputDialog);

}

AG4::~AG4()
{
	delete reset;
}

//Mouse
void AG4::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		if (graph.nodeExists(event->pos()) == nullptr)
		{
			graph.addNode(new Node((graph.getNodes().size()), event->pos()));
		}
		else
		{
			for (Node* node : graph.getNodes())
			{
				if (fabs(node->getX() - event->pos().x()) < Node::m_kDimNode / 2.0 &&
					fabs(node->getY() - event->pos().y()) < Node::m_kDimNode / 2.0)
					if (firstNode == nullptr)
					{
						firstNode = node;
						firstNode->select();
					}
					else if (firstNode->isSelected())
					{
						secondNode = node;
						if (firstNode->getLabel() != secondNode->getLabel())
						{
							onShowNumericInputDialog();
						}
						firstNode->deselect();
						firstNode = nullptr;
						secondNode = nullptr;
					}
					else
					{
						firstNode = nullptr;
					}
			}
		}
	}
	else if (event->button() == Qt::LeftButton)
	{
		for (Node* node : graph.getNodes())
		{
			node->deselect();
			if (fabs(node->getX() - event->pos().x()) < Node::m_kDimNode / 2.0 &&
				fabs(node->getY() - event->pos().y()) < Node::m_kDimNode / 2.0)
			{
				node->select();
				isMousePressed = true;
				break;
			}
		}
	}
	update();
}
void AG4::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		isMousePressed = false;
		for (Node* node : graph.getNodes())
		{
			node->deselect();
		}
	}
	update();
}
void AG4::mouseMoveEvent(QMouseEvent* event)
{
	if (isMousePressed)
	{
		for (Node* node : graph.getNodes())
			if (node->isSelected())
			{
				if (graph.otherThanSelectedExists(event->pos()) == nullptr)
					node->setCoordinates(event->pos());
			}
		update();
	}
}

//Paint
void AG4::paintNode(QPainter& painter, Node* node)
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
void AG4::drawLine(QPainter& painter, Edge* edge)
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
void AG4::drawCost(QPainter& painter, Edge* edge) 
{
	Node *firstNode = edge->getFirstNode();
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
void AG4::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	for (Node* node : graph.getNodes())
		paintNode(painter, node);
	for (Edge* edge : graph.getEdges())
	{
		drawLine(painter, edge);
		drawCost(painter, edge);
	}
	update();
}

//Resize
void AG4::resizeEvent(QResizeEvent* event)
{
	kruskal->move(this->rect().width() - 100, 10);
	prim->move(this->rect().width() - 100, 40);
	reset->move(this->rect().width() - 100, 70);
	QMainWindow::resizeEvent(event);
}

void AG4::on_kruskal_clicked()
{
	std::vector<Edge*> result;
	graph.kruskal(result);
	SecondWindow* secondWindow = new SecondWindow(graph.getNodes(), result, this);
	secondWindow->resize(1000, 800);
	secondWindow->show();
}

void AG4::on_prim_clicked()
{
	std::vector<Edge*> result;
	graph.prim(result);
	SecondWindow* secondWindow = new SecondWindow(graph.getNodes(), result, this);
	secondWindow->resize(1000, 800);
	secondWindow->show();
}

void AG4::onShowNumericInputDialog()
{
	if (firstNode && secondNode) {
		if (numericDialog.exec() == QDialog::Accepted) {
			uint16_t enteredValue = numericDialog.getEnteredValue();
			graph.addEdge(firstNode, secondNode, enteredValue);
			update();
		}
	}
}
//Buttons
void AG4::on_reset_clicked()
{
	if (isButtonPressed == false)
	{
		for (Edge* edge : graph.getEdges())
			if (edge)
				delete edge;

		for (Node* node : graph.getNodes())
			if (node)
				delete node;

		graph.clear();
	}
}