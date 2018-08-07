#pragma once
//class BuildGameField;
#include "ConsoleOut.h"
#include "ConsoleUtils.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "BuildGameField.h"
#include "CheckForWin.h"
#include "RandomBot.h"
#include "LeftRowBot.h"
#include "LowestColumnBot.h"
#include "SmartBot.h"

#define Spieler1 1
#define ZeichenX 1
#define Spieler2 2
#define ZeichenPlus 2

class Game
{
public:
	Game();
	~Game();

	void start();
	void Gameloop();
	void initNewGame();
	void initVariables();
	void checkForWinner();
	bool winner;
	bool draw;
	int gamerow;
	Player *player1;
	Player *player2;


private:
	enum WhichGameTyp { PVP = 1 /*Player vs. Player*/, PVB /*Player vs. Bot*/, BVB /*Bot vs. Bot*/ };
	enum EnemyBot { RANDBOT = 1, LEFTBOT, LOWESTCOLUMNBOT, SMARTBOT };

	BuildGameField * gamefield = new BuildGameField();

	int action;
	void askForNewGame();

	CheckForWin checkwin;

	void restartGame();
	void againstwhichBot();

	int selectedColumn;


};

