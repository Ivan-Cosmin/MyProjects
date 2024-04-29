#include <QFileDialog>
#include <QFileInfo>

#include "GameScreen.h"
#include "FileUtils.h"
#include "Dialog.h"

#include "IGameSettings.h"


GameScreen::GameScreen(IGamePtr game, QWidget* parent)
	: QWidget{ parent }
	, m_game{ game }
	, m_layout{ new QGridLayout{this} }
	, m_history{ new HistoryWidget{this} }
	, m_firstPlayerBar{ new PlayerBar{game->GetFirstPlayer(), true, this} }
	, m_secondPlayerBar{ new PlayerBar{game->GetSecondPlayer(), false, this} }
	, m_board{ new BoardWidget{game->GetBoard(), game->GetTurn(),
			  game->GetFirstPlayer()->GetColor(), game->GetSecondPlayer()->GetColor(),
			  this} }
	, m_loadButton{new QPushButton{"Load", this}}
	, m_saveButton{new QPushButton{"Save", this}}
	, m_restartButton{new QPushButton{"Restart", this}}
{

	QWidget* panel = new QWidget{ this };
	QGridLayout* panelLayout = new QGridLayout{ panel };
	panelLayout->addWidget(m_saveButton, 0, 0);
	panelLayout->addWidget(m_loadButton, 0, 1);
	panelLayout->addWidget(m_restartButton, 0, 2);
	panelLayout->addWidget(m_history, 1, 0, 1, 3);

	panel->setLayout(panelLayout);
	panel->setFixedWidth(350);


	m_layout->addWidget(m_firstPlayerBar, 0, 0, 1, 4);
	m_layout->addWidget(m_board, 1, 0, 1, 3);
	m_layout->addWidget(panel, 1, 3);
	m_layout->addWidget(m_secondPlayerBar, 2, 0, 1, 4);
	
	setLayout(m_layout);

	connect(m_board,
		SIGNAL(BoardClicked(const Position&, const Qt::MouseButton&)),
		SLOT(OnBoardClicked(const Position&, const Qt::MouseButton&)));

	connect(m_history,
		SIGNAL(itemActivated(QListWidgetItem*)),
		SLOT(OnHistoryClicked(QListWidgetItem*)));

	connect(m_saveButton, SIGNAL(clicked()), SLOT(OnSaveClicked()));
	connect(m_loadButton, SIGNAL(clicked()), SLOT(OnLoadClicked()));
	connect(m_restartButton, SIGNAL(clicked()), SLOT(OnRestartClicked()));

	QString stylesheet{ FileUtils::StylesheetFileToString("./stylesheets/game.qss") };
	setStyleSheet(stylesheet);
}

void GameScreen::SetWindowFullScreen(bool isFullScreen)
{
	m_board->SetWindowFullScreen(isFullScreen);
}

void GameScreen::OnColumnPlaced(Position& position, IPlayerPtr player)
{
	m_history->AddColumnItem(player, position);
}

void GameScreen::OnBridgePlaced(Position& firstPos, Position& secondPos, IPlayerPtr player)
{
	m_history->AddBridgeItem(player, firstPos, secondPos, false);
}

void GameScreen::OnBridgeRemoved(Position& firstPos, Position& secondPos, IPlayerPtr player)
{
	m_history->AddBridgeItem(player, firstPos, secondPos, true);
}

void GameScreen::OnSwapRequest()
{
	Dialog* dialog = new Dialog(this);
	auto generatedText = dialog->LoadDialog(
		"A swap request has been made",
		"Do you want to swap with first player?"
	);
	auto response = dialog->ExecuteDialog(generatedText, true);
	m_game->SwapResponse(response);
}

void GameScreen::OnSwapResponse(bool response)
{
	if (response)
	{
		update();
	}
}

void GameScreen::OnGameEnd(EGameResult result)
{
	Dialog* dialog = new Dialog(this);
	
	std::string resultString;
	switch (result)
	{
	case EGameResult::FirstPlayerWon:
		resultString = m_game->GetFirstPlayer()->GetName();
		break;
	case EGameResult::SecondPlayerWon:
		resultString = m_game->GetSecondPlayer()->GetName();
		break;
	case EGameResult::Tie:
		resultString = "It's a tie!";
		break;

	}

	auto generatedText = dialog->LoadDialog(
		"The game has ended:",
		result == EGameResult::Tie
			? resultString : resultString + " won the game!",
		"Do you want to start a new game?"
	);

	auto response = dialog->ExecuteDialog(generatedText, true);
	if (!response) emit(ReturnToMainMenu());
	m_history->clear();
	OnRestartClicked();
}

void GameScreen::OnHistoryClicked(QListWidgetItem* item)
{
	if (IGameSettings::GetInstance()->GetGamemode() != EGamemode::Standard) return;

	const auto& index = m_history->currentRow() + 1;
	m_game->PreviewTable(index);
	m_board->setEnabled(index == m_history->count());
	update();
}

void GameScreen::OnBoardClicked(const Position& position, const Qt::MouseButton& button)
{

	if (button == Qt::LeftButton)
	{
		m_game->PlaceColumn(position);
	}
	else if (button == Qt::RightButton)
	{

		auto currentColumn{ m_game->GetBoard()->GetElement(position) };
		bool currentPlayerTurn = currentColumn && currentColumn->GetPlayer() == m_game->GetTurn();

		if (!currentColumn) return;
		else if (m_selectedColumnPos == Position::EmptyPosition())
		{
			if (!currentPlayerTurn) return;
			m_selectedColumnPos = position;
			m_board->ChangeSelectedColumn(position);
		}
		else
		{
			if (m_selectedColumnPos != position && currentPlayerTurn)
			{
				if (m_game->GetBoard()->BridgeExists(m_selectedColumnPos, position))
				{
					m_game->RemoveBridge(m_selectedColumnPos, position);
				}
				else
				{
					m_game->MakeBridge(m_selectedColumnPos, position);
				}
			}

			m_selectedColumnPos = Position::EmptyPosition();
			m_board->ChangeSelectedColumn(Position::EmptyPosition());
		}
	}
	bool isFirstPlayerTurn = m_game->GetTurn() == m_game->GetFirstPlayer();
	bool isSecondPlayerTurn = m_game->GetTurn() == m_game->GetSecondPlayer();
	m_firstPlayerBar->Update(isFirstPlayerTurn);
	m_secondPlayerBar->Update(isSecondPlayerTurn);
}

void GameScreen::OnSaveClicked()
{
	QString filePath = QFileDialog::getSaveFileName(this, "Save Game", "", "Standard Twixt Notation (*.stn);;Portable Twixt Game (*.ptg)");
	QFileInfo fileInfo(filePath);
	QString fileExtension = fileInfo.suffix();

	m_game->SaveGame(filePath.toStdString(), fileExtension == "ptg" ? StorageFormat::PTG : StorageFormat::STN);
}

void GameScreen::OnLoadClicked()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Load Game", "", "Standard Twixt Notation (*.stn);;Portable Twixt Game (*.ptg)");
	QFileInfo fileInfo(filePath);
	QString fileExtension = fileInfo.suffix();

	m_game->LoadGame(filePath.toStdString(), fileExtension == "ptg" ? StorageFormat::PTG : StorageFormat::STN);

	bool isFirstPlayerTurn = m_game->GetTurn() == m_game->GetFirstPlayer();
	bool isSecondPlayerTurn = m_game->GetTurn() == m_game->GetSecondPlayer();
	m_firstPlayerBar->Update(isFirstPlayerTurn);
	m_secondPlayerBar->Update(isSecondPlayerTurn);
	update();

}

void GameScreen::OnRestartClicked()
{
	m_game->Restart();
	m_history->clear();
	bool isFirstPlayerTurn = m_game->GetTurn() == m_game->GetFirstPlayer();
	bool isSecondPlayerTurn = m_game->GetTurn() == m_game->GetSecondPlayer();
	m_firstPlayerBar->Update(isFirstPlayerTurn);
	m_secondPlayerBar->Update(isSecondPlayerTurn);
	update();
}
