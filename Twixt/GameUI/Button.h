#pragma once

#include <QLabel>
#include <QGridLayout>
#include <QtSvg>
#include <QSvgWidget>

class Button : public QWidget
{
	Q_OBJECT

public:
	Button(QString headerText, QWidget* parent = nullptr, QString descriptionText = "", QSvgWidget* icon = nullptr);

	const QFont& GetHeaderFont() const;
	const QFont& GetDescriptionFont() const;
	int GetIconSize() const;

	void SetHeaderFont(const QFont& font);
	void SetDescriptionFont(const QFont& font);
	void SetIconSize(int size);
	void SetTextColor(QColor color);
	void SetTextShadowColor(QColor color);
	void SetShadowColor(QColor color);
	void SetShadowYOffset(int offset);

signals:
	void ButtonClicked();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	QGridLayout* m_layout;
	QLabel* m_headerLabel, * m_descriptionLabel;
	QSvgWidget* m_icon;
};

