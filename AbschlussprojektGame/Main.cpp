// AbschlussprojektGame.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "../Game/Game.h"
#include <stdlib.h>
#include <crtdbg.h>
#define _CTRDGB_MAP_ALLOC

int main()
{
	Game game;
	game.start();

	system("PAUSE");
	_CrtDumpMemoryLeaks();
    return 0;
}

