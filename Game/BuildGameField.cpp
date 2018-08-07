#include "stdafx.h"
#include "BuildGameField.h"

BuildGameField::BuildGameField()
{
}


BuildGameField::~BuildGameField()
{
}

void BuildGameField::createDefaultGameField()
{
	for (int h = 0; h < height; h++)
	{

		for (int w = 0; w < width; w++)
		{
			GameField.at(w).at(h) = 0;
		}
	}
}

void BuildGameField::printGameField()
{
	system("CLS");
	std::cout << "-----------------------------" << std::endl;
	std::cout << "|1||2||3||4||5||6||7|" << std::endl;

	for (int h = 0; h < height; h++)
	{

		for (int w = 0; w < width; w++)
		{

			if (GameField.at(w).at(h) == 1) {
				std::cout << "|" << "X" << "|";
			}
			else if (GameField.at(w).at(h) == 2) {
				std::cout << "|" << "+" << "|";
			}
			else {
				std::cout << "|" << " |";
			}
		}

		std::cout << std::endl;
	}
}

void BuildGameField::setChipForPlayer(int column, int playericon)
{
	GameField.at(column-1).at(columnHeight.at(column-1)) = playericon;
	columnHeight.at(column-1)--;
	printGameField();
}

int BuildGameField::getvalueAtGamefieldpos(int width, int height)
{
	if (height < 0 || height > 5 || width > 6 || width < 0) {
		return FAIL;
	}

	return GameField.at(width).at(height);
}

int BuildGameField::getColumnHeights(int inPosition)
{
	if (inPosition < 0 || inPosition > 7) {
		return FAIL;
	}
	//Eine Reihe ist voll, wenn get ColumHeight bei -1 ist
	return columnHeight.at(inPosition);
}

int BuildGameField::getGamefieldHeight()
{
	return height;
}

int BuildGameField::getGamefieldWidth()
{
	return width;
}


void BuildGameField::initializeColumHeights()
{
	for (int i = 0; i < width; i++) {
		//Die Spaltenhöhe wird auf 5 gesetzt, um von unten an die Spalten aufzufüllen
		columnHeight.at(i) = 5;
	}
}

bool BuildGameField::canInsert(int column)
{
	if (column <= width && column > 0) {

		if (columnHeight.at(column-1) >= 0) {
			return true;
		}

	}
	return false;
}

