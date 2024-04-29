#include <format>

#include "HistoryWidget.h"
#include "ColorUtils.h"

HistoryWidget::HistoryWidget(QWidget* parent) 
	: QListWidget{parent}
{
	// Empty
}

void HistoryWidget::AddColumnItem(IPlayerPtr player, const Position& position)
{
	QIcon icon = ColorUtils::ColoredIconFromImage(":/GameUI/images/profile.png", player->GetColor());

	std::string text = std::format("Column added at position ({}, {})",
									position.GetRow(), position.GetColumn());

	QListWidgetItem* item = new QListWidgetItem(icon, QString::fromStdString(std::move(text)));
	addItem(item);
}

void HistoryWidget::AddBridgeItem(IPlayerPtr player, Position& firstPosition, Position& secondPosition, bool removed)
{
	QIcon icon = ColorUtils::ColoredIconFromImage(":/GameUI/images/profile.png", player->GetColor());

	std::string text = std::format("Bridge between ({}, {}) -> ({}, {}) {}",
									firstPosition.GetRow(), firstPosition.GetColumn(),
									secondPosition.GetRow(), secondPosition.GetColumn(),
									removed ? "removed" : "added");

	QListWidgetItem* item = new QListWidgetItem(icon, QString::fromStdString(std::move(text)));
	addItem(item);
}
