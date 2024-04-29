#pragma once

#include <cstdint>
#include <utility>

using PositionPair = std::pair<uint16_t, uint16_t>;

class Position
{
public:
	Position() noexcept;
	Position(const uint16_t& row, const uint16_t& column) noexcept;
	Position(const PositionPair& position);
	Position(const Position& other) noexcept;
	Position(Position&& other) noexcept;

	const uint16_t GetRow() const noexcept;
	const uint16_t GetColumn() const noexcept;
	PositionPair ToPair() const;

	bool IsEqual(const uint16_t& row, const uint16_t& column) const;

	bool operator==(const Position& rhs) const;
	bool operator!=(const Position& rhs) const;
	Position& operator=(const Position& rhs);
	Position& operator=(Position&& rhs) noexcept;

public:
	static const Position& EmptyPosition() noexcept;

private:
	uint16_t m_row, m_column;

};

