#include "pch.h"
#include "Gameplay/FileWorld.h"
#include <fstream>

FileWorld::FileWorld()
{
	name = L"invalid";
	places = std::vector<Place>();
}

FileWorld::FileWorld(String _name, std::vector<Place> _places)
{
	name = _name;
	places = std::vector<Place>(_places);
}

String FileWorld::GetWorldName()
{
	return name;
}

std::vector<Place> FileWorld::GetPlaces()
{
	return places;
}

Place FileWorld::GetPlaceAt(int _ID)
{
	for (std::vector<Place>::iterator it = places.begin(); it != places.end(); it++)
	{
		if ((*it).GetID() == _ID)
		{
			return (*it);
		}
	}

	return Place();
}

Place FileWorld::GetPlaceCalled(String _name)
{
	for (std::vector<Place>::iterator it = places.begin(); it != places.end(); it++)
	{
		if ((*it).GetName() == _name)
		{
			return (*it);
		}
	}
	
	return Place();
}

Place::Place()
{
	ID = -1;
	name = L"invalid";
	description = L"invalid";

	connections = std::vector<int>();
}

Place::Place(int _ID, String _name, String _description, std::vector<int> _places)
{
	ID = _ID;
	name = _name;
	description = _description;
	connections = std::vector<int>(_places);
}

String Place::GetName()
{
	return name;
}

String Place::GetDescription()
{
	return description;
}

int Place::GetID()
{
	return ID;
}

std::vector<int> Place::GetConnections()
{
	return connections;
}
