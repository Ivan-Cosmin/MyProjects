#include "gtest/gtest.h"

#include "Game.h"

class PlayerTests : public ::testing::Test{

protected:
	void SetUp() override
	{
		m_player = std::make_shared<Player>("player", EColor::Red, 30, 30);
	}

	void TearDown() override
	{

	}

protected:
	PlayerPtr m_player;

};


TEST_F(PlayerTests, IncreaseBridgeNumber) {
	m_player->IncreaseBridgeNumber(10);
	EXPECT_EQ(m_player->GetBridgeNumber(), 40);
}

TEST_F(PlayerTests, IncreaseColumnNumber) {
	m_player->IncreaseColumnNumber(10);
	EXPECT_EQ(m_player->GetColumnNumber(), 40);
}

TEST_F(PlayerTests, DecreaseBridgeNumber) {
	m_player->DecreaseBridgeNumber(10);
	EXPECT_EQ(m_player->GetBridgeNumber(), 20);
}

TEST_F(PlayerTests, DecreaseColumnNumber) {
	m_player->DecreaseColumnNumber(10);
	EXPECT_EQ(m_player->GetColumnNumber(), 20);
}