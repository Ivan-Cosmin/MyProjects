#pragma once

#include <QString>
#include <QColor>
#include <QComboBox>

#include "../GameLib/IPlayer.h"

struct ColorUtils 
{
	static void GenerateColorVector(std::vector<EColor>& colors);
	static QString TwixtColorToString(EColor color);
	static EColor StringToTwixtColor(QString string);
	static const QColor TwixtColorToQColor(EColor color);
	static void FillPixmapBackground(QPixmap& pixmap, EColor color);
	static QIcon ColoredIconFromImage(QString path, EColor color);
};