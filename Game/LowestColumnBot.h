#pragma once
#include "Player.h"

class LowestColunmBot : public Player
{
public:
	LowestColunmBot(int playerid, int icon);
	~LowestColunmBot();


	int getPositionForColumn(BuildGameField *gamefield) override;

private:
	int getleastChippedColumn(BuildGameField * gamefield);
	
};

