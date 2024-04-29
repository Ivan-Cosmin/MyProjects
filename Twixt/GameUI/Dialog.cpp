#pragma once

#include "Dialog.h"

Dialog::Dialog(QWidget* parent /*= nullptr*/) 
	: QDialog{ parent }
	, m_layout{ new QGridLayout{this } }
	, m_label{new QLabel{this}}
{
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setStyleSheet("background-color: #262522;font-family: Montserrat SemiBold; font-size: 16px; border-radius: 20px;");
}

bool Dialog::ExecuteDialog(std::string result, bool buttons)
{
	m_label->setText(QString::fromStdString(result));
	m_label->setAlignment(Qt::AlignCenter);
	m_layout->addWidget(m_label, 0, 0, 1, 2, Qt::AlignCenter);

	if (buttons)
	{
		Button* acceptButton = new Button{ "Accept" };
		Button* rejectButton = new Button{ "Reject" };

		acceptButton->setObjectName("updateButton");
		acceptButton->SetShadowColor("#466b3a");
		acceptButton->SetShadowYOffset(3);

		rejectButton->setObjectName("discardButton");
		rejectButton->SetShadowColor("#781c1c");
		rejectButton->SetShadowYOffset(3);

		connect(acceptButton, &Button::ButtonClicked, this, [&]() { accept(); });
		connect(rejectButton, &Button::ButtonClicked, this, [&]() { reject(); });

		m_layout->addWidget(acceptButton, 1, 0, Qt::AlignLeft);
		m_layout->addWidget(rejectButton, 1, 1, Qt::AlignRight);
	}

	setLayout(m_layout);
	if (exec() > 0) return true;
	return false;
}
