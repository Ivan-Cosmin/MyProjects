#include "Graf.h"

Graf::Graf()
    :isOriented{true}
{}
Graf::Graf(Graf& g)
    :isOriented{ true }
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
            if (n->getValue() == firstNode->getValue())
                selectFirstNode = n;
            else
                if (n->getValue() == secondNode->getValue())
                    selectSecondNode = n;
            if (selectFirstNode && selectSecondNode)
            {
                addEdge(new Edge{ selectFirstNode ,selectSecondNode });
                break;
            }
        }
    }
}
Graf::~Graf()
{
    for (int i = 0; i < m_edges.size(); i++)
        delete m_edges[i];

    for (int i = 0; i < m_nodes.size(); i++)
        delete m_nodes[i];
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
void Graf::addEdge(Node* firstNode, Node* secondNode)
{
    Edge* edge = new Edge(firstNode, secondNode);
    m_edges.push_back(edge);
}
void Graf::addEdge(Edge* edge)
{
    Edge* ed = new Edge(edge->getFirstNode(), edge->getSecondNode());
    m_edges.push_back(ed);
}

void Graf::setOrientedOrNot(bool tOrF)
{
    isOriented = tOrF;
}

Node* Graf::GetNod(QMouseEvent* e)
{
    for (Node* n : m_nodes)
    {
        if (fabs(n->getX() - e->pos().x()) < Node::DimNODE &&
            fabs(n->getY() - e->pos().y()) < Node::DimNODE)
            return n;
    }
    return nullptr;
}

bool Graf::verifyNods(QMouseEvent* e)
{
    for (Node* n : m_nodes)
    {   if(!n->getIsSelected())
        if (fabs(n->getX() - e->pos().x()) < Node::DimNODE &&
            fabs(n->getY() - e->pos().y()) < Node::DimNODE)
            return false;
    }
    return true;
}
bool Graf::verifyEdges(Edge* ed)
{
    for (Edge* E : m_edges)
    {
        if (E->getFirstNode()->getCoord() == ed->getFirstNode()->getCoord() && E->getSecondNode()->getCoord() == ed->getSecondNode()->getCoord())
            return false;

        if(!isOrientedOrNot())
        if (E->getSecondNode()->getCoord() == ed->getFirstNode()->getCoord() && E->getFirstNode()->getCoord() == ed->getSecondNode()->getCoord())
            return false;
    }
    return true;
}

void Graf::saveMatrixUnoriented()
{
    std::ofstream fout("text.txt");

    fout << m_nodes.size() << "\n";
    for (int i = 1; i <= m_nodes.size(); i++)
    {
        fout << i << ":";
        for (Edge* ed : m_edges)
        {
            if (ed->getFirstNode()->getValue() == i)
                fout << ed->getSecondNode()->getValue() << ", ";
            else
                if (ed->getSecondNode()->getValue() == i)
                    fout << ed->getFirstNode()->getValue() << ", ";
        }
        fout << "\n";
    }
    fout.close();
}
void Graf::saveMatrixOriented()
{
    std::ofstream fout("text.txt");

    fout << m_nodes.size() << "\n";
    for (int i = 1; i <= m_nodes.size(); i++)
    {
        fout << i << ":";
        for (Edge* ed : m_edges)
        {
            if (ed->getFirstNode()->getValue() == i)
                fout << ed->getSecondNode()->getValue() << ", ";
        }
        fout << "\n";
    }
    fout.close();
}

void Graf::reset()
{
    if (m_edges.size() != 0)
    {
        for (int i = 0; i < m_edges.size(); i++)
            delete m_edges[i];
        m_edges.resize(0);
    }

    if (m_nodes.size() != 0)
    {
        for (int i = 0; i < m_nodes.size(); i++)
            delete m_nodes[i];
        m_nodes.resize(0);
    }
}

std::vector<Node*> Graf::getNodes()
{
    return m_nodes;
}
std::vector<Edge*> Graf::getEdges()
{
    return m_edges; 
}

bool Graf::isOrientedOrNot()
{
    return isOriented;
}
