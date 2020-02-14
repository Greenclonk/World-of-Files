#ifndef PLAYER_H
#define PLAYER_H

#include "FileWorld.h"

class Player
{
private:
	String name;
	String worldname;
	int placeID;

public:
	// Constructors
	Player(String _name = L"Player", String _world = L"Invalid",int _at = -1);

	// Set ID of where the Player is at
	void GoToPlace(Place _place);

	// Getters for name and ID of place
	String GetName();
	String GetWorldName();
	int GetWhereAt();
};

#endif // !PLAYER_H