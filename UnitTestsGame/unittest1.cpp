#include "stdafx.h"
#include <CppUnitTest.h>
#include "..\Game\BuildGameField.h"
#include "..\Game\Player.h"
#include "..\Game\Game.h"
#include "..\Game\CheckForWin.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGame
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(InsertNegativeNumber)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();
			gamefield->initializeColumHeights();
			Assert::IsFalse(gamefield->canInsert(-2));
		}

		TEST_METHOD(InsertHighNumber)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();
			gamefield->initializeColumHeights();
			Assert::IsFalse(gamefield->canInsert(2000));
		}

		TEST_METHOD(GetValueForNegativeNumber)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();
			gamefield->initializeColumHeights();
			Assert::AreEqual(gamefield->getvalueAtGamefieldpos(-2, -6), -1);
		}

		TEST_METHOD(GetValueForHighNumber)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();
			gamefield->initializeColumHeights();
			Assert::AreEqual(gamefield->getvalueAtGamefieldpos(-2, 1000), -1);
		}

		TEST_METHOD(CheckForDraw)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();
			CheckForWin checkwin;
			gamefield->initializeColumHeights();
			gamefield->createDefaultGameField();

			for(int h = 0; h < gamefield->getGamefieldHeight(); h ++)
			{
				for (int w = 1; w <= gamefield->getGamefieldWidth(); w++)
				{
					gamefield->setChipForPlayer(w, ZeichenX);
				}
			}
			
			
			Assert::IsTrue(checkwin.checkDraw(gamefield));
		}

		TEST_METHOD(PlayerNotNull)
		{
			// TODO: Testcode hier eingeben
			Player *player = new HumanPlayer(Spieler1, ZeichenX);
			Assert::IsFalse(player == NULL);
		}

		//Zeit ~4 Minuten 30 Sekunden
		TEST_METHOD(SmartBotVSRandomBot)
		{
			// TODO: Testcode hier eingeben
			int SmartBotWon = 0;

			Game game;
			game.player1 = new RandomBot(Spieler1, ZeichenX);
			game.player2 = new SmartBot(Spieler2, ZeichenPlus);

			for (int i = 0; i < 1000; i++) {

				game.initVariables();
				game.initNewGame();
				
				while (!game.winner && !game.draw) {
					game.Gameloop();
					game.checkForWinner();
				}

				//Wenn sich die Spieler reihe geändert hat ist Spieler 1 an der reihe  
				//Spieler 2 hat aber gewonnen
				if (game.gamerow == Spieler1) SmartBotWon++;
			}
			
			//850/1000 = 85%
			Assert::IsTrue(SmartBotWon > 850);
		}

		//Zeit: ~4 Minuten
		TEST_METHOD(SmartBotVSLeftBot)
		{
			// TODO: Testcode hier eingeben
			int SmartBotWon = 0;

			Game game;
			game.player1 = new LeftRowBot(Spieler1, ZeichenX);
			game.player2 = new SmartBot(Spieler2, ZeichenPlus);

			for (int i = 0; i < 1000; i++) {

				game.initVariables();
				game.initNewGame();

				while (!game.winner && !game.draw) {
					game.Gameloop();
					game.checkForWinner();
				}

				if (game.gamerow == Spieler1) SmartBotWon++;
			}

			Assert::IsTrue(SmartBotWon > 850);
		}

		//Zeit: ~3 Minuten
		TEST_METHOD(SmartBotVSLowestColumnBot)
		{
			// TODO: Testcode hier eingeben
			int SmartBotWon = 0;

			Game game;
			game.player1 = new LowestColunmBot(Spieler1, ZeichenX);
			game.player2 = new SmartBot(Spieler2, ZeichenPlus);

			for (int i = 0; i < 1000; i++) {
	
				game.initVariables();
				game.initNewGame();

				while (!game.winner && !game.draw) {
					game.Gameloop();
					game.checkForWinner();
				}

				if (game.gamerow == Spieler1) SmartBotWon++;

			}

			Assert::IsTrue(SmartBotWon > 850);
		}


		TEST_METHOD(CheckWinnerHorizontal)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();
			
			CheckForWin checkwin;

			gamefield->initializeColumHeights();
			gamefield->createDefaultGameField();

			for (int i = 0; i < 4; i++) {
				//Stetze 3 steine in die erste spatlte
				gamefield->setChipForPlayer(1, ZeichenX);
			}

			Assert::IsTrue(checkwin.checkForWin(gamefield));
		}

		TEST_METHOD(CheckWinnerVertikalright)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();

			CheckForWin checkwin;
			gamefield->initializeColumHeights();
			gamefield->createDefaultGameField();

			for (int i = 1; i < 5; i++) {
				//Stetze 3 steine in die erste spatlte
				gamefield->setChipForPlayer(i, ZeichenX);
			}

			Assert::IsTrue(checkwin.checkForWin(gamefield));
		}

		TEST_METHOD(CheckWinnerVertikalLeft)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();

			CheckForWin checkwin;
			gamefield->initializeColumHeights();
			gamefield->createDefaultGameField();

			for (int i = 4; i > 0; i--) {
				//Stetze 3 steine in die erste spatlte
				gamefield->setChipForPlayer(1, ZeichenX);
			}

			Assert::IsTrue(checkwin.checkForWin(gamefield));
		}

		TEST_METHOD(CheckWinnerDiagonalRight)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();

			CheckForWin checkwin;
			gamefield->initializeColumHeights();
			gamefield->createDefaultGameField();

			gamefield->setChipForPlayer(1 ,ZeichenX);
			gamefield->setChipForPlayer(2, ZeichenPlus);
			gamefield->setChipForPlayer(2, ZeichenX);
			gamefield->setChipForPlayer(3, ZeichenPlus);
			gamefield->setChipForPlayer(3, ZeichenPlus);
			gamefield->setChipForPlayer(3, ZeichenX);
			gamefield->setChipForPlayer(4, ZeichenX);
			gamefield->setChipForPlayer(4, ZeichenPlus);
			gamefield->setChipForPlayer(4, ZeichenX);
			gamefield->setChipForPlayer(4, ZeichenX);

			Assert::IsTrue(checkwin.checkForWin(gamefield));
		}

		TEST_METHOD(CheckWinnerDiagonalLeft)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();

			CheckForWin checkwin;
			gamefield->initializeColumHeights();
			gamefield->createDefaultGameField();


			//Wirf startend von Zeile 1 Zeichen diagonal ein 
			gamefield->setChipForPlayer(1, ZeichenX);
			gamefield->setChipForPlayer(1, ZeichenPlus);
			gamefield->setChipForPlayer(1, ZeichenX);
			gamefield->setChipForPlayer(1, ZeichenPlus);
			gamefield->setChipForPlayer(2, ZeichenX);
			gamefield->setChipForPlayer(2, ZeichenPlus);
			gamefield->setChipForPlayer(2, ZeichenPlus);
			gamefield->setChipForPlayer(3, ZeichenX);
			gamefield->setChipForPlayer(3, ZeichenPlus);
			gamefield->setChipForPlayer(4, ZeichenX);

			Assert::IsTrue(checkwin.checkForWin(gamefield));
		}

		TEST_METHOD(CanInsert)
		{
			// TODO: Testcode hier eingeben
			BuildGameField *gamefield = new BuildGameField();

			gamefield->initializeColumHeights();
			gamefield->createDefaultGameField();

			for (int i = 0; i < 6; i++) {
				//Setze 3 steine in die erste spatlte
				Assert::IsTrue(gamefield->canInsert(1));
				gamefield->setChipForPlayer(1, ZeichenX);
				
			}
			Assert::IsFalse(gamefield->canInsert(1));
		}

	};


}