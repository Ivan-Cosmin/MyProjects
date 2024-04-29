#include <QPainter>
#include <QMouseEvent>

#include "BoardWidget.h"
#include "ColorUtils.h"

BoardWidget::BoardWidget(const IBoardPtr gameBoard, IPlayerPtr currentPlayer, EColor firstPlayerColor, EColor secondPlayerColor, QWidget* parent) 
	: QWidget{ parent }
	, m_gameBoard{ gameBoard }
	, m_currentPlayer{currentPlayer}
	, m_firstPlayerColor{ firstPlayerColor }
	, m_secondPlayerColor{ secondPlayerColor }
	, m_isFullScreen{ false }

{
	setMouseTracking(true);
}


void BoardWidget::ChangeSelectedColumn(const Position& selectedColumn)
{
	m_selected = selectedColumn;
	update();
}

void BoardWidget::SetWindowFullScreen(bool isFullScreen)
{
	m_isFullScreen = isFullScreen;
	QResizeEvent resizeEvent(size(), size());
	this->resizeEvent(&resizeEvent);
}

void BoardWidget::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing);

	QPen pen;
	QColor color;

	float radius;
	const auto boardSize{ m_gameBoard->GetSize() };

	for (uint16_t row{ 0 }; row < boardSize; ++row)
	{
		for (uint16_t column{ 0 }; column < boardSize; ++column)
		{
			if (IsCorner(row, column)) continue;

			if (m_selected.IsEqual(row, column))
			{
				color = Qt::white;
				radius = CalculateRadius(false);
			}
			else if (auto element{ m_gameBoard->GetElement(row, column) }; element)
			{
				color = ColorUtils::TwixtColorToQColor(element->GetPlayer()->GetColor());

				if (color == Qt::transparent)
				{
					color = Qt::white;
					radius = CalculateRadius(m_hovered.IsEqual(row, column) ? false : true);
				}
				else radius = CalculateRadius(false);
			}
			else if (m_hovered.IsEqual(row, column))
			{
				color = Qt::white;
				radius = CalculateRadius(false);
			}
			else
			{
				color = Qt::white;
				radius = CalculateRadius(true);
			}


			painter.setPen(color);
			painter.setBrush(color);
			
			painter.drawEllipse(PositionToCoordinates(row, column), radius, radius);
		}
	}

	pen.setWidth(3);
	for (auto bridge : m_gameBoard->GetBridgesPositions())
	{
		auto& [pos1, pos2] {bridge};
		QPointF firstPoint{ PositionToCoordinates(pos1.GetRow(), pos1.GetColumn()) };
		QPointF secondPoint{ PositionToCoordinates(pos2.GetRow(), pos2.GetColumn()) };
		QPointF firstPointOffset{ PointTranslation(firstPoint, secondPoint) };
		const auto playerColor {m_gameBoard->GetElement(pos1)->GetPlayer()->GetColor()};
		color = ColorUtils::TwixtColorToQColor(playerColor);

		pen.setColor(color);
		painter.setPen(pen);

		painter.drawLine(firstPoint + firstPointOffset, secondPoint - firstPointOffset);
	}

	color = ColorUtils::TwixtColorToQColor(m_firstPlayerColor);
	pen.setWidth(2);
	pen.setColor(color);
	painter.setPen(pen);

	QLineF topLine{ GetLineDelimiter(EDirection::Top) };
	QLineF bottomLine{ GetLineDelimiter(EDirection::Bottom) };
	painter.drawLine(topLine);
	painter.drawLine(bottomLine);

	color = ColorUtils::TwixtColorToQColor(m_secondPlayerColor);
	pen.setColor(color);
	painter.setPen(pen);

	QLineF leftLine{ GetLineDelimiter(EDirection::Left) };
	QLineF rightLine{ GetLineDelimiter(EDirection::Right) };
	painter.drawLine(leftLine);
	painter.drawLine(rightLine);
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
	Position pos{ CoordinatesToPosition(event->position()) };
	if (IsCorner(pos.GetRow(), pos.GetColumn())) return;
	emit(BoardClicked(std::move(pos), event->button()));
	update();
}

void BoardWidget::mouseMoveEvent(QMouseEvent* event)
{
	m_hovered = CoordinatesToPosition(event->position());
	update();
}

void BoardWidget::leaveEvent(QEvent* event)
{
	m_hovered = Position::EmptyPosition();
	update();
}

void BoardWidget::resizeEvent(QResizeEvent* event)
{
	const auto size = qMin(width(), height());
	m_isFullScreen ? resize(size * 1.75f, size) : resize(size, size);
	QWidget::resizeEvent(event);
}

Position BoardWidget::CoordinatesToPosition(QPointF pos) const
{
	const auto boardSize{ m_gameBoard->GetSize() };
	const auto circleWidth{ static_cast<float>(width()) / boardSize };
	const auto circleHeight{ static_cast<float>(height()) / boardSize };

	std::size_t line = pos.y() / circleHeight ;
	std::size_t col = pos.x() / circleWidth ;

	return std::move(Position(line, col));

}

QPointF BoardWidget::PositionToCoordinates(uint16_t row, uint16_t column) const
{
	const auto boardSize{ m_gameBoard->GetSize() };
	const auto circleWidth{ static_cast<float>(width()) / boardSize };
	const auto circleHeight{ static_cast<float>(height()) / boardSize };

	// formula calculates the center of the rectangle (0.5f marks the half of the width/height)
	return std::move(QPointF((column + 0.5f) * circleWidth, (row + 0.5f) * circleHeight));
}

bool BoardWidget::IsCorner(int row, int column) const
{
	const auto boardSize{ m_gameBoard->GetSize() };
	return (row == 0 && column == 0) ||
		(row == 0 && column == boardSize - 1) ||
		(row == boardSize - 1 && column == 0) ||
		(row == boardSize - 1 && column == boardSize - 1);
}

QLineF BoardWidget::GetLineDelimiter(EDirection direction) const
{
	const auto boardSize{ m_gameBoard->GetSize() };
	const auto circleWidth{ static_cast<float>(width()) / boardSize };
	const auto circleHeight{ static_cast<float>(height()) / boardSize };
	QPointF lineStart, lineStop;

	if (direction == EDirection::Top || direction == EDirection::Bottom)
	{
		QPointF leftCircle, besideLeftCircle, rightCircle, besideRightCircle;
		const auto row = direction == EDirection::Top ? 0 : boardSize - 2;
		const auto leftColumn{ 1 };
		const auto rightColumn{ boardSize - 2 };

		leftCircle = PositionToCoordinates(row, leftColumn);
		besideLeftCircle = PositionToCoordinates(row + 1, leftColumn);
		rightCircle = PositionToCoordinates(row, rightColumn);
		besideRightCircle = PositionToCoordinates(row + 1, rightColumn);

		lineStart = (leftCircle + besideLeftCircle) / 2.0f;
		lineStop = (rightCircle + besideRightCircle) / 2.0f;
	}
	else
	{
		QPointF topCircle, besideTopCircle, bottomCircle, besideBottomCircle;
		const auto topRow{ 1 };
		const auto bottomRow{ boardSize - 2 };
		const auto column = direction == EDirection::Left ? 0 : boardSize - 2;

		topCircle = PositionToCoordinates(topRow, column);
		besideTopCircle = PositionToCoordinates(topRow, column + 1);
		bottomCircle = PositionToCoordinates(bottomRow, column);
		besideBottomCircle = PositionToCoordinates(bottomRow, column + 1);

		lineStart = (topCircle + besideTopCircle) / 2.0f;
		lineStop = (bottomCircle + besideBottomCircle) / 2.0f;
	}


	return QLineF(lineStart, lineStop);
}

float BoardWidget::CalculateRadius(bool isSmallCircle) const
{
	const auto boardSize{ m_gameBoard->GetSize() };
	const auto circleWidth{ static_cast<float>(width()) / boardSize };
	const auto circleHeight{ static_cast<float>(height()) / boardSize };

	float radius{ static_cast<float>(qMin(circleWidth, circleHeight)) };
	radius /= isSmallCircle ? smallCircleScalingFactor : largeCircleScalingFactor;

	return radius;
}

QPointF BoardWidget::PointTranslation(QPointF firstPoint, QPointF secondPoint)
{
	const auto slope{ CalculateSlope(firstPoint, secondPoint) };
	const auto radius{ CalculateRadius(false) };

	return firstPoint.x() < secondPoint.x()
		? QPointF{ radius * cos(atan(slope)), -radius * sin(atan(slope)) }
		: QPointF{ -radius * cos(atan(slope)), radius * sin(atan(slope)) };
}

float BoardWidget::CalculateSlope(QPointF firstNode, QPointF secondNode)
{
	return -static_cast<float>((firstNode.y() - secondNode.y())) / (firstNode.x() - secondNode.x());
}

