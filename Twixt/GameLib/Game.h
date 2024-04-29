#pragma once

#include <optional>

#include "IGame.h"
#include "Board.h"
#include "Player.h"
#include "Minimax.h"
#include "MinedGame.h"
#include "BulldozerGame.h"

#include "../TwixtTextParser/ITwixtParser.h"

using GamePtr = std::shared_ptr<class Game>;

class Game : public IGame
{
public:
	Game(const IGameSettingsPtr settings);

	IPlayerPtr GetTurn() const override;
	IBoardPtr GetBoard() const override;
	IPlayerPtr CheckWinner() const override;

	IPlayerPtr GetFirstPlayer() const override;
	IPlayerPtr GetSecondPlayer() const override;

	void PreviewTable(int historyIndex, bool hideNotifications = true) override;
	bool PlaceColumn(const Position& position) override;
	bool MakeBridge(const Position& firstPos, const Position& secondPos) override;
	bool RemoveBridge(const Position& firstPos, const Position& secondPos) override;

	void SwapResponse(bool response) override;
	void SwapPlayers();

	void AddObserver(ObserverPtr observer) override;
	void RemoveObserver(ObserverPtr observer) override;

	void Restart();
	bool SaveGame(const std::string_view path, StorageFormat format) override;
	bool LoadGame(const std::string_view path, StorageFormat format) override;

	std::pair<BridgeVector, Position> GetHint(int16_t depth, IPlayerPtr player) const override;

private:
	void NotifyPlaceColumn(Position position, IPlayerPtr player) const;
	void NotifyMakeBridge(Position firstPos, Position secondPos, IPlayerPtr player) const;
	void NotifyRemoveBridge(Position firstPos, Position secondPos, IPlayerPtr player) const;
	void NotifySwapEvent() const;
	void NotifySwapResponse(bool response) const;
	void NotifyGameEnd(EGameResult result) const;

	void ChangeTurn();
	void ComputePathToWin(bool action, const Position& firstPos, const Position& secondPos) const; // action = 0 - make, 1 - remove
	parser::STNGameRepresentation GetSTNGameRepresentation() const;
	void STNGameRepresentationToBoard(const parser::STNGameRepresentation& game);

private:
	BoardPtr m_board;
	uint16_t m_boardSize;
	PlayerPtr m_player1, m_player2;
	IPlayerPtr m_turn;
	Minimax* m_minimax;
	MinedGame* m_minedGame;
	BulldozerGame* m_bulldozerGame;
	EGamemode m_gamemode;
	parser::TwixtParserPtr m_parser;
	const IGameSettingsPtr m_settings;

	bool m_notificationsDisabled, m_firstGameMove, m_gameEnded;

	ObserverList m_observers;

};


