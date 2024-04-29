#include "Position.h"


Position::Position(const uint16_t& row, const uint16_t& column) noexcept
	: m_row{row}
	, m_column{column}
{
	// Empty
}

Position::Position(const Position& rhs) noexcept
	: m_row{rhs.m_row}
	, m_column{rhs.m_column}
{
	// Empty
}

Position::Position(Position&& rhs) noexcept
	: m_row(std::move(rhs.m_row)), m_column(std::move(rhs.m_column))
{
	// Empty
}


Position::Position() noexcept
	: Position{ EmptyPosition() }
{
	// Empty
}

Position::Position(const PositionPair& position)
	: m_row(position.first)
	, m_column(position.second)
{
	// Empty
}

const uint16_t Position::GetRow() const noexcept
{
	return m_row;
}

const uint16_t Position::GetColumn() const noexcept
{
	return m_column;
}

PositionPair Position::ToPair() const
{
	return std::move(std::make_pair(m_row, m_column));
}

bool Position::IsEqual(const uint16_t& row, const uint16_t& column) const
{
	return row == m_row && column == m_column;
}

bool Position::operator==(const Position& rhs) const
{
	return IsEqual(rhs.m_row,rhs.m_column);
}

bool Position::operator!=(const Position& rhs) const
{
	return !IsEqual(rhs.m_row, rhs.m_column);
}

Position& Position::operator=(const Position& rhs)
{
	if (this != &rhs)
	{
		m_row = rhs.m_row;
		m_column = rhs.m_column;
	}
	return *this;
}

Position& Position::operator=(Position&& rhs) noexcept {
	if (this != &rhs) {
		m_row = std::move(rhs.m_row);
		m_column = std::move(rhs.m_column);
	}
	return *this;
}

const Position& Position::EmptyPosition() noexcept
{
	static const Position& position{UINT16_MAX, UINT16_MAX};
	return position;
}