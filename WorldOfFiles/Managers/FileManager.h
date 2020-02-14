#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../SFML.h"
#include <vector>
#include "../Gameplay/FileWorld.h"
#include "../Gameplay/Languages.h"
#include "../Gameplay/Player.h"

struct Options
{
	Vector2i windowSize;
	String fontName;

};

class FileManager
{
private:
	// Inside of the three folders, collection of filenames
	std::vector<String> worlds;
	std::vector<String> languages;
	std::vector<String> saves;

public:
	// Constructor for File Manager
	FileManager();

	// Create the world from a file
	FileWorld ReadWorldFile(int _num);
	// Initialize the used Language
	Language ReadLanguageFile(int _num);
	// Save/Load the player data
	void SavePlayerFiles(Player _player);
	Player ReadPlayerFile(int _num);

	// Vector Getters
	std::vector<String> GetWorlds();
	std::vector<String> GetLanguages();
	std::vector<String> GetSaveFiles();

	// Read the init file that changes window resolution
	static Options ReadOptions();
};


#endif // !FILEMANAGER_H