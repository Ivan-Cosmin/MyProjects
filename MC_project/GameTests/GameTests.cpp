#include "gtest/gtest.h"

#include "Game.h"

class GameTests : public ::testing::Test {

protected:
	void SetUp() override
	{
		m_settings = IGameSettings::GetInstance();
		m_game = std::make_shared<Game>(m_settings);
	}

	void TearDown() override
	{

	}

protected:
	IGameSettingsPtr m_settings;
	GamePtr m_game;

};

// Test fixture for testing specific methods
TEST_F(GameTests, GetTurnReturnsValidPlayer) {

	IPlayerPtr turn = m_game->GetTurn();
	EXPECT_NE(turn, nullptr);
	// Add more assertions or validations based on your requirements
}

TEST_F(GameTests, SwapTest) {

	std::string firstPlayerName = m_game->GetFirstPlayer()->GetName().data();
	std::string secondPlayerName = m_game->GetSecondPlayer()->GetName().data();
	m_game->SwapPlayers();
	std::string newFirstPlayer = m_game->GetFirstPlayer()->GetName().data();
	std::string newSecondPlayer = m_game->GetSecondPlayer()->GetName().data();

	EXPECT_EQ(firstPlayerName, newSecondPlayer);
	EXPECT_EQ(secondPlayerName, newFirstPlayer);
}

TEST_F(GameTests, FirstPlayerBase1Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(0, 1)), true);
		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(0, 1));

		// expects that a column was inserted at Position(0, 1)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player1
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetFirstPlayer());

	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(0, 1)), false);


	}

}

TEST_F(GameTests, FirstPlayerBase2Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(23, 1)), true);
		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(23, 1));

		// expects that a column was inserted at Position(23, 1)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player1
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetFirstPlayer());

	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(23, 1)), false);


	}

}
TEST_F(GameTests, SecondPlayerBase1Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 0)), false);


	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 0)), true);

		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(1, 0));

		// expects that a column was inserted at Position(1, 0)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetSecondPlayer());
	}

}

TEST_F(GameTests, SecondPlayerBase2Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 23)), false);


	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 23)), true);

		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(1, 23));

		// expects that a column was inserted at Position(1, 23)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player2
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetSecondPlayer());
	}

}

TEST_F(GameTests, GetDefaultColorPlayer1Test) {
	// Perform the action

	EColor resultColor = m_game->GetFirstPlayer()->GetColor();

	// Verify the result
	EXPECT_EQ(resultColor, EColor::Blue);
}

TEST_F(GameTests, GetDefaultColorPlayer2Test) {
	// Perform the action

	EColor resultColor = m_game->GetSecondPlayer()->GetColor();

	// Verify the result
	EXPECT_EQ(resultColor, EColor::Red);
}

TEST_F(GameTests, GetDefaultNamePlayer1Test) {
	// Perform the action
	std::string_view resultName = m_game->GetFirstPlayer()->GetName();

	// Verify the result
	EXPECT_EQ(resultName, "Player1");
}

TEST_F(GameTests, GetDefaultNamePlayer2Test) {
	// Perform the action
	std::string_view resultName = m_game->GetSecondPlayer()->GetName();

	// Verify the result
	EXPECT_EQ(resultName, "Player2");
}

TEST_F(GameTests, SetColorTest) {
	// Perform the action
	m_game->GetFirstPlayer()->SetColor(EColor::Blue);
	m_game->GetSecondPlayer()->SetColor(EColor::Red);
	// Verify the result
	EXPECT_EQ(m_game->GetFirstPlayer()->GetColor(), EColor::Blue);
	EXPECT_EQ(m_game->GetSecondPlayer()->GetColor(), EColor::Red);
}

TEST_F(GameTests, SetNameTest) {
	// Perform the action
	m_game->GetFirstPlayer()->SetName("NewPlayer1Name");
	m_game->GetSecondPlayer()->SetName("NewPlayer2Name");

	// Verify the result
	EXPECT_EQ(m_game->GetFirstPlayer()->GetName(), "NewPlayer1Name");
	EXPECT_EQ(m_game->GetSecondPlayer()->GetName(), "NewPlayer2Name");
}

TEST_F(GameTests, FirstPlayerWon) {
	std::vector<Position> positions;

	for (int index = 0; index < 12; index++)
	{
		m_game->PlaceColumn(Position(index * 2, index + 1));
		positions.push_back(Position(index * 2, index + 1));
		m_game->PlaceColumn(Position(index + 1, 22));
	}
	m_game->PlaceColumn(Position(23, 14));
	positions.push_back(Position(23, 14));

	m_game->PlaceColumn(Position(20, 17));

	for (int index = 1; index < positions.size(); index++)
	{
		m_game->MakeBridge(positions[index], positions[index - 1]);
	}

	auto winner = m_game->CheckWinner();
	EXPECT_EQ(winner, m_game->GetFirstPlayer());
}

TEST_F(GameTests, GameEndsTie) {

	std::vector<Position> positions;

	for (int index = 1; index < 200; index++)
	{
		m_game->PlaceColumn(Position(index / 24, index % 24));
		m_game->PlaceColumn(Position(index / 24 + 1, (index % 23) + 1));
	}

	auto winner = m_game->CheckWinner();
	EXPECT_NE(winner, m_game->GetFirstPlayer());
	EXPECT_NE(winner, m_game->GetSecondPlayer());

	// can't make anymore moves becouse game is ended
	EXPECT_EQ(m_game->PlaceColumn(Position(20, 20)), false);
}