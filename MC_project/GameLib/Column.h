#pragma once

#include "IColumn.h"

using ColumnPtr = std::shared_ptr<class Column>;

class Column : public IColumn
{
public:
	Column(IPlayerPtr player);

	IPlayerPtr GetPlayer() const noexcept override;

private:
	IPlayerPtr m_player;
};