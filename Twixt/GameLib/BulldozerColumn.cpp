#include "BulldozerColumn.h"

PlayerPtr BulldozerColumn::m_bulldozer{ std::make_shared<Player>("Bulldozer", EColor::Yellow, 0, 0) };

IPlayerPtr BulldozerColumn::GetPlayer() const noexcept
{
    return m_bulldozer;
}
