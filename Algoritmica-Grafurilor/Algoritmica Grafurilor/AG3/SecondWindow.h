#pragma once
#include <QMainWindow>
#include "Node.h"
#include "Edge.h"
#include<vector>

class SecondWindow : public QMainWindow
{
	Q_OBJECT

public:
	SecondWindow(std::vector<Node*> nodes, std::vector<Edge*> edges, QWidget* parent = nullptr);
	~SecondWindow();
	void paintEvent(QPaintEvent* e);
private:
	std::vector<Node*> m_nodes;
	std::vector<Edge*> m_edges;
};
