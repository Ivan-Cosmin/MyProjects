
#include <QGridLayout>
#include <QFontDatabase>

#include "GameUI.h"
#include "FileUtils.h"

GameUI::GameUI(QWidget *parent)
    : QMainWindow{parent}
    , m_screens{new QStackedWidget{this}}
{
    resize(1100, 600);
    LoadFonts();
    InitializeMainMenu();

    // Set the stylesheet from file
    QString stylesheet{ FileUtils::StylesheetFileToString("stylesheets/default.qss") };
	setStyleSheet(stylesheet);

    // Connect buttons
	connect(m_mainMenuScreen, SIGNAL(MenuClicked(const EButtonPressed&)), SLOT(OnMainMenuButtonClicked(const EButtonPressed&)));

}

void GameUI::OnMainMenuButtonClicked(const EButtonPressed& button)
{
    // Load game screen when button pressed 
    if (button == EButtonPressed::playButton)
    {
        IGameSettingsPtr settings = IGameSettings::GetInstance();
        const auto& game = IGame::Produce(settings);
        m_gameScreen = std::make_shared<GameScreen>(game, this);
        connect(m_gameScreen.get(), SIGNAL(ReturnToMainMenu()), SLOT(OnReturnToMainMenuClicked()));
        game->AddObserver(m_gameScreen);
        resize(1050, 800);
        m_screens->addWidget(m_gameScreen.get());
        m_screens->setCurrentWidget(m_gameScreen.get());
        WidgetUtils::CenterWidget(this);
    }
    else if (button == EButtonPressed::settingsButton)
    {
        IGameSettingsPtr settings{ IGameSettings::GetInstance() };
		m_settingsScreen = new SettingsScreen(settings);

        // Call show function to resize properly for centering on main menu and then hide
        m_settingsScreen->show();
        WidgetUtils::CenterWidget(m_settingsScreen, this);
        m_settingsScreen->hide();

        // And then execute the dialog to prevent user press other menu buttons
        m_settingsScreen->exec();
    }
}

void GameUI::OnReturnToMainMenuClicked()
{
    m_screens->setCurrentWidget(m_mainMenuScreen);
}

void GameUI::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::WindowStateChange)
	{
        if (m_screens->currentWidget() == m_gameScreen.get())
        {
            if (windowState() && Qt::WindowFullScreen)
            {
                m_gameScreen->SetWindowFullScreen(true);
            }
            else
            {
                m_gameScreen->SetWindowFullScreen(false);
            }
        }
	}
}

void GameUI::InitializeMainMenu()
{
    // Initialize the main menu screen
	m_mainMenuScreen = new MainMenuScreen(m_screens);

    // Add main menu screen to screen list
	m_screens->addWidget(m_mainMenuScreen);
	m_screens->setCurrentWidget(m_mainMenuScreen);

    // Display the screen
	setCentralWidget(m_screens);
}

void GameUI::LoadFonts()
{
    QString path{ ":/GameUI/fonts/" };
    QFontDatabase::addApplicationFont(path + "Montserrat-Black.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Bold.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Light.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Medium.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Regular.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-SemiBold.ttf");
    QFontDatabase::addApplicationFont(path + "Montserrat-Thin.ttf");

}
