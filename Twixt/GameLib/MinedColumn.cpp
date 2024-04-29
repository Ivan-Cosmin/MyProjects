#include "MinedColumn.h"

PlayerPtr MinedColumn::mineSpot{ std::make_shared<Player>("", EColor::NoColor, 0, 0)};

IPlayerPtr MinedColumn::GetPlayer() const noexcept
{
    return mineSpot;
}
