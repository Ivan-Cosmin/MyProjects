#pragma once
#include "Edge.h"
#include <vector>
#include <unordered_map>
#include <QPoint>
#include <iostream>
#include <queue>


class Graph
{
public:
	//Constructors && Destructors
	Graph();
	//TODO Copy Construct
	~Graph();

	//Getters
	std::vector<Node*> getNodes() const noexcept;
	std::vector <Edge*> getEdges() const noexcept;
	std::unordered_map<Node*, std::vector<Edge*>> getGraph() const noexcept;

	//Verify
	Node* nodeExists(const QPoint& pos) const ;
	Node* otherThanSelectedExists(const QPoint& pos) const;

	//Setters
	void addEdge(Node* firstNode, Node* secondNode, const uint16_t& cost);
	void addNode(Node* node);

	//Reset
	void clear();

	//Algorithm
	void kruskal(std::vector<Edge*>& result);
	void prim(std::vector<Edge*>& result);

private:
	int inTreeCount(const std::vector<bool>& inTree) const; 
	bool edgeAlreadyExists(Node* firstNode, Node* secondNode);

private:
	std::unordered_map<Node*, std::vector<Edge*>> m_graph;
};