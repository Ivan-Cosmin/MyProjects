#pragma once
#include "IColumn.h"
#include "Player.h"

using BulldozerColumnPtr = std::shared_ptr<class BulldozerColumn>;

class BulldozerColumn : public IColumn
{

public:
	BulldozerColumn() noexcept = default;

	IPlayerPtr GetPlayer() const noexcept override;

private:
	static PlayerPtr m_bulldozer;

};