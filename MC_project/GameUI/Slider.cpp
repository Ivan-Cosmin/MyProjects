#include "Slider.h"

Slider::Slider(uint16_t minValue, uint16_t maxValue, QWidget* parent)
	: QWidget{parent}
	, m_layout{new QGridLayout{this}}
	, m_slider{new QSlider{Qt::Horizontal, this}}
	, m_label{new QLabel{this}}
{
	// Set the limits
	m_slider->setMinimum(minValue);
	m_slider->setMaximum(maxValue);


	m_label->setMinimumWidth(50);

	m_layout->addWidget(m_slider, 0, 0, Qt::AlignLeft);
	m_layout->addWidget(m_label, 0, 1, Qt::AlignRight);

	setLayout(m_layout);

	connect(m_slider, SIGNAL(valueChanged(int)), SLOT(OnSliderValueChanged(int)));
}

void Slider::SetValue(uint16_t value)
{
	m_slider->setValue(value);
}

uint16_t Slider::GetValue() const noexcept
{
	return m_slider->value();
}

void Slider::OnSliderValueChanged(int value)
{
	m_label->setText(QString::number(value));
}
