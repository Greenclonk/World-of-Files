#include "pch.h"
#include "Gameplay/Player.h"

Player::Player(String _name, String _world, int _at)
{
	name = _name;
	worldname = _world;
	placeID = _at;
}

void Player::GoToPlace(Place _place)
{
	placeID = _place.GetID();
}

String Player::GetName()
{
	return name;
}

String Player::GetWorldName()
{
	return worldname;
}

int Player::GetWhereAt()
{
	return placeID;
}
