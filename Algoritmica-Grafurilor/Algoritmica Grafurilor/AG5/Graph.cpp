#include "Graph.h"

#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <stack>

Graph::Graph()
	: m_selectedNode{ nullptr }
	, m_type(EGraphType::neorientat)
{

}


const std::unordered_map<int, NodePtr>& Graph::getNodes() const
{
	return m_nodes;
}
std::vector<Arch> Graph::getArches()const
{
	return m_arches;
}

int Graph::getNumberOfNodes() const
{
	return m_nodes.size();
}

EGraphType Graph::getType()const
{
	return m_type;
}

NodePtr Graph::getSelectedNode()const
{
	return m_selectedNode;
}

void Graph::setType(EGraphType ty)
{
	m_type = ty;
}

void Graph::setSelectedNode(NodePtr n)
{
	m_selectedNode = n;
}

void Graph::addNode(NodePtr newNode)
{
	m_nodes[m_nodes.size()] = newNode;
}

void Graph::addArch(const Arch& e)
{
	m_arches.push_back(e);
}

std::vector<std::vector<bool>> Graph::getAdjMatrix() const
{
	std::vector<std::vector<bool>> matrix;
	matrix.resize(m_nodes.size());
	for (auto& line : matrix)
		line.resize(m_nodes.size(), false);


	for (auto& arch : m_arches)
		matrix[arch.getFirstNodePtr()->getValue()][arch.getSecondNodePtr()->getValue()] = true;

	return matrix;
}




































//void Graph::loadMapFromXML()
//{
//	QFile file("Harta_Luxemburg.xml");
//	if (!file.open(QFile::ReadOnly | QFile::Text))
//	{
//		qDebug() << "Cannot open file: " << file.errorString();
//		return;
//	}
//
//	QXmlStreamReader xmlReader(&file);
//	while (!xmlReader.atEnd() && !xmlReader.hasError())
//	{
//		QXmlStreamReader::TokenType token = xmlReader.readNext();
//		if (token == QXmlStreamReader::StartElement)
//		{
//			if (xmlReader.name().toString() == "node")
//			{
//				int id = xmlReader.attributes().value("id").toInt();
//				int latitude = xmlReader.attributes().value("latitude").toInt();
//				int longitude = xmlReader.attributes().value("longitude").toInt();
//				Node* newNode = new Node(QPoint(latitude, longitude), id);
//				addNode(newNode);
//			}
//			else if (xmlReader.name().toString() == "arc") 
//			{
//				int from = xmlReader.attributes().value("from").toInt(); 
//				int to = xmlReader.attributes().value("to").toInt(); 
//				int length = xmlReader.attributes().value("length").toInt(); 
//
//				Node* nodeFrom = getNodeById(from); 
//				Node* nodeTo = getNodeById(to); 
//
//				if (nodeFrom && nodeTo) 
//				{
//					Arch* newArch = new Arch(nodeFrom, nodeTo); 
//					newArch->setCost(length); 
//					addArch(newArch); 
//				}
//			}
//		}
//	}
//
//	if (xmlReader.hasError())
//	{
//		qDebug() << "Error parsing XML: " << xmlReader.errorString();
//	}
//
//	file.close();
//}

