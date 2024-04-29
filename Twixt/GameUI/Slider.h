#pragma once

#include <QSlider>
#include <QLabel>
#include <QGridLayout>

class Slider : public QWidget
{
	Q_OBJECT

public:

	Slider(const uint16_t minValue, const uint16_t maxValue, QWidget* parent);

	void SetValue(uint16_t value);
	uint16_t GetValue() const noexcept;

private slots:
	void OnSliderValueChanged(int value);

private: 
	QGridLayout* m_layout;
	QSlider* m_slider;
	QLabel* m_label;
};

