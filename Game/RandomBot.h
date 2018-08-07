#pragma once
#include "Player.h"
#include <stdio.h>
#include <stdint.h>

class RandomBot	: public Player
{
public:
	RandomBot(int playerid, int icon);
	~RandomBot();

	int getPositionForColumn(BuildGameField *gamefield) override;
};

