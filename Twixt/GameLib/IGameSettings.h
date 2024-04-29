#pragma once

#include <memory>

#include "IPlayer.h"

enum class EGamemode { Standard, MinedColumns, Bulldozer };

using IGameSettingsPtr = std::shared_ptr<struct IGameSettings>;

struct IGameSettings
{

// Make a new instance of GameSettings with singleton
	static IGameSettingsPtr GetInstance();

// Board settings

	// Getters
	virtual const uint16_t GetTableSize() const noexcept = 0;
	virtual const uint16_t GetColumnLimit() const noexcept = 0;
	virtual const uint16_t GetBridgeLimit() const noexcept = 0;
	virtual const EGamemode GetGamemode() const noexcept = 0;
	// Setters
	virtual void SetTableSize(uint16_t size) = 0;
	virtual void SetColumnLimit(uint16_t limit) = 0;
	virtual void SetBridgeLimit(uint16_t limit) = 0;
	virtual void SetGamemode(EGamemode gamemode) = 0;

// Player settings

	// Getters
	virtual const std::string_view GetFirstPlayerName() const noexcept = 0;
	virtual const EColor GetFirstPlayerColor() const noexcept = 0;
	virtual const std::string_view GetSecondPlayerName() const noexcept = 0;
	virtual const EColor GetSecondPlayerColor() const noexcept = 0;
	// Setters
	virtual void SetFirstPlayerName(std::string_view name) = 0;
	virtual void SetFirstPlayerColor(EColor color) = 0;
	virtual void SetSecondPlayerName(std::string_view name) = 0;
	virtual void SetSecondPlayerColor(EColor color) = 0;

	virtual ~IGameSettings() = default;

// Constants

	static const size_t defaultTableSize;
	static const size_t defaultColumnLimit;
	static const size_t defaultBridgeLimit;
	static const std::string defaultFirstPlayerName;
	static const EColor defaultFirstPlayerColor;
	static const std::string defaultSecondPlayerName;
	static const EColor defaultSecondPlayerColor;
	static const EGamemode defaultGamemode;

};

