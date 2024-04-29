#pragma once

#include <QGridLayout>
#include <QWidget>

#include "IBoard.h"

enum class EDirection
{
	Top,
	Bottom,
	Left,
	Right,
};

class BoardWidget : public QWidget
{
	Q_OBJECT

public:
	BoardWidget(const IBoardPtr gameBoard, IPlayerPtr currentPlayer, EColor firstPlayerColor, EColor secondPlayerColor, QWidget* parent = nullptr);
	void ChangeSelectedColumn(const Position& selectedColumn);
	void SetWindowFullScreen(bool isFullScreen);

signals:
	void BoardClicked(const Position& position, const Qt::MouseButton& button);


protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	Position CoordinatesToPosition(QPointF pos) const;
	QPointF PositionToCoordinates(uint16_t row, uint16_t column) const;
	bool IsCorner(int row, int column) const;
	QLineF GetLineDelimiter(EDirection direction) const;
	float CalculateRadius(bool isSmallCircle) const;
	QPointF PointTranslation(QPointF firstPoint, QPointF secondPoint);
	float CalculateSlope(QPointF firstNode, QPointF secondNode);

private:
	bool m_isFullScreen;

	const IBoardPtr m_gameBoard;
	IPlayerPtr m_currentPlayer;
	EColor m_firstPlayerColor, m_secondPlayerColor;

	static const size_t smallCircleScalingFactor{12};
	static const size_t largeCircleScalingFactor{3};

	Position m_hovered;
	Position m_selected;

};

