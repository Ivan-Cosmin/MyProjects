#pragma once

#include "Button.h"

enum class EButtonPressed
{
	playButton,
	settingsButton,
};

class MainMenuScreen : public QWidget
{
	Q_OBJECT

public:
	MainMenuScreen(QWidget* parent = nullptr);

public slots:
	void OnSettingsButtonClicked();
	void OnPlayButtonClicked();

signals:
	void MenuClicked(const EButtonPressed& button);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	void InitPageWidgets();
	const QFont GetResizedFont(const QFont& font, float textRatio);
	int GetResizedIcon(int size, float sizeRatio);

private:
	QGridLayout* m_layout;
	QLabel* m_mainText, *m_imageWidget;
	Button* m_settingsButton, * m_playButton;

	static const uint16_t mainTextSize = 55;
	static const uint16_t headerLabelSize = 35;
	static const uint16_t descriptionLabelSize = 20;
	static const uint16_t svgIconSize = 70;

};

