
#include "SettingsScreen.h"
#include "FileUtils.h"
#include "ColorUtils.h"

const uint16_t SettingsScreen::minTableSize{5}, SettingsScreen::maxTableSize{50};
const uint16_t SettingsScreen::minColumnLimit{20}, SettingsScreen::maxColumnLimit{100};
const uint16_t SettingsScreen::minBridgeLimit{20}, SettingsScreen::maxBridgeLimit{100};

SettingsScreen::SettingsScreen(IGameSettingsPtr settings, QWidget* parent)
	: QDialog{parent}
	, m_gameSettings{settings}
	, m_layout{new QGridLayout{this}}
	, m_tableSizeSlider{new Slider{minTableSize, maxTableSize, this}}
	, m_columnLimitSlider{new Slider{minColumnLimit, maxColumnLimit, this}}
	, m_bridgeLimitSlider{new Slider{minBridgeLimit, maxBridgeLimit, this}}
	, m_firstPlayerName{new QLineEdit{this}}
	, m_secondPlayerName{new QLineEdit{this}}
	, m_firstPlayerColor{new QComboBox{this}}
	, m_secondPlayerColor{new QComboBox{this}}
	, m_gamemode{new QComboBox{this}}
	, m_updateButton{new Button{"Update"}}
	, m_discardButton{new Button{"Discard"}}
{
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	
	ColorUtils::GenerateColorVector(m_colors);

	InitializeButtons();
	InitializeValues();
	InitializeLayout();

	auto stylesheet{ FileUtils::StylesheetFileToString("stylesheets/settings.qss") };
	setStyleSheet(stylesheet);

	connect(m_updateButton, SIGNAL(ButtonClicked()), SLOT(OnUpdateButtonClicked()));
	connect(m_discardButton, SIGNAL(ButtonClicked()), SLOT(OnDiscardButtonClicked()));
}

void SettingsScreen::OnUpdateButtonClicked()
{
	m_gameSettings->SetTableSize(m_tableSizeSlider->GetValue());
	m_gameSettings->SetColumnLimit(m_columnLimitSlider->GetValue());
	m_gameSettings->SetBridgeLimit(m_bridgeLimitSlider->GetValue());
	m_gameSettings->SetFirstPlayerName(m_firstPlayerName->text().toStdString());
	m_gameSettings->SetFirstPlayerColor(ColorUtils::StringToTwixtColor(m_firstPlayerColor->currentText()));
	m_gameSettings->SetSecondPlayerName(m_secondPlayerName->text().toStdString());
	m_gameSettings->SetSecondPlayerColor(ColorUtils::StringToTwixtColor(m_secondPlayerColor->currentText()));

	QString gamemodeText = m_gamemode->currentText();
	EGamemode selectedGamemode;

	if (gamemodeText == "Standard") selectedGamemode = EGamemode::Standard;
	else if (gamemodeText == "Mined Columns") selectedGamemode = EGamemode::MinedColumns;
	else if (gamemodeText == "Bulldozer") selectedGamemode = EGamemode::Bulldozer;
	m_gameSettings->SetGamemode(selectedGamemode);

	close();
}

void SettingsScreen::OnDiscardButtonClicked()
{
	close();
}

void SettingsScreen::AddFieldToLayout(QString fieldName, QWidget* widget)
{
	QLabel* fieldLabel{ new QLabel{fieldName, this} };

	if (widget)
	{
		fieldLabel->setObjectName("FieldText");
		m_layout->addWidget(fieldLabel, m_layout->rowCount(), 0, Qt::AlignLeft);
		m_layout->addWidget(widget, m_layout->rowCount() - 1, 1, Qt::AlignRight);

	}
	else
	{
		QString objectName{ fieldName.isEmpty() ? "Empty" : "HeaderFieldText" };
		fieldLabel->setObjectName(objectName);
		m_layout->addWidget(fieldLabel, m_layout->rowCount(), 0, Qt::AlignLeft);
	}
}

void SettingsScreen::InitializeButtons()
{
	m_updateButton->setObjectName("updateButton");
	m_updateButton->SetShadowColor("#466b3a");
	m_updateButton->SetShadowYOffset(3);

	m_discardButton->setObjectName("discardButton");
	m_discardButton->SetShadowColor("#781c1c");
	m_discardButton->SetShadowYOffset(3);


}

void SettingsScreen::InitializeValues()
{
	m_tableSizeSlider->SetValue(m_gameSettings->GetTableSize());
	m_columnLimitSlider->SetValue(m_gameSettings->GetColumnLimit());
	m_bridgeLimitSlider->SetValue(m_gameSettings->GetBridgeLimit());

	m_firstPlayerName->setText(QString::fromStdString(m_gameSettings->GetFirstPlayerName().data()));
	m_secondPlayerName->setText(QString::fromStdString(m_gameSettings->GetSecondPlayerName().data()));

	InitializePlayerColorPick(true);
	InitializePlayerColorPick(false);
	InitializeGamemodes();

}

void SettingsScreen::InitializePlayerColorPick(bool isFirstPlayerBox)
{
	QComboBox* currentBox;
	EColor initialColor;
	if (isFirstPlayerBox)
	{
		currentBox = m_firstPlayerColor;
		initialColor = m_gameSettings->GetFirstPlayerColor();
	}
	else
	{
		currentBox = m_secondPlayerColor;
		initialColor = m_gameSettings->GetSecondPlayerColor();
	}

	for (auto color : m_colors)
	{
		const auto hexColor = ColorUtils::TwixtColorToQColor(color);
		const auto colorString = ColorUtils::TwixtColorToString(color);

		QPixmap pixmap(12, 12);
		pixmap.fill(hexColor);
		const auto icon{ QIcon(pixmap) };

		currentBox->addItem(icon, colorString);
		if (color == initialColor)
			currentBox->setCurrentIndex(currentBox->count() - 1);
	}
}

void SettingsScreen::InitializeGamemodes()
{
	m_gamemode->addItem("Standard");
	m_gamemode->addItem("Mined Columns");
	m_gamemode->addItem("Bulldozer");

	m_gamemode->setCurrentIndex(static_cast<int>(m_gameSettings->GetGamemode()));
}

void SettingsScreen::InitializeLayout()
{
	// Player settings related widgets
	AddFieldToLayout("");
	AddFieldToLayout("First Player Settings");
	AddFieldToLayout("Name", m_firstPlayerName);
	AddFieldToLayout("Color", m_firstPlayerColor);
	AddFieldToLayout("");
	AddFieldToLayout("Second Player Settings");
	AddFieldToLayout("Name", m_secondPlayerName);
	AddFieldToLayout("Color", m_secondPlayerColor);
	AddFieldToLayout("");

	// Game settings related widgets
	AddFieldToLayout("");
	AddFieldToLayout("Gamemodes settings");
	AddFieldToLayout("Gamemode", m_gamemode);
	AddFieldToLayout("");

	// Board settings related widgets
	AddFieldToLayout("Board settings");
	AddFieldToLayout("Table Size", m_tableSizeSlider);
	AddFieldToLayout("Pillars Number", m_columnLimitSlider);
	AddFieldToLayout("Bridges Number", m_bridgeLimitSlider);
	AddFieldToLayout("");

	m_layout->addWidget(m_updateButton, m_layout->rowCount(), 0, Qt::AlignLeft);
	m_layout->addWidget(m_discardButton, m_layout->rowCount()-1, 1, Qt::AlignRight);

	AddFieldToLayout("");

	setLayout(m_layout);

}

