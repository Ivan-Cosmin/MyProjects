#pragma once
#include "Node.h"
#include "edge.h"

#include<list>
#include <vector>
#include <stack>
#include <QMouseEvent>
#include <fstream>
#include <limits>
#include <algorithm>
#include <unordered_set>
const int INF = std::numeric_limits<int>::max();

class Graf
{

public:
	Graf();
	Graf(Graf& g);
	~Graf();
	void addNode(Node* n);
	void addNode(QPoint p);
	void AddEdge(Node*, Node*);
	void AddEdge(Edge*);

	std::vector<Node*>& GetNodes();
	std::vector<Edge*>& getEdges();
	Node* GetNode(QMouseEvent* e);
	Node* GetRoot();

	bool ExistNode(QMouseEvent* e);
	bool ExistEdge(Edge* ed);
	bool isTree();

	void WriteInFile(const std::vector<Node*>& vector);
	void FindRoot();

	bool hasCycles();
	std::vector<Node*> topologicalSort(std::vector<Edge*>& resultEdgeUsed);

private:
	void DFS(Node* start);

private:

	std::vector<Node*> m_nodes; //N
	std::vector<Edge*> m_edges; //A
	std::unordered_set<Node*> visitedSet;
	Node* m_root;
};

