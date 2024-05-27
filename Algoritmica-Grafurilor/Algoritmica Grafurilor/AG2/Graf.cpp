#include "Graf.h"

Graf::Graf(const int& lines, const int& columns, 
	       const int& nrOfNodes, const int&nrOfOutputs
		  )
	:m_nrOfNodes{nrOfNodes}
	,m_nrOfOutputs{nrOfOutputs}
	,m_start{ nullptr }

{
	MatrixResize(lines, columns);
}
Graf::Graf(const Graf& g)
	:m_nrOfNodes{g.m_nrOfNodes}
	,m_nrOfOutputs{g.m_nrOfOutputs}
	,m_start{g.m_start}
{
	int lines = g.m_matrix.size(), columns = g.m_matrix[0].size();
	uint8_t element;

	for (int line = 0; line < lines; line++)
		for (int column = 0; column < columns; column++)
		{
			element = g.m_matrix[line][column]->getValue();
			if (element)
				m_matrix[line][column] = new Node({ line,column }, element);
			else
				m_matrix[line][column] = nullptr;
		}
}
Graf::Graf()
	:m_nrOfNodes{0}
	,m_nrOfOutputs{0}
	,m_start{nullptr}
{
}
Graf::~Graf()
{
	for (int line = 0; line < m_matrix.size(); line++)
		for (int column = 0; column < m_matrix[0].size(); column++)
			delete m_matrix[line][column];
}

void Graf::MatrixResize(const int& lines, const int& columns)
{
	m_matrix.resize(lines);
	for (int line = 0; line < lines; line++)
		m_matrix[line].resize(columns);
}

std::vector<std::vector<Node*>>& Graf::GetMatrix()
{
	return m_matrix;
}
const QMap<QPoint, QPoint>& Graf::GetParents()
{
	return m_parents;
}
const std::vector<QPoint>& Graf::GetOutputs()
{
	return m_outputs;
}
const std::vector<std::stack<QPoint>>& Graf::GetVectorForNodesToPaint()
{
	return m_vectorForNodesToPaint;
}
const int& Graf::GetSizeLines() const
{
	return m_matrix.size();
}
Node* Graf::GetNode(const int& line, const int& column) const
{
	return m_matrix[line][column];
}
const int& Graf::GetSizeColumns() const
{
	return m_matrix[0].size();
}
const int& Graf::GetNrOutputs() const
{
	return m_nrOfOutputs;
}

bool Graf::NodeIsNull(const int& line, const int& column)
{
	if (m_matrix[line][column] == nullptr)
		return true;
	return false;
}
bool Graf::NodeIsForPath(const int& line, const int& column)
{
	return m_matrix[line][column]->getSelected();
}
uint8_t Graf::ValueNode(const int& line, const int& column) const
{
	return m_matrix[line][column]->getValue();
}
void Graf::BFS()
{
	int line = m_start->getX();
	int column = m_start->getY();
	while (m_nrOfOutputs)
	{
		if (m_matrix[line][column] != nullptr)
		{
				//To Node from left
					if (column - 1 >= 0)
						if (m_matrix[line][column - 1] != nullptr && (
							m_matrix[line][column - 1]->getValue() == '1' ||
							m_matrix[line][column - 1]->getValue() == '2')&&
						   !m_matrix[line][column - 1]->getVerified())
						{
							m_matrix[line][column - 1]->setVerified(true);
							m_parents[QPoint{ line,column - 1 }] = QPoint{ line,column };
							m_nextNode.emplace(line, column - 1);
							if (m_matrix[line][column - 1]->getValue() == '2')
								m_nrOfOutputs--;
						}

				//To Node from right
					if (column + 1 < m_matrix[0].size())
						if (m_matrix[line][column + 1] != nullptr && (
							m_matrix[line][column + 1]->getValue() == '1' ||
							m_matrix[line][column + 1]->getValue() == '2') &&
						   !m_matrix[line][column + 1]->getVerified())
						{
							m_matrix[line][column + 1]->setVerified(true);
							m_parents[QPoint{ line,column + 1 }] = QPoint{ line,column };
							m_nextNode.emplace(line, column + 1);
							if (m_matrix[line][column + 1]->getValue() == '2')
								m_nrOfOutputs--;
						}

				//To Node from up
					if (line - 1 >= 0)
						if (m_matrix[line - 1][column] != nullptr && (
							m_matrix[line - 1][column]->getValue() == '1' ||
							m_matrix[line - 1][column]->getValue() == '2') &&
						   !m_matrix[line - 1][column]->getVerified())
						{
							m_matrix[line - 1][column]->setVerified(true);
							m_parents[QPoint{ line - 1,column }] = QPoint{ line,column };
							m_nextNode.emplace(line - 1, column);
							if (m_matrix[line - 1][column]->getValue() == '2')
								m_nrOfOutputs--;
						}

				//To Node from down
					if (line + 1 < m_matrix.size())
						if (m_matrix[line + 1][column] != nullptr && (
							m_matrix[line + 1][column]->getValue() == '1' ||
							m_matrix[line + 1][column]->getValue() == '2') &&
							!m_matrix[line + 1][column]->getVerified())
						{
							m_matrix[line + 1][column]->setVerified(true);
							m_parents[QPoint{ line + 1,column }] = QPoint{ line,column };
							m_nextNode.emplace(line + 1, column);
							if (m_matrix[line + 1][column]->getValue() == '2')
								m_nrOfOutputs--;
						}

				if (m_nextNode.empty())
					break;
			line = m_nextNode.front().first;
			column = m_nextNode.front().second;
			m_nextNode.pop();
		}
	}
}
void Graf::MakeVectorForNodesPaints()
{
	for (auto output : m_outputs)
	{
		std::stack<QPoint> stack;
		QPoint element = output;
		while (element != m_start->getCoord())
		{
			element = m_parents.value(element);
			if (m_parents.find(element) != m_parents.end())
				stack.push(element);
			else break;
		}
		m_vectorForNodesToPaint.push_back(stack);
	}
}

std::istream& operator>>(std::istream& fin, Graf& G)
{
	int lines, columns;
	uint8_t element;
	fin >> lines >> columns;

	G.m_matrix.resize(lines);
	for (int line = 0; line < lines; line++)
		G.m_matrix[line].resize(columns);

	for (int line = 0; line < lines; line++)
	for (int column = 0; column < columns; column++)
		
		{
			fin >> element;
			if (element != '0')
			{
				Node* n = new Node({ line,column }, element);
				G.m_matrix[line][column] = n;
				if (element != '3')
				{
					if (element == '2')
					{
						G.m_nrOfOutputs++;
						G.m_outputs.push_back({ line,column });
					}
					else
						G.m_nrOfNodes++;
				}
				else
					G.m_start = n;
			}
			else
				G.m_matrix[line][column] = nullptr;
		}
	return fin;
}

bool operator<(const QPoint& First, const QPoint& Second)
{
	if (First.x() != Second.x())
		return First.x() < Second.x();
	else
		return First.y() < Second.y();
}

