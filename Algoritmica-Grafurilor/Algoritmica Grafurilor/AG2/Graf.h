#pragma once
#include "Node.h"
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <QMap>

class Graf : public QWidget
{
   
public:
    Graf(const int& ,const int&m, const int&, const int&);
    Graf(const Graf& g);
    Graf();
    ~Graf();

    void MakeVectorForNodesPaints();
    void MatrixResize(const int&, const int&);

    const int& GetSizeLines() const;
    Node* GetNode(const int& line, const int& column) const;
    const int& GetSizeColumns() const; 
    const int& GetNrOutputs() const; 
    std::vector<std::vector<Node*>>& GetMatrix();
    const QMap<QPoint, QPoint>& GetParents();
    const std::vector<QPoint>& GetOutputs();
    const std::vector<std::stack<QPoint>>& GetVectorForNodesToPaint();

    bool NodeIsNull(const int&, const int&);
    bool NodeIsForPath(const int& line, const int& column);
    uint8_t ValueNode(const int&, const int&) const;
    void BFS();

private:
    std::vector<std::vector<Node*>> m_matrix;
    QMap<QPoint,QPoint> m_parents;
    std::queue<std::pair<int, int>> m_nextNode;
    std::vector<QPoint> m_outputs;
    int m_nrOfNodes;
    int m_nrOfOutputs;
    Node* m_start;
    std::vector<std::stack<QPoint>> m_vectorForNodesToPaint;
public:
    friend std::istream& operator>> (std::istream& fin, Graf& G);
};

