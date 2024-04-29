#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "IPlayer.h"

class PlayerBar : public QWidget
{
public:
	PlayerBar(const IPlayerPtr player, bool turn, QWidget* parent = nullptr);
	void Update(bool playerTurn);

private:
	const IPlayerPtr m_player;
	QGridLayout* m_layout;
	QLabel* m_profilePicture, * m_playerName;
	QLabel* m_bridgePicture, * m_columnPicture;
	QLabel* m_columnsRemaining, * m_bridgesRemaining;

};