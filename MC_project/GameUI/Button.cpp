
#include <QGraphicsDropShadowEffect>
#include <QStyleOption>
#include <QPainter>


#include "Button.h"

Button::Button(QString headerText, QWidget* parent, QString descriptionText, QSvgWidget* icon)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{
	// Header
	m_headerLabel = new QLabel(headerText, this);
	m_headerLabel->setObjectName("headerLabel");

	// Add description if exists
	if (!descriptionText.isEmpty())
	{
		m_descriptionLabel = new QLabel(descriptionText, this);
		m_descriptionLabel->setObjectName("descriptionLabel");
	}

	// Add icon if exists
	if (icon)
	{
		m_icon = icon;
		m_icon->setParent(this);
		m_icon->setObjectName("icon");
	}

	// Add drop shadow to title
	auto titleEffect = new QGraphicsDropShadowEffect(m_headerLabel);
	titleEffect->setXOffset(0);
	titleEffect->setYOffset(1);

	if (!descriptionText.isEmpty())
	{
		// Add drop shadow to description
		auto descriptionEffect = new QGraphicsDropShadowEffect(m_descriptionLabel);
		descriptionEffect->setXOffset(0);
		descriptionEffect->setYOffset(1);

		m_descriptionLabel->setGraphicsEffect(descriptionEffect);
	}

	if (icon)
	{
		// Add drop shadow to button icon
		auto iconEffect = new QGraphicsDropShadowEffect(m_icon);
		iconEffect->setColor("#171716");
		iconEffect->setOffset(1);
		iconEffect->setBlurRadius(2);

		m_icon->setGraphicsEffect(iconEffect);
	}

	// Add the created effects to labels
	m_headerLabel->setGraphicsEffect(titleEffect);

	// Add a shadow to widget
	auto buttonEffect = new QGraphicsDropShadowEffect(this);
	buttonEffect->setXOffset(0);
	buttonEffect->setYOffset(8);
	setGraphicsEffect(buttonEffect);

	// Add the widgets to layout
	if (icon && !descriptionText.isEmpty())
	{
	
		// add all widgets if exists
		m_layout->addWidget(m_icon, 0, 0, 2, 1, Qt::AlignCenter);
		m_layout->addWidget(m_headerLabel, 0, 1, 1, 3, Qt::AlignLeft);
		m_layout->addWidget(m_descriptionLabel, 1, 1, 1, 3, Qt::AlignLeft);
	}
	else if (icon && descriptionText.isEmpty())
	{
		// add only the header and description label
		m_layout->addWidget(m_icon, 0, 0, Qt::AlignRight);
		m_layout->addWidget(m_headerLabel, 0, 1, 1, 3, Qt::AlignLeft);
	}
	else if (!icon && !descriptionText.isEmpty())
	{
		// add only the header and icon
		m_layout->addWidget(m_headerLabel, 0, 0, Qt::AlignLeft);
		m_layout->addWidget(m_descriptionLabel, 1, 0, Qt::AlignLeft);
	}
	else
	{
		m_layout->addWidget(m_headerLabel);
	}


	// Set the layout
	setLayout(m_layout);
}

const QFont& Button::GetHeaderFont() const
{
	return m_headerLabel->font();
}

const QFont& Button::GetDescriptionFont() const
{
	return m_descriptionLabel->font();
}

int Button::GetIconSize() const
{
	return m_icon->width();
}

void Button::SetHeaderFont(const QFont& font)
{
	m_headerLabel->setFont(font);
}

void Button::SetDescriptionFont(const QFont& font)
{
	m_descriptionLabel->setFont(font);
}

void Button::SetIconSize(int size)
{
	m_icon->setMaximumSize(size, size);
}

void Button::SetTextColor(QColor color)
{
	m_headerLabel->setStyleSheet("color: " + color.name());
	m_descriptionLabel->setStyleSheet("color: " + color.name());
}

void Button::SetTextShadowColor(QColor color)
{
	auto headerShadow = qobject_cast<QGraphicsDropShadowEffect*>(m_headerLabel->graphicsEffect());
	headerShadow->setColor(color);

	auto descriptionShadow = qobject_cast<QGraphicsDropShadowEffect*>(m_descriptionLabel->graphicsEffect());
	descriptionShadow->setColor(color);
}

void Button::SetShadowColor(QColor color)
{
	auto shadow = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
	shadow->setColor(color);
}

void Button::SetShadowYOffset(int offset)
{
	auto shadow = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
	shadow->setYOffset(offset);
}

void Button::mousePressEvent(QMouseEvent* event)
{
	emit(ButtonClicked());
}

// Forced to override paintEvent with this code becouse subclassing a QWidget and using stylesheets
// Source here: https://doc.qt.io/Qt-5/stylesheet-reference.html
void Button::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

