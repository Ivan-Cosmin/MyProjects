#pragma once

#include <QStackedWidget>
#include <QMainWindow>

#include "MainMenuScreen.h"
#include "SettingsScreen.h"
#include "GameScreen.h"
#include "WidgetUtils.h"

#include "IGame.h"



class GameUI : public QMainWindow
{
    Q_OBJECT

public:
    GameUI(QWidget *parent = nullptr);
    ~GameUI() = default;

public slots:
    void OnMainMenuButtonClicked(const EButtonPressed& button);
    void OnReturnToMainMenuClicked();

protected:
    void changeEvent(QEvent* event) override;

private:
    void InitializeMainMenu();
    void LoadFonts();

    QWidget* centralWidget;
    QStackedWidget* m_screens;
    MainMenuScreen* m_mainMenuScreen;
    SettingsScreen* m_settingsScreen;
    std::shared_ptr<GameScreen> m_gameScreen;
};
