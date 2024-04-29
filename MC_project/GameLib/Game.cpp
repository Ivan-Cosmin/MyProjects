
#include <ranges>
#include <algorithm>

#include "Game.h"
#include "MinedGame.h"
#include "BulldozerGame.h"

IGamePtr IGame::Produce(const IGameSettingsPtr settings)
{
	return std::make_shared<Game>(settings);
}

Game::Game(const IGameSettingsPtr settings)
	: m_player1{ std::make_shared<Player>(settings->GetFirstPlayerName(), settings->GetFirstPlayerColor(),
							settings->GetBridgeLimit(), settings->GetColumnLimit())}
	, m_player2{ std::make_shared<Player>(settings->GetSecondPlayerName(), settings->GetSecondPlayerColor(),
							settings->GetBridgeLimit(), settings->GetColumnLimit())}
	, m_boardSize{ settings->GetTableSize() }
	, m_parser{ parser::ITwixtParser::Produce()}
	, m_board{ std::make_shared<Board>(settings->GetTableSize())}
	, m_gamemode{ settings->GetGamemode()}
	, m_notificationsDisabled{false}
	, m_firstGameMove{false}
	, m_gameEnded{false}
	, m_settings{settings}
{	
	m_turn = m_player1;

	m_minedGame = new MinedGame(m_board);
	m_bulldozerGame = new BulldozerGame(m_board);

	if (m_gamemode == EGamemode::MinedColumns) m_minedGame->AddMines();
	if (m_gamemode == EGamemode::Bulldozer) m_bulldozerGame->DestroyOrMove(m_player1, m_player2);
	if (m_board->GetSize() <= 7)
	{
		m_minimax = new Minimax(m_board, m_boardSize - 1, m_player1, m_player2);
	}
}


bool Game::PlaceColumn(const Position& position)
{
	if (m_gameEnded && !m_notificationsDisabled) return false;

	bool isMinedColumn = false;
	bool isFirstPlayer = m_turn == m_player1;
	bool canAdd = isFirstPlayer ? m_player1->HasColumnsToAdd() : m_player2->HasColumnsToAdd();

	if (!m_player1->HasColumnsToAdd() && !m_player2->HasColumnsToAdd())
	{
		m_gameEnded = true;
		NotifyGameEnd(EGameResult::Tie);
	}

	if (std::dynamic_pointer_cast<MinedColumn>(m_board->GetElement(position)))
		isMinedColumn = true;

	if ((position.GetRow() == 0 || position.GetRow() == m_board->GetSize() - 1) &&
		!isFirstPlayer) return false;

	if ((position.GetColumn() == 0 || position.GetColumn() == m_board->GetSize() - 1) &&
		isFirstPlayer) return false;

	if (!canAdd && !m_notificationsDisabled) return false;

	if (isMinedColumn) m_board->RemoveColumn(position);
	if (!m_board->PlaceColumn(position, m_turn)) return false;

	NotifyPlaceColumn(position, m_turn);
	if (!m_notificationsDisabled)
	{
		isFirstPlayer ? m_player1->DecreaseColumnNumber() : m_player2->DecreaseColumnNumber();
	}

	if (m_turn == m_player2 && m_gamemode == EGamemode::Bulldozer)
	{
		auto bulldozerPos = m_bulldozerGame->DestroyOrMove(m_player1, m_player2);
		auto bulldozerPlayer = m_board->GetElement(bulldozerPos)->GetPlayer();
		NotifyPlaceColumn(bulldozerPos, bulldozerPlayer);
	}
	ChangeTurn();

	if (!m_firstGameMove)
	{
		m_firstGameMove = true;
		NotifySwapEvent();
	}

	if (m_gamemode == EGamemode::MinedColumns && isMinedColumn)
	{
		m_minedGame->DestroyArea(position, m_player1, m_player2);
		isFirstPlayer ? m_player1->SetDoubleTurn(true) : m_player2->SetDoubleTurn(true);
	}

	return true;

}

bool Game::MakeBridge(const Position& firstPos, const Position& secondPos)
{
	if (m_gameEnded && !m_notificationsDisabled) return false;

	bool isFirstPlayer = m_turn == m_player1;

	bool canAdd = isFirstPlayer ? m_player1->HasBridgesToAdd() : m_player2->HasBridgesToAdd();
	if (!canAdd && !m_notificationsDisabled) return false;

	if (!m_board->MakeBridge(firstPos, secondPos, m_turn)) return false;

	NotifyMakeBridge(firstPos, secondPos, m_turn);

	if (!m_notificationsDisabled)
	{
		isFirstPlayer ? m_player1->DecreaseBridgeNumber() : m_player2->DecreaseBridgeNumber();
	}
	
	ComputePathToWin(0, firstPos, secondPos);

	auto winner = CheckWinner();
	if (winner)
	{
		NotifyGameEnd(winner == m_player1 ? EGameResult::FirstPlayerWon : EGameResult::SecondPlayerWon);
		m_gameEnded = true;
	}

	return true;
}

bool Game::RemoveBridge(const Position& firstPos, const Position& secondPos)
{
	if (m_gameEnded && !m_notificationsDisabled) return false;

	if (!m_board->RemoveBridge(firstPos, secondPos, m_turn)) return false;

	NotifyRemoveBridge(firstPos, secondPos, m_turn);
	if (!m_notificationsDisabled)
	{
		m_turn == m_player1 ? m_player1->IncreaseBridgeNumber() : m_player2->IncreaseBridgeNumber();
	}

	ComputePathToWin(1, firstPos, secondPos);

	return true;
}

void Game::SwapResponse(bool response)
{
	if (response) SwapPlayers();
	NotifySwapResponse(response);
}

void Game::SwapPlayers()
{
	std::string auxiliarName = m_player1->GetName().data();
	m_player1->SetName(m_player2->GetName());
	m_player2->SetName(auxiliarName);
}

IPlayerPtr Game::GetFirstPlayer() const
{
	return m_player1;
}

IPlayerPtr Game::GetSecondPlayer() const
{
	return m_player2;
}

void Game::PreviewTable(int historyIndex, bool hideNotifications /* = true */)
{
	m_notificationsDisabled = hideNotifications;

	const auto& movesRepresentation = m_parser->GetGamePreview(historyIndex);
	m_board->Clear();
	m_turn = m_player1;

	for (auto move : movesRepresentation)
	{
		const auto& [firstPos, secondPos, removed] = move;
		const auto& [firstPosRow, firstPosColumn] = firstPos;
		const auto& [secondPosRow, secondPosColumn] = secondPos;

		if (!secondPosRow && !secondPosColumn)
		{
			PlaceColumn(Position(firstPosRow, firstPosColumn));
		}
		else
		{
			removed ? RemoveBridge(Position(firstPosRow, firstPosColumn), Position(secondPosRow, secondPosColumn))
					: MakeBridge  (Position(firstPosRow, firstPosColumn), Position(secondPosRow, secondPosColumn));
		}
	}

	m_notificationsDisabled = false;

}

IPlayerPtr Game::GetTurn() const
{
	return m_turn;
}

IBoardPtr Game::GetBoard() const 
{
	return m_board;
}

IPlayerPtr Game::CheckWinner() const
{
	if (m_turn == m_player1)
	{
		if (m_board->CheckWinner(0))
		{
			return m_player1;
		}
	}
	else
	{
		if (m_board->CheckWinner(1))
		{
			return m_player2;
		}
	}
	return nullptr;
}

void Game::AddObserver(ObserverPtr observer)
{
	m_observers.push_front(observer);
}

void Game::RemoveObserver(ObserverPtr observer)
{
	m_observers.remove_if(
		[observer](ObserverPtr weakObserver) {
			return weakObserver.expired() || weakObserver.lock() == observer.lock();
		});
}

void Game::Restart()
{
	m_board->Clear();
	m_turn = m_player1;
	m_parser->Clear();

	m_player1->SetName(m_settings->GetFirstPlayerName());
	m_player2->SetName(m_settings->GetSecondPlayerName());
	m_player1->IncreaseBridgeNumber(m_settings->GetBridgeLimit());
	m_player2->IncreaseBridgeNumber(m_settings->GetBridgeLimit());
	m_player1->IncreaseColumnNumber(m_settings->GetColumnLimit());
	m_player2->IncreaseColumnNumber(m_settings->GetColumnLimit());

	m_notificationsDisabled = m_firstGameMove = m_gameEnded = false;
	if (m_gamemode == EGamemode::MinedColumns) m_minedGame->AddMines();
	if (m_gamemode == EGamemode::Bulldozer) m_bulldozerGame->DestroyOrMove(m_player1, m_player2);
}

void Game::NotifyPlaceColumn(Position position, IPlayerPtr player) const
{
	if (m_notificationsDisabled) return;
	m_parser->AddColumn(position.ToPair());
	for (auto& observer : m_observers)
	{
		observer.lock()->OnColumnPlaced(position, player);
	}
}

void Game::NotifyMakeBridge(Position firstPos, Position secondPos, IPlayerPtr player) const
{
	if (m_notificationsDisabled) return;
	m_parser->AddBridge(false, firstPos.ToPair(), secondPos.ToPair());
	for (auto& observer : m_observers)
	{
		observer.lock()->OnBridgePlaced(firstPos, secondPos, player);
	}
}

void Game::NotifyRemoveBridge(Position firstPos, Position secondPos, IPlayerPtr player) const
{
	if (m_notificationsDisabled) return;
	m_parser->AddBridge(true, firstPos.ToPair(), secondPos.ToPair());
	for (auto& observer : m_observers)
	{
		observer.lock()->OnBridgeRemoved(firstPos, secondPos, player);
	}
}

void Game::NotifySwapEvent() const
{
	if (m_notificationsDisabled) return;
	for (auto& observer : m_observers)
	{
		observer.lock()->OnSwapRequest();
	}
}

void Game::NotifySwapResponse(bool response) const
{
	if (m_notificationsDisabled) return;
	for (auto& observer : m_observers)
	{
		observer.lock()->OnSwapResponse(response);
	}
}

void Game::NotifyGameEnd(EGameResult result) const
{
	if (m_notificationsDisabled) return;
	for (auto& observer : m_observers)
	{
		observer.lock()->OnGameEnd(result);
	}
}

void Game::ChangeTurn()
{
	if (auto player = dynamic_cast<Player*>(m_turn.get()); player && player->GetDoubleTurn())
	{
		player->SetDoubleTurn(false);
		return;
	}

	m_turn = m_turn == m_player1 ? m_player2 : m_player1;
}

void Game::ComputePathToWin(bool action, const Position& firstPos, const Position& secondPos) const
{
	if (m_turn == m_player1)
	{
		m_board->ComputePathToWin(0, action, firstPos, secondPos);
	}
	else
	{
		m_board->ComputePathToWin(1, action, firstPos, secondPos);
	}
}

parser::STNGameRepresentation Game::GetSTNGameRepresentation() const
{
	parser::BoardRepresentation boardRepresentation{m_boardSize, std::vector<parser::Piece>{m_boardSize, parser::Piece::Empty}};
	for (int row = 0; row < m_boardSize; row++)
	{
		for (int column = 0; column < m_boardSize; column++)
		{
			auto currentColumn = m_board->GetElement(row, column);
			if (!currentColumn) continue;
			boardRepresentation[row][column] = currentColumn->GetPlayer() == m_player1
				? parser::Piece::FirstPlayer
				: parser::Piece::SecondPlayer;
		}
	}

	BridgeVector bridges = m_board->GetBridgesPositions();
	parser::MovesPositions movesRepresentation;
	for (auto bridge : bridges)
	{
		const auto& [firstPos, secondPos] = bridge;
		movesRepresentation.emplace_back(firstPos.ToPair(), secondPos.ToPair());
	}

	return std::make_pair(boardRepresentation, movesRepresentation);
}

void Game::STNGameRepresentationToBoard(const parser::STNGameRepresentation& game)
{
	Restart();
	const auto& [boardRepresentation, moves] = game;
	for (uint16_t row = 0; row < boardRepresentation.size(); row++)
	{
		for (uint16_t column = 0; column < boardRepresentation.size(); column++)
		{
			if (boardRepresentation[row][column] == parser::Piece::Empty) continue;
			PlayerPtr currentPlayer = boardRepresentation[row][column] == parser::Piece::FirstPlayer ? m_player1 : m_player2;
			m_board->PlaceColumn({ row, column }, currentPlayer);
			ChangeTurn();
			if (!m_firstGameMove) m_firstGameMove = true;
			currentPlayer->DecreaseColumnNumber();
		}
	}

	for (auto move : moves)
	{
		const auto& [firstPos, secondPos] = move;
		const auto& [firstPosRow, firstPosColumn] = firstPos;
		const auto& [secondPosRow, secondPosColumn] = secondPos;
		PlayerPtr currentPlayer = std::dynamic_pointer_cast<Player>(m_board->GetElement(firstPosRow, firstPosColumn)->GetPlayer());

		if (currentPlayer) 
		{
			m_board->MakeBridge({ firstPosRow, firstPosColumn }, { secondPosRow, secondPosColumn }, currentPlayer);
			currentPlayer->DecreaseBridgeNumber();
		}
	}
}

bool Game::SaveGame(const std::string_view path, StorageFormat format)
{
	switch (format)
	{
	case StorageFormat::STN:
		return parser::ITwixtParser::SaveSTN(GetSTNGameRepresentation(), path);
	case StorageFormat::PTG:
		return m_parser->SavePTG(path);
	}
	return false;
}

bool Game::LoadGame(const std::string_view path, StorageFormat format)
{
	switch (format)
	{
	case StorageFormat::STN:
	{
		auto representation = parser::ITwixtParser::LoadSTN(path);
		const auto& [board, moves] = representation;
		if (board.empty()) return false;
		STNGameRepresentationToBoard(representation);
		return true;
	}
	case StorageFormat::PTG:
	{
		if (size_t size = m_parser->LoadPTG(path); size)
		{
			PreviewTable(size, false);
			return true;
		}
		break;
	}
	}
	return false;
}

std::pair<BridgeVector, Position> Game::GetHint(int16_t depth, IPlayerPtr player) const
{
	return m_minimax->GetHint(depth, player);
}
