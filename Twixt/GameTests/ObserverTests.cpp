
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IGameObserver.h"
#include "Game.h"

using ::testing::_;

class MockObserver : public IGameObserver
{
public:
	MOCK_METHOD(void, OnColumnPlaced, (Position& position, IPlayerPtr player), (override));
	MOCK_METHOD(void, OnBridgePlaced, (Position& firstPos, Position& secondPos, IPlayerPtr player), (override));
	MOCK_METHOD(void, OnBridgeRemoved, (Position& firstPos, Position& secondPos, IPlayerPtr player), (override));
	MOCK_METHOD(void, OnSwapRequest, (), (override));
	MOCK_METHOD(void, OnSwapResponse, (bool response), (override));
	MOCK_METHOD(void, OnGameEnd, (EGameResult result), (override));
};

class GameMockTests : public ::testing::Test
{
protected:
	void SetUp()
	{
		m_settings = IGameSettings::GetInstance();
		m_game = std::make_shared<Game>(m_settings);
		m_mock = std::make_shared<MockObserver>();
		m_game->AddObserver(m_mock);
	}

protected:
	std::shared_ptr<MockObserver> m_mock;
	GamePtr m_game;
	IGameSettingsPtr m_settings;
};

TEST_F(GameMockTests, NotifyColumnPlaced) 
{
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, _)).Times(2);
	EXPECT_CALL(*m_mock, OnSwapRequest()).Times(1);

	m_game->PlaceColumn(Position(0, 5));
	m_game->PlaceColumn(Position(3, 5));

}

TEST_F(GameMockTests, NotifyBridgePlaced)
{
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, m_game->GetFirstPlayer())).Times(2);
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, m_game->GetSecondPlayer())).Times(2);
	EXPECT_CALL(*m_mock, OnBridgePlaced(_, _, _)).Times(1);
	EXPECT_CALL(*m_mock, OnSwapRequest()).Times(1);

	m_game->PlaceColumn(Position(0, 5));
	m_game->PlaceColumn(Position(3, 5));
	m_game->PlaceColumn(Position(1, 7));
	m_game->PlaceColumn(Position(1, 1));

	m_game->MakeBridge(Position(0, 5), Position(1, 7));
}

TEST_F(GameMockTests, NotifyBridgeRemoved)
{
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, _)).Times(4);
	EXPECT_CALL(*m_mock, OnBridgePlaced(_, _, _)).Times(1);
	EXPECT_CALL(*m_mock, OnBridgeRemoved(_, _, _)).Times(1);
	EXPECT_CALL(*m_mock, OnSwapRequest()).Times(1);

	m_game->PlaceColumn(Position(0, 2));
	m_game->PlaceColumn(Position(3, 3));
	m_game->PlaceColumn(Position(1, 4));
	m_game->PlaceColumn(Position(9, 9));

	m_game->MakeBridge(Position(0, 2), Position(1, 4));
	m_game->RemoveBridge(Position(0, 2), Position(1, 4));
}

TEST_F(GameMockTests, NotifySwapResponseAccept)
{
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, _)).Times(2);
	EXPECT_CALL(*m_mock, OnSwapRequest()).Times(1);
	EXPECT_CALL(*m_mock, OnSwapResponse(true)).Times(1);

	m_game->PlaceColumn(Position(0, 5));
	m_game->SwapResponse(true);
	m_game->PlaceColumn(Position(3, 5));

}

TEST_F(GameMockTests, NotifySwapResponseDeny)
{
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, _)).Times(2);
	EXPECT_CALL(*m_mock, OnSwapRequest()).Times(1);
	EXPECT_CALL(*m_mock, OnSwapResponse(false)).Times(1);

	m_game->PlaceColumn(Position(3, 5));
	m_game->SwapResponse(false);
	m_game->PlaceColumn(Position(1, 2));

}

TEST_F(GameMockTests, NotifyGameEndFirstWin)
{
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, _)).Times(26);
	EXPECT_CALL(*m_mock, OnSwapRequest()).Times(1);
	EXPECT_CALL(*m_mock, OnBridgePlaced(_, _, _)).Times(12);
	EXPECT_CALL(*m_mock, OnGameEnd(EGameResult::FirstPlayerWon)).Times(1);

	std::vector<Position> positions;

	for (int index = 0; index < 12; index++)
	{
		m_game->PlaceColumn(Position(index*2, index+1));
		positions.push_back(Position(index * 2, index + 1));
		m_game->PlaceColumn(Position(index+1, 22));
	}
	m_game->PlaceColumn(Position(23, 14));
	positions.push_back(Position(23, 14));

	m_game->PlaceColumn(Position(20, 17));

	for (int index = 1; index < positions.size(); index++)
	{
		m_game->MakeBridge(positions[index], positions[index - 1]);
	}

}

TEST_F(GameMockTests, NotifyGameEndTie)
{
	EXPECT_CALL(*m_mock, OnColumnPlaced(_, _)).Times(100);
	EXPECT_CALL(*m_mock, OnSwapRequest()).Times(1);
	EXPECT_CALL(*m_mock, OnGameEnd(EGameResult::Tie)).Times(1);

	std::vector<Position> positions;

	for (int index = 1; index < 200; index++)
	{
		m_game->PlaceColumn(Position(index/24, index%24));
		m_game->PlaceColumn(Position(index/24+1, (index%23)+1));
	}

}


