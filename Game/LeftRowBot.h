#pragma once
#include "Player.h"

class LeftRowBot	: public Player
{
public:
	LeftRowBot(int playerid, int icon);
	~LeftRowBot();
	int getPositionForColumn(BuildGameField *gamefield) override;

private:
	int insertinColumn = 1;
};

