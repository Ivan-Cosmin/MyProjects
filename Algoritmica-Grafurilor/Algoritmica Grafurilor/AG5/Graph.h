#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <queue>

enum class EGraphType
{
	orientat,
	neorientat
};

class Graph
{
public:
	Graph();

	const std::unordered_map<int, NodePtr>& getNodes() const;
	std::vector<Arch> getArches() const;
	int getNumberOfNodes() const;
	EGraphType getType()const;
	NodePtr getSelectedNode()const;

	void setType(EGraphType ty);
	void setSelectedNode(NodePtr n);

	void addNode(NodePtr newNode);
	void addArch(const Arch& e);

	//std::vector<std::vector<int>> getAdjLists() const;
	std::vector<std::vector<bool>> getAdjMatrix() const;


private:
	std::unordered_map<int, NodePtr> m_nodes;
	NodePtr m_selectedNode;
	std::vector<Arch> m_arches;

	EGraphType m_type;
};


#endif // GRAPH_H
