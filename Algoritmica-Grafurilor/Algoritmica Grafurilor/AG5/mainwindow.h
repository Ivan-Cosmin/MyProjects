#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QMainWindow>
#include "Node.h"
#include "Graph.h"
#include "ui_mainwindow.h"
#include <stack>
#include <qstack.h>
#include <qfile.h>
#include <QXmlStreamReader>

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    mainwindow(QWidget *parent = nullptr, QMainWindow* mainWindow = nullptr);
    ~mainwindow();
private:

	void resizeEvent(QResizeEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void ReadFromFile();

	inline QPointF CoordMapToScreen(const QPointF& mapCoord) const;
	inline QPointF CoordScreenToMap(const QPointF& screenCoord) const;

	int FindCloseNodeId(const Node& pos);

	void Reset();

	std::vector<int> Dijkstra(bool useHeuristicAstar = true);
	std::vector<std::vector<std::pair<int, float>>> getAdjList() const;

private:
    Ui::mainwindowClass ui;
	QMainWindow m_mainWindow;
	Graph m_graph;

	int minimumLat, minimumLong;
	int maximumLat, maximumLong;
	int startPos{-1},endPos{-1};
	
};
