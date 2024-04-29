#include <QFile>

#include "FileUtils.h"

QString FileUtils::StylesheetFileToString(const QString& path)
{
	QFile file(path);
	file.open(QFile::ReadOnly);
	QString output = QLatin1String(file.readAll());
	return output;
}
