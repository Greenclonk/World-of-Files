#ifndef LANGUAGES_H
#define LANGUAGES_H

#include "../SFML.h"
#include <map>
#include <iostream>

class Language
{
private:
	// The name of the language
	String name;
	// The regular strips of text
	std::map<std::wstring, std::wstring> map;

public:
	// Constructor
	Language();
	Language(String _name, std::map<std::wstring, std::wstring> _map);

	// Set the new language, giving a full translated map/dictionary
	void SetLanguage(String _name, std::map<std::wstring, std::wstring> _map);

	// Get the value from the key
	String GetValue(std::wstring _key);
};

#endif // !LANGUAGES_H