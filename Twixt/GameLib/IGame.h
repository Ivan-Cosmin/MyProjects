#pragma once

#include "IGameSettings.h"
#include "IGameObserver.h"
#include "Position.h"
#include "IPlayer.h"
#include "IBoard.h"

using IGamePtr = std::shared_ptr<struct IGame>;

enum class StorageFormat
{
	STN,  // standard twixt notation
	PTG,  // portable twixt game
};

struct IGame
{
	static IGamePtr Produce(const IGameSettingsPtr settings);

	virtual void AddObserver(ObserverPtr observer) = 0;
	virtual void RemoveObserver(ObserverPtr observer) = 0;

	virtual IPlayerPtr GetTurn() const = 0;
	virtual IBoardPtr GetBoard() const = 0;
	virtual IPlayerPtr CheckWinner() const = 0;

	virtual IPlayerPtr GetFirstPlayer() const = 0;
	virtual IPlayerPtr GetSecondPlayer() const = 0;

	virtual void PreviewTable(int historyIndex, bool hideNotifications = true) = 0;
	virtual bool PlaceColumn(const Position& position) = 0;
	virtual bool MakeBridge(const Position& firstPos, const Position& secondPos) = 0;
	virtual bool RemoveBridge(const Position& firstPos , const Position& secondPos) = 0;
	virtual std::pair<BridgeVector, Position> GetHint(int16_t depth, IPlayerPtr player) const = 0;

	virtual void SwapResponse(bool response) = 0;

	virtual void Restart() = 0;
	virtual bool SaveGame(const std::string_view path, StorageFormat format) = 0;
	virtual bool LoadGame(const std::string_view path, StorageFormat format) = 0;

	virtual ~IGame() = default;
};

