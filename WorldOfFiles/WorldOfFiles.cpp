// WorldOfFiles.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "SFML.h"
#include "Managers/GameManager.h"

int main()
{
	//Read Init.txt for values of Window and Font
	Options options = FileManager::ReadOptions();
	RenderWindow window(VideoMode(options.windowSize.x, options.windowSize.y), "World of Files");

	String fontPath = String(L"Files\\Font\\YuGoth.ttc");
	
	Font gameFont;
	if (!gameFont.loadFromFile(fontPath))
	{
		printf("Font was not loaded! Trying regular font! \n");
		window.close();
	}

	GameManager GameManager(&window, gameFont);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// Enters the event checker of GameManager
			GameManager.EventUpdate(event);
		}

		// Enter the updatephase of GameManager
		GameManager.Update();

		// Enters the renderphase of GameManager
		GameManager.RenderUpdate();
	}

	return 0;
}
