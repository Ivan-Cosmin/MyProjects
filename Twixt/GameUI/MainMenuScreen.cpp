
#include <QLabel>
#include <QMouseEvent>
#include "MainMenuScreen.h"
#include "FileUtils.h"

MainMenuScreen::MainMenuScreen(QWidget* parent)
	: QWidget{ parent }
	, m_layout{ new QGridLayout{this} }
{
	// Init the page content
	InitPageWidgets();

	// import the stylesheet for design
	auto stylesheet{ FileUtils::StylesheetFileToString("stylesheets/mainmenu.qss") };
	setStyleSheet(stylesheet);

	// Add rules for the layout
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	m_layout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(m_layout);

	connect(m_playButton, SIGNAL(ButtonClicked()), SLOT(OnPlayButtonClicked()));
	connect(m_settingsButton, SIGNAL(ButtonClicked()), SLOT(OnSettingsButtonClicked()));

}

void MainMenuScreen::OnSettingsButtonClicked()
{
	emit(MenuClicked(EButtonPressed::settingsButton));
}

void MainMenuScreen::OnPlayButtonClicked()
{
	emit(MenuClicked(EButtonPressed::playButton));
}

void MainMenuScreen::resizeEvent(QResizeEvent* event)
{
	static const float mainTextRatio = static_cast<float>(mainTextSize) / qMin(width(), height());
	static const float headerLabelRatio = static_cast<float>(headerLabelSize) / qMin(width(), height());
	static const float descriptionLabelRatio = static_cast<float>(descriptionLabelSize) / qMin(width(), height());
	static const float svgIconRatio = static_cast<float>(svgIconSize) / qMin(width(), height());

	const QFont& mainFont = m_mainText->font();
	const QFont& playHeaderFont = m_playButton->GetHeaderFont();
	const QFont& settingsHeaderFont = m_settingsButton->GetHeaderFont();
	const QFont& playDescriptionFont = m_playButton->GetDescriptionFont();
	const QFont& settingsDescriptionFont = m_settingsButton->GetDescriptionFont();
	int playIconSize = m_playButton->GetIconSize();
	int settingsIconSize = m_settingsButton->GetIconSize();

	m_mainText->setFont(GetResizedFont(mainFont, mainTextRatio));
	m_playButton->SetHeaderFont(GetResizedFont(playHeaderFont, headerLabelRatio));
	m_settingsButton->SetHeaderFont(GetResizedFont(settingsHeaderFont, headerLabelRatio));
	m_playButton->SetDescriptionFont(GetResizedFont(playDescriptionFont, descriptionLabelRatio));
	m_settingsButton->SetDescriptionFont(GetResizedFont(settingsDescriptionFont, descriptionLabelRatio));
	m_playButton->SetIconSize(GetResizedIcon(playIconSize, svgIconRatio));
	m_settingsButton->SetIconSize(GetResizedIcon(settingsIconSize, svgIconRatio));
}

void MainMenuScreen::InitPageWidgets()
{
	// Image init
	QLabel* imageWidget{ new QLabel(this) };
	imageWidget->setObjectName("imageWidget");
	QPixmap presentationImage(":/GameUI/images/presentation.png");
	imageWidget->setPixmap(presentationImage);
	imageWidget->setScaledContents(true);

	// Header text init
	QString mainTextString = "<center>Play Twixt</center>\n<center>on the #1 App!</center>";
	m_mainText = new QLabel(std::move(mainTextString), this);

	// Play button init
	QSvgWidget* playButtonIcon = new QSvgWidget(":/GameUI/images/controller.svg");
	playButtonIcon->setMaximumSize(svgIconSize, svgIconSize);
	m_playButton = new Button("Play", this, "Play local with your friends", playButtonIcon);
	m_playButton->setObjectName("playButton");
	m_playButton->SetShadowColor("#466b3a");

	// Settings button init
	QSvgWidget* settingsButtonIcon = new QSvgWidget(":/GameUI/images/settings.svg");
	settingsButtonIcon->setMaximumSize(80, 80);
	m_settingsButton = new Button("Settings", this, "Change the game settings", settingsButtonIcon);
	m_settingsButton->setObjectName("settingsButton");
	m_settingsButton->SetShadowColor("#333230");
	m_settingsButton->SetTextColor("#C4C4C3");
	m_settingsButton->SetTextShadowColor("#242423");
	
	// Add widgets for the screen layout
	m_layout->addWidget(imageWidget, 0, 0, 4, 1);
	m_layout->addWidget(m_mainText, 0, 1, 2, 1, Qt::AlignCenter);
	m_layout->addWidget(m_playButton, 2, 1);
	m_layout->addWidget(m_settingsButton, 3, 1);
}

const QFont MainMenuScreen::GetResizedFont(const QFont& font, float textRatio)
{
	const float newSize = qMin(width(), height()) * textRatio;
	QFont newFont(font);
	newFont.setPixelSize(newSize);
	return std::move(newFont);
	
}

int MainMenuScreen::GetResizedIcon(int size, float sizeRatio)
{
	return std::move(qMin(width(), height()) * sizeRatio);
	
}
