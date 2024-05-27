#pragma once

#include "SecondWindow.h"
#include <QtWidgets/QMainWindow>
#include <QCoreApplication>
#include "ui_AG3.h"
#include "Graf.h"
#include "Node.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QTextStream>
#include <QDebug>
#include <QMainWindow>


namespace Ui { class AG3; }

class AG3 : public QMainWindow
{
	Q_OBJECT

public:
	AG3(QWidget* parent = nullptr);
	~AG3();

	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void paintEvent(QPaintEvent* e);
	void drawLine(Node* N1, Node* N2, int radius, QPainter& p);
	void drawArrow(QPoint Q1, QPoint Q2, QPainter& p);
	void paintNode(QPainter&, Node*);

private slots:
	void RootButton();
	void TopologicalSort();


private:
	SecondWindow* secondWindow;
	Graf m_graf;
	std::vector<Edge*> resultEdgeUsed;
	Node* m_firstNode;
	Node* m_secondNode;
	Ui::AG3Class ui;
	bool isMousePressed;
	QTextStream outStream{stdout};
};
