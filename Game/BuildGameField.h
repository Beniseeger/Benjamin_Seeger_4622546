#pragma once
#include <array>
#include <iostream>
#include <stdlib.h>
#include "ConsoleOut.h"
#define FAIL -1

class BuildGameField
{
public:
	BuildGameField();
	~BuildGameField();

	void createDefaultGameField();
	void printGameField();
	void initializeColumHeights();
	bool canInsert(int column);
	void setChipForPlayer(int column, int playericon);
	int getvalueAtGamefieldpos(int width, int height);
	int getColumnHeights(int inPosition);
	
	int getGamefieldHeight();
	int getGamefieldWidth();



private:
	std::array<int, 7> columnHeight;

	const int height = 6;
	const int width = 7;

	std::array<std::array<int, 6>, 7> GameField;		
	//Zugreifen mit:	
	/*GameField.at(2 (1*)).at(2(2*));	1* ist die Breite und 2* ist die Höhe		
	*/

};

