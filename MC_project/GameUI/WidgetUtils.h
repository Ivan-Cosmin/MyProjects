#include <QWidget>
#include <QApplication>
#include <QScreen>

class WidgetUtils {
public:
	static void CenterWidget(QWidget* widgetToCenter, QWidget* parent = nullptr);
};