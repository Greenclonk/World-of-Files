#include "pch.h"
#include "Gameplay/Languages.h"

Language::Language()
{
	name = L"uninitialized";
	map = std::map<std::wstring, std::wstring>();
}

Language::Language(String _name, std::map<std::wstring, std::wstring> _map)
{
	name = _name;
	map = std::map<std::wstring, std::wstring>(_map);
}

void Language::SetLanguage(String _name, std::map<std::wstring, std::wstring> _map)
{
	name = _name;
	map = std::map<std::wstring, std::wstring>(_map);
}

String Language::GetValue(std::wstring _key)
{
	std::map<std::wstring, std::wstring>::iterator it = map.find(_key);

	if (it != map.end())
	{
		// Returns the value found
		return it->second;
	}

	return String(L"VALUE NOT FOUND");
}
