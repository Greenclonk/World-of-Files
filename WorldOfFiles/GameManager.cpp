#include "pch.h"
#include "Managers/GameManager.h"

GameManager::GameManager()
{

}

GameManager::GameManager(RenderWindow * _window, Font & _font)
{
	window = _window;
	UI = UIManager(_window, _font);
	Reader = FileManager();

	statePlay = GameState::LanguagePick;

	std::vector<String> foundLanguages = Reader.GetLanguages();

	int nbButton = foundLanguages.size() < 6 ? foundLanguages.size() : 5;
	for (int i = 0; i < nbButton; i++)
	{
		UI.SetButtonString(foundLanguages.at(i), i);
	}
	// Keep last Button to always be next
	UI.SetButtonString(L">", 5);
	lastButton = 5;

	UI.SetButtonLayout(ButtonLayout::Vertical);
	UI.SetNBButtonVisible(foundLanguages.size() < 6 ? foundLanguages.size() : 6);

	selectionPage = 0;
	isDirty = true;
	isButtonPressed = -1;
}

void GameManager::EventUpdate(Event event)
{
	// Checks if Mouse Button has been pressed
	if (event.type == Event::MouseButtonPressed)
	{
		Vector2i mousePosition = (Mouse::getPosition() - window->getPosition());
		mousePosition.y -= 30; // Remove Title Border

		int pressed = UI.IsButtonPressed(mousePosition);
		if (pressed != -1 && isButtonPressed == -1)
		{
			isButtonPressed = pressed;
		}
	}
}

void GameManager::Update()
{
	if (isButtonPressed != -1)
	{
		switch (statePlay)
		{
		case LanguagePick:
		{
			if (isButtonPressed != lastButton)
			{
				language = Reader.ReadLanguageFile(isButtonPressed + selectionPage * 5);

				SetMainMenu();
				selectionPage = 0;
			}
			else
			{
				SelectNext(Reader.GetLanguages());
			}
			break;
		}
		case MainMenu: 
		{
			int size = 0;
			// Button layout => NEW_BUTTON, LOAD_BUTTON, LANGUAGE_BUTTON, EXIT_BUTTON
			switch (isButtonPressed)
			{
			case 0:
			{
				std::vector<String> foundWorlds = Reader.GetWorlds();
				size = foundWorlds.size();

				int nbButton = size < 6 ? size : 5;
				for (int i = 0; i < nbButton; i++)
				{
					UI.SetButtonString(foundWorlds.at(i), i);
				}

				statePlay = GameState::WorldSelect;
				break;
			}
			case 1:
			{
				std::vector<String> foundSaves = Reader.GetSaveFiles();
				size = foundSaves.size();

				int nbButton = size < 6 ? size : 5;
				for (int i = 0; i < nbButton; i++)
				{
					UI.SetButtonString(foundSaves.at(i), i);
				}

				statePlay = GameState::LoadSelect;
				break;
			}
			case 2:
			{
				std::vector<String> foundLanguages = Reader.GetLanguages();
				size = foundLanguages.size();

				int nbButton = size < 6 ? size : 5;
				for (int i = 0; i < nbButton; i++)
				{
					UI.SetButtonString(foundLanguages.at(i), i);
				}

				statePlay = GameState::LanguagePick;
				break;
			}
			default:
				window->close();
				break;
			}

			lastButton = size < 6 ? size : 5;
			UI.SetNBButtonVisible(size < 6 ? size : 6);
			UI.SetButtonLayout(ButtonLayout::Vertical);
			break;
		}
		case WorldSelect:
		{
			if (isButtonPressed != lastButton)
			{
				world = Reader.ReadWorldFile(isButtonPressed + selectionPage * 5);
				player = Player(L"Player", world.GetWorldName(), 0);

				PlayerUpdate();
				selectionPage = 0;
				statePlay = GameState::Explore;
			}
			else
			{
				SelectNext(Reader.GetWorlds());
			}
			break;
		}
		case LoadSelect:
		{
			if (isButtonPressed != lastButton)
			{
				player = Reader.ReadPlayerFile(isButtonPressed + selectionPage * 5);
				std::vector<String> worlds = Reader.GetWorlds();

				bool success = false;
				for (int i = 0; i < worlds.size(); i++)
				{
					if (worlds.at(i) == player.GetWorldName())
					{
						success = true;
						world = Reader.ReadWorldFile(i);
						i = worlds.size();
					}
				}

				if (success)
				{
					selectionPage = 0;
					statePlay = GameState::Explore;
					PlayerUpdate();
				}
				else
				{
					selectionPage = 0;
					SetMainMenu();
				}
			}
			else
			{
				SelectNext(Reader.GetSaveFiles());
			}
			break;
		}
		case Explore:
		{
			std::vector<int> connections = world.GetPlaceAt(player.GetWhereAt()).GetConnections();

			lastButton = connections.size();
			if (isButtonPressed < lastButton)
			{
				int goToID = connections.at(isButtonPressed);
				player.GoToPlace(world.GetPlaceAt(goToID));
				PlayerUpdate();
			}
			else
			{
				UI.SetButtonString(language.GetValue(String(L"CONTINUE_BUTTON")), 0);
				UI.SetButtonString(language.GetValue(String(L"SAVE_BUTTON")), 1);
				UI.SetButtonString(language.GetValue(String(L"EXIT_BUTTON")), 2);

				UI.SetButtonLayout(ButtonLayout::Vertical);
				UI.SetNBButtonVisible(3);

				statePlay = GameState::GameMenu;
			}
			break;
		}
		case GameMenu:
		{
			switch (isButtonPressed)
			{
			case 1:
			{
				Reader.SavePlayerFiles(player);
				//We leave it unbreaked, so that it continues into the next case and sets it back to explore
			}
			case 0:
			{
				PlayerUpdate();
				statePlay = GameState::Explore;
				break;
			}
			default:
				window->close();
				break;
			}
			break;
		}
		default:
			window->close();
			break;
		}
		
		isDirty = true;
		isButtonPressed = -1;
	}
}

void GameManager::SetMainMenu()
{
	// The buttons receive their translated string from our language map
	UI.SetButtonString(language.GetValue(L"NEW_BUTTON"), 0);
	UI.SetButtonString(language.GetValue(L"LOAD_BUTTON"), 1);
	UI.SetButtonString(language.GetValue(L"LANGUAGE_BUTTON"), 2);
	UI.SetButtonString(language.GetValue(L"EXIT_BUTTON"), 3);

	UI.SetButtonLayout(ButtonLayout::Vertical);
	UI.SetNBButtonVisible(4);

	statePlay = GameState::MainMenu;
}

void GameManager::PlayerUpdate()
{
	Place place = world.GetPlaceAt(player.GetWhereAt());

	int nbButton = place.GetConnections().size();
	for (int i = 0; i < nbButton; i++)
	{
		UI.SetButtonString(world.GetPlaceAt(place.GetConnections().at(i)).GetName(), i);
	}

	UI.SetButtonLayout(ButtonLayout::Normal);
	UI.SetNBButtonVisible(nbButton + 1);
	lastButton = nbButton;

	// Create the text that will be on the main text box, it is fused from different strings
	String mainText =
		language.GetValue(std::wstring(L"ARRIVED_TEXT")) +
		String(L"\n\n") +
		place.GetDescription() +
		String(L"\n\n") +
		language.GetValue(std::wstring(L"WHERETO_TEXT"));

	mainText.replace(std::wstring(L"PLACE"), place.GetName());
	mainText.replace(std::wstring(L"PLAYER"), player.GetName());

	UI.SetButtonString(language.GetValue(std::wstring(L"MENU_BUTTON")), nbButton);
	UI.SetMainString(mainText);
}

void GameManager::SelectNext(std::vector<String> _vector)
{
	//Increment the page that is selected
	selectionPage++;

	// Reset page to show first buttons
	if (selectionPage * 5 > _vector.size()) selectionPage = 0;

	int remaining = _vector.size() - selectionPage * 5;
	int nbButton = remaining < 6 ? remaining : 5;
	for (int i = 0; i < nbButton; i++)
	{
		UI.SetButtonString(_vector.at(i + selectionPage * 5), i);
	}
	// Keep last Button to always be next
	UI.SetButtonString(L">", nbButton);

	UI.SetButtonLayout(ButtonLayout::Vertical);
	UI.SetNBButtonVisible(nbButton + 1);
	lastButton = nbButton;
}

void GameManager::RenderUpdate()
{
	// Update frame only when something has changed
	if (isDirty)
	{
		UI.DrawScreen();
		isDirty = false;
	}
}
