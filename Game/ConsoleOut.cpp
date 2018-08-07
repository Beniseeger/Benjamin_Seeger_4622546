#include "stdafx.h"
#include "ConsoleOut.h"
#include <iostream>

//Darf ich ein Namespace in einem Namespace verwenden ? 
using namespace std;

void ConsoleOut::cantInsertColumn()
{
	cout << "In dieser Spalte kann kein Chip mehr gesetzt werden!" << endl;
}

void ConsoleOut::welcomeScreen()
{
	system("CLS");
	cout << " ----------------------------------------Willkommen zu diesem 4-Gewinnt Spiel!---------------------------------------" << endl;
	cout << "Spieler 1 hat das Zeichen: |X| und Spieler 2: |+|" << endl;
	cout << "Waehlen Sie zwischen: -- 1->Player vs. Player / 2->Player vs. Bot / 3->Bot vs. Bot --" << endl;
}

void ConsoleOut::whichColunm()
{
	cout << "In welche Spalte wollen Sie ihren Chip setzen ?" << endl;
}

void ConsoleOut::notaValidNumber()
{
	cout << "Das ist keine gueltige Zahl. Bitte geben Sie eine gueltige ein" << endl;
}

void ConsoleOut::winnerScreen(int winner)
{
	cout << "------------------------------------------------" << endl;
	cout << "Herzlichen Glueckwunsch!" << endl;
	cout << "Spieler " << winner  << " hat gewonnen!!!" << endl;
	cout << "Wollen Sie nochmal Spielen ? (1->JA / 2->NEIN)" << endl;
	cout << "------------------------------------------------" << endl;
}

void ConsoleOut::goodByeScreen()
{
	cout << "Auf Wiedersehen!" << endl;
}

void ConsoleOut::whichEnemyBot()
{
	cout << "Welcher Bot soll antreten?" << endl << "(1->Random Bot | 2->Linkseinwurf Bot | 3->Bot in niedrigste Spalte | 4->Schlauer Bot)" << endl;
}

void ConsoleOut::player1Turn()
{
	cout << "Spieler 1 ist an der Reihe!" << endl;
}

void ConsoleOut::player2Turn()
{
	cout << "Spieler 2 ist an der Reihe!" << endl;
}

void ConsoleOut::drawScreen()
{
	cout << "------------------------------------------------" << endl;
	cout << "Unentschieden !" << endl;
	cout << "------------------------------------------------" << endl;
}
