
#include <QPainter>

#include "PlayerBar.h"
#include "ColorUtils.h"
#include "Player.h"

PlayerBar::PlayerBar(const IPlayerPtr player, bool turn, QWidget* parent) 
	: QWidget{parent}
	, m_player{player}
	, m_layout{new QGridLayout{this}}
	, m_profilePicture{new QLabel{this}}
	, m_playerName{new QLabel{this}}
	, m_bridgePicture{new QLabel{this}}
	, m_columnPicture{new QLabel{this}}
	, m_bridgesRemaining{new QLabel{"0", this}}
	, m_columnsRemaining{new QLabel{"0", this}}
{
	setFixedHeight(70);
	setFixedWidth(250);
	m_profilePicture->setFixedSize(60, 60);
	m_profilePicture->setObjectName("profilePicture");
	m_playerName->setObjectName("playerName");
	m_columnPicture->setFixedSize(30, 30);
	m_bridgePicture->setFixedSize(30, 30);
	m_bridgesRemaining->setObjectName("playerName");
	m_columnsRemaining->setObjectName("playerName");
	m_bridgesRemaining->setAlignment(Qt::AlignCenter);
	m_columnsRemaining->setAlignment(Qt::AlignCenter);
	

	QPixmap columnPicture(":/GameUI/images/column.png");
	QPixmap bridgePicture(":/GameUI/images/bridge.png");
	ColorUtils::FillPixmapBackground(columnPicture, m_player->GetColor());
	ColorUtils::FillPixmapBackground(bridgePicture, m_player->GetColor());
	m_bridgePicture->setPixmap(bridgePicture);
	m_columnPicture->setPixmap(columnPicture);

	Update(turn);

	m_layout->addWidget(m_profilePicture, 0, 0, 2, 1);
	m_layout->addWidget(m_playerName, 0, 1, 1, 4);

	m_layout->addWidget(m_columnPicture, 1, 1, Qt::AlignCenter);
	m_layout->addWidget(m_columnsRemaining, 1, 2, Qt::AlignCenter);
	m_layout->addWidget(m_bridgePicture, 1, 3, Qt::AlignCenter);
	m_layout->addWidget(m_bridgesRemaining, 1, 4, Qt::AlignCenter);

	setLayout(m_layout);
}

void PlayerBar::Update(bool playerTurn)
{
	QPixmap profilePicture(":/GameUI/images/profile.png");
	ColorUtils::FillPixmapBackground(profilePicture, m_player->GetColor());
	m_profilePicture->setPixmap(profilePicture);
	m_playerName->setText(QString(m_player->GetName().data()) + (playerTurn ? " (turn)" : ""));

	PlayerPtr player = std::dynamic_pointer_cast<Player>(m_player);
	if (player)
	{
		m_bridgesRemaining->setText(QString::number(player->GetBridgeNumber()));
		m_columnsRemaining->setText(QString::number(player->GetColumnNumber()));
	}

	setLayout(m_layout);
}


