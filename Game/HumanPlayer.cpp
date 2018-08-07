#include "stdafx.h"
#include "HumanPlayer.h"


HumanPlayer::HumanPlayer(int playerid, int zeichen)
	: Player(playerid, zeichen)
{
}


HumanPlayer::~HumanPlayer()
{
}

int HumanPlayer::getPositionForColumn(BuildGameField *gamefield)
{
	ConsoleOut::whichColunm();
	selectedColumn = ConsoleUtils::readInteger();
	return selectedColumn;
}

