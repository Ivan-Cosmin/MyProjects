#include "Graph.h"

//Constructors && Destructors
Graph::Graph()
{
}
Graph::~Graph()
{
	for (Edge* edge : getEdges())
		if (edge)
			delete edge;

	for (Node* node : getNodes())
		if (node)
			delete node;

	clear();
}

//Getters
std::unordered_map<Node*, std::vector<Edge*>> Graph::getGraph() const noexcept
{
	return m_graph;
}
std::vector<Node*> Graph::getNodes() const noexcept
{
	std::vector<Node*> nodes;
	for (auto& pair : m_graph) {
		nodes.push_back(pair.first);
	}
	return nodes;
}
std::vector<Edge*> Graph::getEdges() const noexcept
{
	std::vector<Edge*> edges;
	for (auto& pair : m_graph)
	{
		for (Edge* edge : pair.second)
			if (std::ranges::find(edges, edge) == edges.end())
				edges.push_back(edge);
	}
	return edges;
}

//Setters
void Graph::addEdge(Node* firstNode, Node* secondNode, const uint16_t& cost)
{
	 if(!edgeAlreadyExists(firstNode, secondNode))
	 {
		 Edge* edge = new Edge{ firstNode,secondNode,cost };
		 if (edge)
		 {
			 m_graph[firstNode].push_back(edge);
			 m_graph[secondNode].push_back(edge);
		 }
	 }
}
void Graph::addNode(Node* node)
{
	m_graph[node] = {};
}

//Verify
Node* Graph::nodeExists(const QPoint& pos) const
{
	for (Node* node : getNodes())
	{
		if (fabs(node->getX() - pos.x()) < Node::m_kDimNode * 1.5 &&
			fabs(node->getY() - pos.y()) < Node::m_kDimNode * 1.5)
			return node;
	}
	return nullptr;
}
Node* Graph::otherThanSelectedExists(const QPoint& pos) const
{
	for (Node* node : getNodes())
	{
		if (!node->isSelected())
			if (fabs(node->getX() - pos.x()) < Node::m_kDimNode * 1.5 &&
				fabs(node->getY() - pos.y()) < Node::m_kDimNode * 1.5)
				return node;
	}
	return nullptr;
}

int Graph::inTreeCount(const std::vector<bool>& inTree) const
{
	return std::ranges::count(inTree, true);
}

bool Graph::edgeAlreadyExists(Node* firstNode, Node* secondNode)
{
	for (Edge* edge : m_graph[firstNode])
		for (Edge* edge1 : m_graph[secondNode])
			if (edge == edge1)
			{
				auto itFirst = std::ranges::find (m_graph[firstNode], edge);
				if (itFirst != m_graph[firstNode].end()) {
					m_graph[firstNode].erase(itFirst);
				}

				auto itSecond = std::ranges::find(m_graph[secondNode], edge);
				if (itSecond != m_graph[secondNode].end()) {
					m_graph[secondNode].erase(itSecond);
				}

				delete edge;
				return true;
			}

	return false;
}

//Reset
void Graph::clear()
{
	m_graph.clear();
}

void Graph::kruskal(std::vector<Edge*>& result)
{
	std::vector<Edge*> edges = getEdges();

	std::ranges::sort(edges, [](const Edge* const a , const Edge* const b) {
		return a->getCost() < b->getCost();
		});

	std::unordered_map<Node*, std::vector<Node*>> sets;
	for (const auto& pair : m_graph) {
		sets[pair.first] = { pair.first };
	}

	for (Edge* edge : edges) {
		std::vector<Node*>* set1 = &sets[edge->getFirstNode()];
		std::vector<Node*>* set2 = &sets[edge->getSecondNode()];

		if (std::ranges::find_first_of(*set1,*set2) == set1->end()) {
			result.push_back(edge);

			set1->insert(set1->end(), set2->begin(), set2->end());
			for (Node* node : *set1) {
				sets[node] = *set1;
			}
		}
	}
}

void Graph::prim(std::vector<Edge*>& result)
{
	struct EdgeCompare 
	{
		bool operator()(const Edge* a, const Edge* b) const
		{
			return a->getCost() > b->getCost();
		}
	};
	std::vector<Node*> nodes = getNodes();
	std::vector<Edge*> edges = getEdges();

	std::priority_queue<Edge*, std::vector<Edge*>, EdgeCompare> minHeap;
	std::vector<bool> inTree(nodes.size(), false);

	Node* startNode = nodes.front();
	inTree[startNode->getLabel()] = true;

	for(auto edge : m_graph[startNode])
		minHeap.push(edge);

	while (minHeap.size() > 0 && inTreeCount(inTree) < nodes.size()) 
	{
		Edge* currentEdge = minHeap.top();
		minHeap.pop();

		Node* endNode = (inTree[currentEdge->getFirstNode()->getLabel()]) ? currentEdge->getSecondNode() : currentEdge->getFirstNode();
		if (!inTree[endNode->getLabel()]) 
		{
			inTree[endNode->getLabel()] = true;
			result.push_back(currentEdge);

			for (auto edge : m_graph[endNode])
				if(edge != currentEdge)
				minHeap.push(edge);

		}
	}
}
