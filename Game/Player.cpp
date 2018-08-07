#include "stdafx.h"
#include "Player.h"
#include "BuildGameField.h"

Player::Player(int playerid, int icon) : m_playerid(playerid), m_icon(icon)
{
}


Player::~Player()
{
}

int Player::getPlayerId()
{
	return m_playerid;
}

int Player::getIcon()
{
	return m_icon;
}

bool Player::insertChipPlayer(int column, BuildGameField *gamefield)
{
	if (gamefield->canInsert(column)) {
			gamefield->setChipForPlayer(column, getIcon());			
			return true;
	}
	else {
		ConsoleOut::cantInsertColumn();
	}

	return false;
}



