#include "Graf.h"

Graf::Graf()
	:m_root{ nullptr }
{}
Graf::Graf(Graf& g)
{
	for (Node* n : g.m_nodes)
	{
		addNode(n);
	}
	for (Edge* ed : g.m_edges)
	{
		Node* selectFirstNode{ nullptr }, * selectSecondNode{ nullptr }, * firstNode{ ed->getFirstNode() }, * secondNode{ ed->getSecondNode() };
		for (Node* n : g.m_nodes)
		{
			if (n->GetValue() == firstNode->GetValue())
				selectFirstNode = n;
			else
				if (n->GetValue() == secondNode->GetValue())
					selectSecondNode = n;
			if (selectFirstNode && selectSecondNode)
			{
				AddEdge(new Edge{ selectFirstNode ,selectSecondNode });
				break;
			}
		}
	}
}
Graf::~Graf()
{
	for (int i = 0; i < m_edges.size(); i++)
		if (m_edges[i] != nullptr)
		delete m_edges[i];

	for (int i = 0; i < m_nodes.size(); i++)
		if(m_nodes[i])
		delete m_nodes[i];
	m_edges.clear();
	m_nodes.clear();
}

void Graf::addNode(Node* n1)
{
	Node* n = new Node(n1);
	m_nodes.push_back(n);
}
void Graf::addNode(QPoint p)
{
	Node* n = new Node;
	n->setCoord(p);
	n->setValue(m_nodes.size() + 1);
	m_nodes.push_back(n);
}
void Graf::AddEdge(Node* firstNode, Node* secondNode)
{
	Edge* edge = new Edge(firstNode, secondNode);
	m_edges.push_back(edge);
}
void Graf::AddEdge(Edge* edge)
{
	Edge* ed = new Edge(edge->getFirstNode(), edge->getSecondNode());
	m_edges.push_back(ed);
}

bool Graf::ExistNode(QMouseEvent* e)
{
	for (Node* n : m_nodes)
	{
		if (!n->getIsSelected())
			if (fabs(n->GetX() - e->pos().x()) < Node::DimNODE &&
				fabs(n->GetY() - e->pos().y()) < Node::DimNODE)
				return false;
	}
	return true;
}
bool Graf::ExistEdge(Edge* ed)
{
	for (Edge* E : m_edges)
	{
		if (E->getFirstNode()->getCoord() == ed->getFirstNode()->getCoord() && 
			E->getSecondNode()->getCoord() == ed->getSecondNode()->getCoord())
			return false;
	}
	return true;
}

void Graf::WriteInFile(const std::vector<Node*>& vector)
{
	std::ofstream fout("text.txt");
	for (const auto& node : vector)
	{
		fout << node->GetValue() << " ";
	}
	fout.close();
}

void Graf::FindRoot()
{
	std::unordered_set<Node*> potentialRoots(m_nodes.begin(), m_nodes.end());

	for (Edge* edge : m_edges) {
		potentialRoots.erase(edge->getSecondNode());
	}

	if (potentialRoots.size() == 1)
		m_root = *(potentialRoots.begin());
	else
		m_root = nullptr;
}

bool Graf::hasCycles()
{
	std::unordered_set<Node*> visitedSet;
	std::unordered_set<Node*> onStackSet;
	std::stack<Node*> stack;

	for (Node* node : m_nodes) {
		if (!visitedSet.count(node)) {
			stack.push(node);

			while (!stack.empty()) {
				Node* current = stack.top();
				stack.pop();

				visitedSet.insert(current);
				onStackSet.insert(current);

				for (Edge* edge : m_edges) {
					if (edge->getFirstNode() == current) {
						Node* neighbor = edge->getSecondNode();

						if (!visitedSet.count(neighbor)) {
							stack.push(neighbor);
						}
						else if (onStackSet.count(neighbor)) {
							return true;
						}
					}
				}

				onStackSet.erase(current);
			}
		}
	}

	return false;
}

std::vector<Node*> Graf::topologicalSort(std::vector<Edge*>& resultEdgeUsed)
{
	{
		std::unordered_set<Node*> visitedSet;
		std::vector<Node*> result;
		
		std::stack<std::pair<Node*, bool>> stack;

		for (Node* node : m_nodes) {
			if (!visitedSet.count(node)) {
				stack.push({ node, false });

				while (!stack.empty()) {
					auto currentPair = stack.top();
					stack.pop();
					Node* current = currentPair.first;
					bool visited = currentPair.second;

					if (!visited) {
						visitedSet.insert(current);
						stack.push({ current, true });

						for (Edge* edge : m_edges) {
							if (edge->getFirstNode() == current && !visitedSet.count(edge->getSecondNode()))
							{
								stack.push({ edge->getSecondNode(), false });
								resultEdgeUsed.push_back(edge);
							}
						}
					}
					else {
						result.push_back(current);
					}
				}
			}
		}

		std::reverse(result.begin(), result.end());
		return result;
	}
}
void Graf::DFS(Node* start)
{
	visitedSet.clear();
	std::stack<Node*> stack;
	stack.push(start);

	while (!stack.empty()) {
		Node* current = stack.top();
		stack.pop();

		if (!visitedSet.count(current)) {
			visitedSet.insert(current);

			for (Edge* edge : m_edges) {
				if (edge->getFirstNode() == current && !visitedSet.count(edge->getSecondNode())) {
					stack.push(edge->getSecondNode());
				}
			}
		}
	}
}

bool Graf::isTree()
{

	if (hasCycles()) {
		return false;
	}

	if (m_edges.size() != m_nodes.size() - 1) {
		return false;
	}

	return true;
}



std::vector<Node*>& Graf::GetNodes()
{
	return m_nodes;
}
std::vector<Edge*>& Graf::getEdges()
{
	return m_edges;
}
Node* Graf::GetNode(QMouseEvent* e)
{
	for (Node* n : m_nodes)
	{
		if (fabs(n->GetX() - e->pos().x()) < Node::DimNODE &&
			fabs(n->GetY() - e->pos().y()) < Node::DimNODE)
			return n;
	}
	return nullptr;
}
Node* Graf::GetRoot()
{
	return m_root;
}
