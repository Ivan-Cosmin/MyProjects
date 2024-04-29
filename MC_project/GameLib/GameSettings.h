#pragma once

#include "IGameSettings.h"

using GameSettingsPtr = std::shared_ptr<class GameSettings>;

class GameSettings : public IGameSettings
{
public:
// Make a new instance of GameSettings with singleton
	static GameSettingsPtr ObtainInstance();

// Board settings

	// Getters
	const uint16_t GetTableSize() const noexcept override;
	const uint16_t GetColumnLimit() const noexcept override;
	const uint16_t GetBridgeLimit() const noexcept override;
	const EGamemode GetGamemode() const noexcept override;
	// Setters
	void SetTableSize(uint16_t size) override;
	void SetColumnLimit(uint16_t limit) override;
	void SetBridgeLimit(uint16_t limit) override;
	void SetGamemode(EGamemode gamemode) override;

// Player settings

	// Getters
	const std::string_view GetFirstPlayerName() const noexcept override;
	const EColor GetFirstPlayerColor() const noexcept override;
	const std::string_view GetSecondPlayerName() const noexcept override;
	const EColor GetSecondPlayerColor() const noexcept override;
	// Setters
	void SetFirstPlayerName(std::string_view name) override;
	void SetFirstPlayerColor(EColor color) override;
	void SetSecondPlayerName(std::string_view name) override;
	void SetSecondPlayerColor(EColor color) override;

	GameSettings();
private:
	uint16_t m_tableSize, m_columnLimit, m_bridgeLimit;
	std::string m_firstPlayerName, m_secondPlayerName;
	EColor m_firstPlayerColor, m_secondPlayerColor;
	EGamemode m_gamemode;
	static GameSettingsPtr instance;



};

