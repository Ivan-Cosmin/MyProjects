#pragma once

#include "IColumn.h"
#include "Position.h"

#include <vector>
#include <tuple>

using BridgePositions = std::pair<Position, Position>;
using BridgeVector = std::vector<BridgePositions>;
using IBoardPtr = std::shared_ptr<struct IBoard>;

struct IBoard
{
	virtual const uint16_t GetSize() const = 0;

	virtual const IColumnPtr GetElement(const Position& pos) const = 0;
	virtual const IColumnPtr GetElement(const uint16_t& row, const uint16_t& column) const = 0;
	virtual const BridgeVector GetBridgesPositions() const = 0;
	virtual bool BridgeExists(const Position& firstPos, const Position& secondPos) const = 0;

	virtual const IColumnPtr operator[](Position pos) const = 0;

	virtual ~IBoard() = default;
};