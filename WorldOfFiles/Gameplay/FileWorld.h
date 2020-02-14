#ifndef FILEWORLD_H
#define FILEWORLD_H

#include "../SFML.h"
#include <vector>

class Place
{
private:
	int ID;
	String name;
	String description;
	std::vector<int> connections;

public:
	// Constructor for an area/place
	Place(); // Invalid Place
	Place(int _ID, String _name, String _description, std::vector<int> _places);

	// Getters
	String GetName();
	String GetDescription();
	int GetID();
	std::vector<int> GetConnections();

};

class FileWorld
{
private:
	String name;
	std::vector<Place> places;

public:
	// Constructors for File World
	FileWorld();
	FileWorld(String _name, std::vector<Place> _places);

	// Getters for the world
	String GetWorldName();
	std::vector<Place> GetPlaces();

	// Getters for the vector, giving back a Place/Area
	Place GetPlaceAt(int _ID);
	Place GetPlaceCalled(String _name);
};


#endif // !FILEWORLD_H