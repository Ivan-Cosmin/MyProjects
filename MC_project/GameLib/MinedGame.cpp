#include "MinedGame.h"

MinedGame::MinedGame(BoardPtr board)
	:m_board{board}
{
	// Empty
}

void MinedGame::AddMines()
{
	uint16_t numberMines{ (uint16_t)((5.0 / 100.0) * (m_board->GetSize() * m_board->GetSize())) };
	while (numberMines)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(1, m_board->GetSize() - 2);

		uint16_t row{ (uint16_t)distr(eng) }, column{ (uint16_t)distr(eng) };
		Position pos{ row,column };

		PlaceMine(pos);
		--numberMines;
	}
}

void MinedGame::DestroyArea(const Position& position, PlayerPtr firstPlayer, PlayerPtr secondPlayer)
{
	uint16_t rowPosition{ position.GetRow() }, columnPosition{ position.GetColumn() };
	
	for (uint16_t row{ (uint16_t)(rowPosition - 1) }; row <= rowPosition + 1; ++row)
	{
		for (uint16_t column{ (uint16_t)(columnPosition - 1) }; column <= columnPosition + 1; ++column)
		{
			if (auto player = m_board->GetElement(row, column); player)
			{
				PlayerPtr playerUsed = player->GetPlayer() == firstPlayer ? firstPlayer : secondPlayer;
				uint16_t numberOfBridgesRemoved{ m_board->RemoveColumn({ row,column }) };

				playerUsed->IncreaseBridgeNumber(numberOfBridgesRemoved);
				playerUsed->IncreaseColumnNumber();
			}
		}
	}
}

void MinedGame::PlaceMine(const Position& position)
{
	m_board->PlaceColumn(position, std::make_shared<MinedColumn>());
}