#pragma once
#include "BuildGameField.h"

class BuildGameField;

class Player
{
public:
	Player(int playerrow, int icon);
	~Player();

	int getPlayerId();
	int getIcon();
	virtual int getPositionForColumn(BuildGameField *gamefield) = 0;
	bool insertChipPlayer(int column, BuildGameField *gamefield);

private:
	const int m_playerid;
	const int m_icon;
};

