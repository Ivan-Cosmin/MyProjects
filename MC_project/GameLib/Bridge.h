#pragma once

#include "IColumn.h"

using BridgePtr = std::shared_ptr<class Bridge>;

class Bridge
{
public:
	Bridge(IColumnPtr firstColumn, IColumnPtr secondColumn);

    IColumnPtr GetFirstColumn() const noexcept;
	IColumnPtr GetSecondColumn() const noexcept;

private:
	IColumnPtr m_firstColumn, m_secondColumn;
};