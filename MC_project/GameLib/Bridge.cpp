#include "Bridge.h"

Bridge::Bridge(IColumnPtr firstColumn, IColumnPtr secondColumn)
	: m_firstColumn{firstColumn}
	, m_secondColumn{secondColumn}
{
	// Empty
}

 IColumnPtr Bridge::GetFirstColumn() const noexcept
{
	return m_firstColumn;
}

 IColumnPtr Bridge::GetSecondColumn() const noexcept
{
	return m_secondColumn;
}






