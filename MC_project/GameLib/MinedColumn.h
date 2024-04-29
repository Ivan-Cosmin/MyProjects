#pragma once
#include "IColumn.h"
#include "Player.h"

using MinedColumnPtr = std::shared_ptr<class MinedColumn>;

class MinedColumn : public IColumn
{
public:
	MinedColumn() noexcept = default;

	IPlayerPtr GetPlayer() const noexcept override;
private:
	static PlayerPtr mineSpot;
};

