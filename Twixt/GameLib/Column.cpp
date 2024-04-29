#include "Column.h"

Column::Column(IPlayerPtr player)
	:m_player{ player }
{
	// Empty
}

IPlayerPtr Column::GetPlayer() const noexcept
{
	return m_player;
}
