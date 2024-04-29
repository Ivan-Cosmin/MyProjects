#pragma once

#include "Position.h"
#include "IPlayer.h"

#include <memory>
#include <forward_list>

using ObserverPtr = std::weak_ptr<struct IGameObserver>;
using ObserverList = std::forward_list<ObserverPtr>;

enum class EGameResult
{
	FirstPlayerWon,
	SecondPlayerWon,
	Tie,
};

struct IGameObserver
{
	virtual void OnColumnPlaced(Position& position, IPlayerPtr player) = 0;
	virtual void OnBridgePlaced(Position& firstPos, Position& secondPos, IPlayerPtr player) = 0;
	virtual void OnBridgeRemoved(Position& firstPos, Position& secondPos, IPlayerPtr player) = 0;

	virtual void OnSwapRequest() = 0;
	virtual void OnSwapResponse(bool response) = 0;

	virtual void OnGameEnd(EGameResult result) = 0;

	virtual ~IGameObserver() = default;
};
