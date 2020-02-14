#include "pch.h"
#include "Managers/FileManager.h"
#include <fstream>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

FileManager::FileManager()
{
	// Initialize the vectors used to store folder information
	worlds = std::vector<String>();
	languages = std::vector<String>();
	saves = std::vector<String>();

	String path = "Files\\";
	String folders[3] = {"Worlds\\","Languages\\","Saves\\"};
	// TODO, read the folders
	for (int folder = 0; folder < 3; folder++)
	{
		//line from http://www.cplusplus.com/forum/beginner/215121/, slightly touched
		for (auto & p : fs::directory_iterator((path + folders[folder]).toAnsiString()))
		{
			if (String(p.path().extension()) == String(L".file"))
			{
				String newValue = p.path().filename().wstring();
				newValue = newValue.substring(0, newValue.find("."));

				if (folder == 0) // Worlds
				{ worlds.push_back(newValue); }
				if (folder == 1) // Languages
				{ languages.push_back(newValue); }
				if (folder == 2) // Saves
				{ saves.push_back(newValue); }
			}
		}
	}
}

FileWorld FileManager::ReadWorldFile(int _num)
{
	String name = L"invalid";
	std::vector<Place> places = std::vector<Place>();

	if (_num >= 0 && _num < worlds.size())
	{
		name = worlds.at(_num);
		String filepath = L"Files\\Worlds\\" + name + L".file";
		std::wifstream WorldFile;
		WorldFile.open(filepath.toWideString(), std::wofstream::in);
		if (WorldFile.is_open())
		{
			// Reference Code from https://stackoverflow.com/questions/19697296/what-is-stdwifstreamgetline-doing-to-my-wchar-t-array-its-treated-like-a-b
			WorldFile.imbue(std::locale(WorldFile.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

			// Read the whole file, adding the different places into the created World
			wchar_t buffer[1024];
			String line;
			std::wstring first, second, third;
			int count = 0;

			if (!WorldFile.eof())
			{
				WorldFile.getline(buffer, 1024);
				line = String(buffer);
			}

			// Checks if it is a World file
			if (line.find(L"--WORLD--") != String::InvalidPos)
			{
				while (!WorldFile.eof())
				{
					WorldFile.getline(buffer, 1024);

					// Example of a line, "Castle|4,5,8|A beautiful Castle on top of the Mountain
					line = String(buffer);

					// Check size of the line, to remove invisible characters
					if (line.getSize() > 2)
					{
						int one = line.find(L"|"),
							two = line.find(L"|", one + 1);

						// Divide the line into two parts, one which has the name, the other has connections
						first = line.substring(0, one); // example: Castle
						second = line.substring(one + 1, two - one - 1); // example: 4,5,8
						third = line.substring(two + 1); // unused, example: A beautiful Castle on top of the Mountain

						// Initialize the variables needed
						String placeName, description, nextHalf = second;
						std::wstring secSplit;
						std::vector<int> placeConnections;

						int nb = 0, conID = 0;

						// Take first Integer before the ','
						nb = nextHalf.find(L",");
						secSplit = nextHalf.substring(0, nb);
						// Check if the string has at least 1 char
						if (secSplit.size() > 0)
						{
							conID = std::stoi(secSplit);
							placeConnections.push_back(conID);
						}
						// Continue splitting and adding Place IDs to Connections
						while (nextHalf.find(L",") != String::InvalidPos)
						{
							nextHalf = nextHalf.substring(nb + 1);
							nb = nextHalf.find(L",");
							secSplit = nextHalf.substring(0, nb);
							// Check if the string has at least 1 char
							if (secSplit.size() > 0)
							{
								conID = std::stoi(secSplit);
								placeConnections.push_back(conID);
							}
						}

						// Put the split line into their respective string
						placeName = String(first);
						description = String(third);
						// Replace the fake line breaks ('†') into real ones ('\n')
						description.replace(L"†", '\n');

						Place place(count, placeName, description, placeConnections);
						// Add the newly created place to the world
						places.push_back(place);
						// Increment nb of count/id
						count++;
					}
				}
			}
		}
		WorldFile.close();
	}

	return FileWorld(name, places);
}

Language FileManager::ReadLanguageFile(int _num)
{
	String name = L"invalid";
	std::map<std::wstring, std::wstring> map = std::map<std::wstring, std::wstring>();

	if (_num >= 0 && _num < languages.size())
	{
		name = languages.at(_num);
		String filepath = L"Files\\Languages\\" + name + L".file";
		std::wifstream LanugageFile;
		LanugageFile.open(filepath.toWideString(), std::wofstream::in);
		if (LanugageFile.is_open())
		{
			// Reference Code from https://stackoverflow.com/questions/19697296/what-is-stdwifstreamgetline-doing-to-my-wchar-t-array-its-treated-like-a-b
			LanugageFile.imbue(std::locale(LanugageFile.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

			// Read the whole file, adding the different places into the created World
			wchar_t buffer[1024];
			String line, key, value;

			if(!LanugageFile.eof())
			{
				// Get the first line of the file
				LanugageFile.getline(buffer, 1024);
				line = String(buffer);
			}

			// Checks if it is a Language file
			if (line.find(L"-LANGUAGE-") != String::InvalidPos)
			{
				while (!LanugageFile.eof())
				{
					LanugageFile.getline(buffer, 1024);
					line = String(buffer);

					// Check size of the line, to removes empty lines
					if (line.getSize() > 1)
					{
						// Divide the line into two parts, one which the key, the other the value
						key = String(line.substring(0, line.find(L"|"))); // example: ARRIVED
						value = String(line.substring(line.find(L"|") + 1)); // example: You arrived at 0 (0 is replaced by place name)

						map.insert(std::pair<std::wstring, std::wstring>(key, value));
					}
				}
			}
		}
		LanugageFile.close();
	}

	return Language(name, map);
}

void FileManager::SavePlayerFiles(Player _player)
{
	String filepath = L"Files\\Saves\\" + _player.GetName() + L".file";
	std::wofstream PlayerFile;
	PlayerFile.open(filepath.toWideString(), std::wofstream::out);
	if (PlayerFile.is_open())
	{
		PlayerFile << _player.GetWorldName().toWideString() << std::endl;
		PlayerFile << _player.GetWhereAt() << std::endl;
	}
	PlayerFile.close();
}

Player FileManager::ReadPlayerFile(int _num)
{
	String name = L"Player", world = L"Invalid";
	int at = -1;

	if (_num >= 0 && _num < saves.size())
	{
		name = saves.at(_num);
		String filepath = L"Files\\Saves\\" + name + L".file";
		std::ifstream PlayerFile;
		PlayerFile.open(filepath.toWideString(), std::ifstream::in);
		if (PlayerFile.is_open())
		{
			char line[1024];

			// First line of file is the name of the World this player is from
			PlayerFile.getline(line, 1024);
			world = String(line);
			// Second line is the position they saved at
			PlayerFile.getline(line, 1024);
			at = std::stoi(String(line).toAnsiString());
		}
		PlayerFile.close();
	}

	return Player(name, world, at);
}

std::vector<String> FileManager::GetWorlds()
{
	return worlds;
}
std::vector<String> FileManager::GetLanguages()
{
	return languages;
}
std::vector<String> FileManager::GetSaveFiles()
{
	return saves;
}

Options FileManager::ReadOptions()
{
	Options options;

	options.windowSize = Vector2i(1200,600);
	options.fontName = L"YuGoth.ttc";

	//Reads/Create the file that hold the information
	String filepath = L"Files\\Options.txt";
	std::wifstream OptionsFile;
	OptionsFile.open(filepath.toWideString(), std::wifstream::in);
	if (OptionsFile.is_open())
	{
		// Reference Code from https://stackoverflow.com/questions/19697296/what-is-stdwifstreamgetline-doing-to-my-wchar-t-array-its-treated-like-a-b
		OptionsFile.imbue(std::locale(OptionsFile.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

		wchar_t line[1024];
		// Remove First line, which is a description
		OptionsFile.getline(line, 1024);
		// Reading second Line, X resolution
		OptionsFile.getline(line, 1024);
		options.windowSize.x = std::stoi(String(line).toAnsiString());
		// Reading third Line, Y resolution
		OptionsFile.getline(line, 1024);
		options.windowSize.y = std::stoi(String(line).toAnsiString());
		// Reading fourth Line, name of font (Has Bug)
	//	OptionsFile.getline(line, 1024);
	//	options.fontName = String(line);

		if (options.windowSize.x < 300) options.windowSize.x = 300;
		if (options.windowSize.y < 300) options.windowSize.y = 300;
	}
	else
	{
		//Create the missing options txt
		std::wofstream OptionsFileOut;
		OptionsFileOut.open(filepath.toWideString(), std::wofstream::out);
		OptionsFile.imbue(std::locale(OptionsFileOut.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));

		OptionsFileOut << "first X dimension, then Y, then name of font" << std::endl;
		OptionsFileOut << options.windowSize.x << std::endl;
		OptionsFileOut << options.windowSize.y << std::endl;
	//	OptionsFileOut << options.fontName.toWideString() << std::endl;

		OptionsFileOut.close();
	}
	OptionsFile.close();

	return options;
}
