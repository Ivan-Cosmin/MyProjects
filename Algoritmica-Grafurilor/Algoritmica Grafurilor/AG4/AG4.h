#pragma once
#include "Graph.h"
#include "NumericDialogBox.h"
#include "SecondWindow.h"
#include <QtWidgets/QMainWindow>
#include "ui_AG4.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>

class AG4 : public QMainWindow
{
	Q_OBJECT

public:
	AG4(QWidget* parent = nullptr);
	~AG4();
	void paintNode(QPainter& painter, Node* node);
	void drawLine(QPainter& painter, Edge* edge);
	void drawCost(QPainter& painter, Edge* edge);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;


private slots:
	void on_reset_clicked();
	void on_kruskal_clicked();
	void on_prim_clicked();
	void onShowNumericInputDialog();

private:
	Ui::AG4Class ui;
	Graph graph;
	Node* firstNode, * secondNode;
	bool isMousePressed;
	QPushButton* reset;
	QPushButton* kruskal;
	QPushButton* prim;
	bool isButtonPressed;
	NumericDialogBox numericDialog;
};