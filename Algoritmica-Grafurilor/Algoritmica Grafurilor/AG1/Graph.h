#pragma once
#include "Node.h"
#include "Edge.h"

#include <vector>
#include <QMouseEvent>
#include <fstream>

class Graf
{
   
public:
    Graf();
    Graf(Graf& g);
    ~Graf();
    void addNode(Node* n);
    void addNode(QPoint p);
    void addEdge(Node*, Node*);
    void addEdge(Edge*);
    void setOrientedOrNot(bool);

    std::vector<Node*> getNodes();
    std::vector<Edge*> getEdges();
    Node* GetNod(QMouseEvent* e);
    bool isOrientedOrNot();

    bool verifyNods(QMouseEvent* e);
    bool verifyEdges(Edge* ed);

    void saveMatrixUnoriented();
    void saveMatrixOriented();
    void reset();


private:
    std::vector<Node*> m_nodes;
    std::vector<Edge*> m_edges;
    bool isOriented;
};

