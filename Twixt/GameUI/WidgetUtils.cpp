#include "WidgetUtils.h"
#include <QMainWindow>

void WidgetUtils::CenterWidget(QWidget* widgetToCenter, QWidget* parent /*= nullptr*/)
{
	if (!widgetToCenter) return;

	QRect parentGeometry;

	if (!parent)
	{
		// If no parent provided, center on screen
		QScreen* primaryScreen = QGuiApplication::primaryScreen();
		parentGeometry = primaryScreen->geometry();
	}
	else
	{
		// If parent provided, center on parent
		parentGeometry = parent->geometry();
	}

	// Calculate the center point of the screen
	float centerX = parentGeometry.x() + parentGeometry.width() / 2.0f;
	float centerY = parentGeometry.y() + parentGeometry.height() / 2.0f;

	// Calculate the top-left corner of the widget to center it
	float widgetX = centerX - widgetToCenter->width() / 2.0f;
	float widgetY = centerY - widgetToCenter->height() / 2.0f;

	// Move the widget to the calculated position
	widgetToCenter->move(widgetX, widgetY);
}

