#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent, QMainWindow* mainWindow)
    : QMainWindow(parent)
    , m_mainWindow(mainWindow) 
{
    ui.setupUi(this);
    ReadFromFile();
}

mainwindow::~mainwindow()
{}

void mainwindow::paintEvent(QPaintEvent* event)
{
    
    QPainter p(this);

    p.setPen(QColor(Qt::lightGray));

    auto m_arches = m_graph.getArches();
    auto m_nodes = m_graph.getNodes();

    for (const auto& e : m_arches)
    {
        const auto& startNode = e.getFirstNodePtr()->getPosition();
        const auto& finishNode = e.getSecondNodePtr()->getPosition();

        const auto firstScreenCoord = CoordMapToScreen({ startNode.x(), startNode.y() });
        const auto secondScreenCoord = CoordMapToScreen({ finishNode.x(), finishNode.y() });

        p.drawLine({ firstScreenCoord, secondScreenCoord });
    }


    //Draw selected nodes
    const float NodeRadius = 3.f;
    p.setBrush(QColor(Qt::cyan));
    if (startPos != -1)
    {
        QPointF screenCoord = CoordMapToScreen({ m_nodes[startPos]->getPosition().x(), m_nodes[startPos]->getPosition().y() });
        QRectF r(QPointF(screenCoord.x() - NodeRadius, screenCoord.y() - NodeRadius), QPointF(screenCoord.x() + NodeRadius, screenCoord.y() + NodeRadius));

        p.drawEllipse(r);
    }

    p.setBrush(QColor(Qt::darkYellow));
    if (endPos != -1)
    {
        QPointF screenCoord = CoordMapToScreen({ m_nodes[endPos]->getPosition().x(), m_nodes[endPos]->getPosition().y() });
        QRectF r(QPointF(screenCoord.x() - NodeRadius, screenCoord.y() - NodeRadius), QPointF(screenCoord.x() + NodeRadius, screenCoord.y() + NodeRadius));

        p.drawEllipse(r);
    }

    //Draw Shortest Path
    auto solution = Dijkstra(false);
    if (solution.empty())
        return;

    p.setPen(QColor(Qt::red));

    for (int i = 0; i < solution.size() - 1; i++)
    {
        const auto& startNode = m_nodes[solution[i]];
        const auto& finishNode = m_nodes[solution[i + 1]];

        const auto firstScreenCoord = CoordMapToScreen({ startNode->getPosition().x(), startNode->getPosition().y() });
        const auto secondScreenCoord = CoordMapToScreen({ finishNode->getPosition().x(), finishNode->getPosition().y() });

        p.drawLine({ firstScreenCoord, secondScreenCoord });
    }
}

void mainwindow::mouseReleaseEvent(QMouseEvent* event)
{
	QPointF screenClickPos = QPointF(event->pos());
	QPointF mapClickPos = CoordScreenToMap(screenClickPos);
	Node node(mapClickPos, -1);

	if (event->button() == Qt::LeftButton)
	{
		startPos = FindCloseNodeId(node);
	}
	else if (event->button() == Qt::RightButton)
	{
		endPos = FindCloseNodeId(node);
	}

	update();
}

void mainwindow::ReadFromFile()
{
    QFile file("./Harta_Luxemburg.xml");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file.";
        return;
    }

    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == QString("node")) {
                const QPoint pos = QPoint(xmlReader.attributes().value("latitude").toUInt(), xmlReader.attributes().value("longitude").toUInt());
                m_graph.addNode(std::make_shared<Node>(pos, m_graph.getNumberOfNodes()));

                if (m_graph.getNodes().size() == 1)
                {
                    minimumLat = pos.x();
                    minimumLong = pos.y();
                    maximumLat = pos.x();
                    maximumLong = pos.y();
                }
                if (m_graph.getNodes().size() > 1)
                {
                    minimumLat = std::min(pos.x(), minimumLat);
                    minimumLong = std::min(pos.y(), minimumLong);
                    maximumLat = std::max(pos.x(), maximumLat);
                    maximumLong = std::max(pos.y(), maximumLong);
                }

            }
            else if (xmlReader.name() == QString("arc")) {
                const auto& firstNode = xmlReader.attributes().value("from").toUInt();
                const auto& secondNode = xmlReader.attributes().value("to").toUInt();
                const auto& cost = xmlReader.attributes().value("length").toUInt();

                auto itFirst = m_graph.getNodes().find(firstNode);
                auto itSecond = m_graph.getNodes().find(secondNode);

                if (itFirst != m_graph.getNodes().end() && itSecond != m_graph.getNodes().end()) {
                    m_graph.addArch(Arch(itFirst->second, itSecond->second, cost));
                }
            }
        }
    }

    file.close();
}

inline QPointF mainwindow::CoordMapToScreen(const QPointF& mapCoord) const
{
	auto [mapLat, mapLng] = mapCoord;

	float mapEffectiveWidth = maximumLat - minimumLat;
	float mapEffectiveHeight = maximumLong - minimumLong;

	mapLat -= minimumLat;
	mapLng -= minimumLong;

	// 90 degrees
	float rotatedLat = mapLng;
	float rotatedLng = mapEffectiveWidth - mapLat;

	float screenLat = rotatedLat / mapEffectiveHeight * size().width();
	float screenLng = rotatedLng / mapEffectiveWidth * size().height();

	return { screenLat, screenLng };
}

inline QPointF mainwindow::CoordScreenToMap(const QPointF& screenCoord) const
{
	const auto& [screenLat, screenLong] = screenCoord;

	float effectiveMapLat = maximumLat - minimumLat;
	float effectiveMapLong = maximumLong - minimumLong;

	// 90 degrees
	float rotatedLat = size().height() - screenLong;
	float rotatedLng = screenLat;

	float mapLat = rotatedLat / size().height() * effectiveMapLat + minimumLat;
	float mapLong = rotatedLng / size().width() * effectiveMapLong + minimumLong;

	return { mapLat, mapLong };
}

int mainwindow::FindCloseNodeId(const Node& node)
{
    int minDistNodeId = -1; 
    float minimumDistance = INFINITY; 
    float currentDistance; 

    auto nodes = m_graph.getNodes(); 

    for (int i = 0; i < nodes.size(); ++i) 
    {
        const auto& currentNodeId = nodes[i]; 
        currentDistance = currentNodeId->getEulerDistance(node); 
        if (currentDistance < minimumDistance) 
        { 
            minimumDistance = currentDistance; 
            minDistNodeId = i; 
        }
    }

    return minDistNodeId; 
}

void mainwindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event); 
    update();
}

void mainwindow::Reset()
{
    startPos = -1;
    endPos = -1;
    update();
}

std::vector<int> mainwindow::Dijkstra(bool useHeuristicAstar)
{
    if (startPos == -1 || endPos == -1 || startPos == endPos) return {};

    static auto adjacencyList = getAdjList();

    class DijQElement
    {
    public:
        int node = 0;
        float dist = 0;
        float heuristic = 0;

        DijQElement(int node, float dist, float heuristic) : node(node), dist(dist), heuristic(heuristic) {}

        float getDistance() const { return dist + heuristic; }
        bool operator<(const DijQElement& other) const { return getDistance() > other.getDistance(); }
    };

    auto nodes = m_graph.getNodes();

    std::vector<int> parent(nodes.size(), -1);
    std::vector<bool> visited(nodes.size(), false);
    std::vector<float> distance(nodes.size(), INFINITY);
    std::priority_queue<DijQElement> pq;

    distance[startPos] = 0;
    pq.push({ startPos,0, 0 });

    while (!pq.empty())
    {
        const auto topElement = pq.top();

        if (visited[topElement.node]) {
            pq.pop();
            continue;
        }
        visited[topElement.node] = true;

        if (topElement.node == endPos) break;

        for (const auto& element : adjacencyList[topElement.node]) 
        {
            auto [node, edgeLen] = element;
            if (visited[node]) continue;

            if (distance[node] > edgeLen + distance[topElement.node]) 
            {
                distance[node] = edgeLen + distance[topElement.node];
                parent[node] = topElement.node;

                auto endNode = nodes.find(endPos);

                if (endNode != nodes.end())
                    pq.emplace(node, distance[node], (useHeuristicAstar ? nodes[node]->getEulerDistance(*endNode->second) : 0));
            }
        }

        pq.pop();
    }

    if (pq.empty())
        return {};

    int poz = endPos;
    std::vector<int> way;
    while (parent[poz] != -1) {
        way.emplace_back(poz);
        poz = parent[poz];
    }

    return way;
}

std::vector<std::vector<std::pair<int, float>>> mainwindow::getAdjList() const
{
    auto nodes = m_graph.getNodes();

    std::vector<std::vector<std::pair<int, float>>> adjacencyList;
    adjacencyList.resize(nodes.size());

    auto arches = m_graph.getArches();

    for (const auto& arch : arches)
    {
        adjacencyList[arch.getFirstNodePtr()->getValue()].emplace_back(arch.getSecondNodePtr()->getValue(), arch.getCost());
    }
    return adjacencyList;
}
