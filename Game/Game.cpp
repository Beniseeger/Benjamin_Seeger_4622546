#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}


Game::~Game()
{

	delete gamefield;
	delete player1;
	delete player2;

	player1 = nullptr;
	player2 = nullptr;
	gamefield = nullptr;
}

void Game::start()
{
	initVariables();

	ConsoleOut::welcomeScreen();

	do {
		action = ConsoleUtils::readInteger();

		if(action < 1 || action > 3)
			ConsoleOut::notaValidNumber();
		else break;

	} while (true);

	initNewGame();
	
	switch (action)
	{
	case PVP: 
		player1 = new HumanPlayer(Spieler1, ZeichenX);
		player2 = new HumanPlayer(Spieler2, ZeichenPlus);
		break;
	case PVB:
		player1 = new HumanPlayer(Spieler1, ZeichenX);
		againstwhichBot();
		break;
	case BVB:
		againstwhichBot();
		action = -1;
		againstwhichBot();
		break;
	default:
		break;
	}

	while (!winner && !draw) {
		gamefield->printGameField();
		Gameloop();
		checkForWinner();
		askForNewGame();
	}
}

void Game::initNewGame()
{
	gamefield->createDefaultGameField();
	gamefield->initializeColumHeights();
}

void Game::initVariables()
{
	//Spieler 1 beginnt
	gamerow = Spieler1;
	winner = false;
	draw = false;
	action = -1;
	selectedColumn = -1;
}

void Game::Gameloop()
{

	if (gamerow == Spieler1) {	//gamerow ist die Variable, die angibt, welcher Spieler an der Reihe ist
		//Spieler 1 ist dran
		ConsoleOut::player1Turn();

		if (player1->insertChipPlayer(player1->getPositionForColumn(gamefield), gamefield)) {
			//Erfolgreiches Einwerfen
			//wechselt die Spieler Reihe: Spieler1 ist dran 
			gamerow = Spieler2;
		}
	}
	else if(gamerow == Spieler2){
		ConsoleOut::player2Turn();
		if (player2->insertChipPlayer(player2->getPositionForColumn(gamefield), gamefield)) {
			gamerow = Spieler1;
		}
	}
}


void Game::checkForWinner()
{
if (checkwin.checkForWin(gamefield)) {
		winner = true;
	}

	//!winner wird hier abgefragt, sodass wenn das Spielfeld voll ist, jemand aber gewonnen hat
	//nicht der Unentschieden Text aufgerufen wird 
	if (checkwin.checkDraw(gamefield) && !winner) {
		draw = true;
	}
}

void Game::askForNewGame()
{
	if (winner) {
		if (gamerow == 2) {
			ConsoleOut::winnerScreen(Spieler1);
		}
		else {
			ConsoleOut::winnerScreen(Spieler2);
		}

		action = ConsoleUtils::readInteger();
	}

	if (draw) {
		ConsoleOut::drawScreen();

		action = ConsoleUtils::readInteger();
	}

	if (winner || draw) {
		if (action == 1) {
			restartGame();
		}
		else {
			ConsoleOut::goodByeScreen();
		}
	}
}

void Game::restartGame()
{

	delete player1;
	delete player2;

	player1 = nullptr;
	player2 = nullptr;

	start();
}

void Game::againstwhichBot()
{
	system("cls");
	if (player1 == NULL) {
		std::cout << "Waehlen Sie Spieler 1:" << std::endl;
		std::cout << "SmartBot ist nicht waehlbar" << std::endl;

		do {
			ConsoleOut::whichEnemyBot();
			action = ConsoleUtils::readInteger();

			//Smart Bot ist hier nicht aufgelistet, da er immer Spieler 2 sein soll
			if (action == RANDBOT)
				player1 = new RandomBot(Spieler1, ZeichenX);
			else if (action == LEFTBOT)
				player1 = new LeftRowBot(Spieler1, ZeichenX);
			else if (action == LOWESTCOLUMNBOT)
				player1 = new LowestColunmBot(Spieler1, ZeichenX);
			else {
				//Keine Gültige Eingabe vielleicht ein zurück Button ? 
				ConsoleOut::notaValidNumber();
			}
		} while (action > 3 || action < 1);
	}
	else {
		std::cout << "Waehlen Sie Spieler 2:" << std::endl;

		do {
			ConsoleOut::whichEnemyBot();
			action = ConsoleUtils::readInteger();

			if (action == RANDBOT)
				player2 = new RandomBot(Spieler2, ZeichenPlus);
			else if (action == LEFTBOT)
				player2 = new LeftRowBot(Spieler2, ZeichenPlus);
			else if (action == LOWESTCOLUMNBOT)
				player2 = new LowestColunmBot(Spieler2, ZeichenPlus);
			else if (action == SMARTBOT)
				player2 = new SmartBot(Spieler2, ZeichenPlus);
			else {
				//Keine Gültige Eingabe vielleicht ein zurück Button ? 
				ConsoleOut::notaValidNumber();
			}
		} while (action > 4 || action < 1);
	}
}

