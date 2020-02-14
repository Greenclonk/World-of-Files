#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "UIManager.h"
#include "FileManager.h"
#include "../Gameplay/FileWorld.h"
#include "../Gameplay/Player.h"


enum GameState
{
	LanguagePick,
	MainMenu,
	WorldSelect,
	LoadSelect,
	Explore,
	GameMenu

};

class GameManager
{
private:
	// Reference to the main window
	RenderWindow *window;

	// Other Managers
	UIManager UI; // Renders the Windows and Buttons
	FileManager Reader; // Reads files, to create Languages, Worls, and Saves

	// Gameplay Elements
	GameState statePlay; // The Gamestate, which state is shown
	FileWorld world; // The World, which has the places and its connections
	Player player; // The Explorer/Player, who knows where he is
	Language language; // The Language chosen to play the game in

	// Checks if anything has been changed
	bool isDirty; 
	// Checks if a Button has been pressed (-1, if not)
	int isButtonPressed;
	// If selection is more than 5, add a Next Button
	int selectionPage;
	// What is the last Button (for next page)
	int lastButton;

public:
	// Constructor
	GameManager();
	GameManager(RenderWindow *_window, Font & _font);

	// Main Functions
	void EventUpdate(Event event);
	void Update();
	void RenderUpdate();

	// Small Functions to remove double code
	void SetMainMenu();
	void PlayerUpdate();
	void SelectNext(std::vector<String> _vector);
};

#endif // !GAMEMANAGER_H