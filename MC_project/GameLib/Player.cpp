#include "Player.h"

Player::Player(const std::string_view& name, const EColor& color,
			   const uint16_t& BridgeCounter,const uint16_t& ColumnCounter)
	: m_color{color}
	, m_name{name}
	, m_doubleTurn{false}
	, m_BridgeCounter{BridgeCounter}
	, m_ColumnCounter{ColumnCounter}
{
	// Empty
}

EColor Player::GetColor() const noexcept
{
	return m_color;
}

std::string_view Player::GetName() const noexcept
{
	return m_name;
}

bool Player::GetDoubleTurn() const
{
	return m_doubleTurn;
}

bool Player::HasBridgesToAdd() const
{
	return m_BridgeCounter > 0;
}

bool Player::HasColumnsToAdd() const
{
	return m_ColumnCounter > 0;
}

const uint16_t& Player::GetBridgeNumber() const noexcept
{
	return m_BridgeCounter;
}

const uint16_t& Player::GetColumnNumber() const noexcept
{
	return m_ColumnCounter;
}

void Player::SetColor(EColor color)
{
	m_color = color;
}

void Player::SetName(std::string_view name)
{
	m_name = name;
}

void Player::SetDoubleTurn(bool hasDoubleTurn)
{
	m_doubleTurn = hasDoubleTurn;
}

void Player::IncreaseBridgeNumber(const uint16_t& number)
{
	if (number == 50) m_BridgeCounter = 50;
	if(m_BridgeCounter + number <= 50) m_BridgeCounter += number;
}

void Player::DecreaseBridgeNumber(const uint16_t& number)
{
	if (m_BridgeCounter - number >= 0) m_BridgeCounter -= number;
}

void Player::IncreaseColumnNumber(const uint16_t& number)
{
	if (number == 50) m_ColumnCounter = 50;
	if (m_ColumnCounter + number <= 50) m_ColumnCounter += number;
}

void Player::DecreaseColumnNumber(const uint16_t& number)
{
	if (m_ColumnCounter - number >= 0) m_ColumnCounter -= number;
}
