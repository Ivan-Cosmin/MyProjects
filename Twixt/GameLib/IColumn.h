#pragma once

#include "IPlayer.h"

using IColumnPtr = std::shared_ptr<struct IColumn>;

struct IColumn
{
	virtual IPlayerPtr GetPlayer() const noexcept = 0;

	virtual ~IColumn() = default;
};