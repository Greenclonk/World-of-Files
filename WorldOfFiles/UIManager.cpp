#include "pch.h"
#include "Managers/UIManager.h"

// Constuctors
UIManager::UIManager()
{
	window = nullptr;
}

UIManager::UIManager(RenderWindow *_window, Font & _font)
{
	window = _window;

	if (window != nullptr)
	{
		// Initialize the main text box that will be used for the Programm
		MainBox = TextBox(window, _font);

		// Initialize all 6 Buttons used in the Programm
		for (int i = 0; i < 6; i++)
		{
			Buttons[i] = Button(window, _font);
		}

		// Initialize layout to Normal (Big Box with Buttons under)
		layout = ButtonLayout::Normal;

		ResizeUI();
	}
}

// Setters
void UIManager::SetMainString(String _string)
{
	MainBox.SetString(_string);
}

void UIManager::SetButtonString(String _string, int _number)
{
	// Check if number is viable
	if (_number >= 0 && _number <= 6)
	{
		Buttons[_number].SetString(_string);
	}
}

void UIManager::SetButtonLayout(ButtonLayout _layout)
{
	layout = _layout;

	switch (layout)
	{
	case Vertical:
		MainBox.SetVisible(false);
		break;
	default:
		MainBox.SetVisible(true);
		break;
	}
}

int UIManager::IsButtonPressed(Vector2i _position)
{
	int button = -1;
	for (int i = 0; i < 6; i++)
	{
		if (Buttons[i].GetVisible() && Buttons[i].IsInside(_position))
		{
			button = i;
		}
	}
	return button;
}

void UIManager::SetNBButtonVisible(int _number)
{
	// Check if number is viable
	if (_number >= 0 && _number <= 6)
	{
		// Checks how many Buttons are visible
		int nbVisible = 0;
		for (int i = 0; i < 6; i++)
		{
			if (Buttons[i].GetVisible())
			{
				nbVisible++;
			}
		}

		if (nbVisible != _number)
		{
			for (int i = 0; i < 6; i++)
			{
				Buttons[i].SetVisible(false);
			}

			for (int i = 0; i < _number; i++)
			{
				Buttons[i].SetVisible(true);
			}
		}

		ResizeUI();
	}
}

void UIManager::SetButtonInteractable(int _number, bool _interactable)
{
	// Check if number is viable
	if (_number >= 0 && _number < 6)
	{
		Buttons[_number].SetInteractable(_interactable);
	}
}

// Updates the new sizes for the UI
void UIManager::ResizeUI()
{
	// Checks how many Buttons are visible
	int nbVisible = 0;
	for (int i = 0; i < 6; i++)
	{
		if (Buttons[i].GetVisible())
		{
			nbVisible++;
		}
	}
	// Perpare the Vectors to be used
	Vector2f size, position;

	switch (layout)
	{
	case Vertical:
		if (nbVisible > 0)
		{
			// Calculate suitable size for buttons
			size.x = (float)(window->getSize().x / 3);
			size.y = (float)(window->getSize().y / nbVisible);

			for (int i = 0; i < nbVisible; i++)
			{
				// Calculate position for Button
				position.x = size.x;
				position.y = i * size.y;

				// Update their position and size
				Buttons[i].SetSize(size);
				Buttons[i].SetPosition(position);
			}
		}
		break;
	default:
		{
			// How much space for the Buttons, a third of the screen
			int buttonSpaceHeight = window->getSize().y / 3;

			Vector2f boxPosition = Vector2f(0.0f, 0.0f);
			Vector2f boxSize = Vector2f((float)window->getSize().x, (float)(window->getSize().y - buttonSpaceHeight));

			MainBox.SetPosition(boxPosition);
			MainBox.SetSize(boxSize);

			if (nbVisible > 0)
			{
				// Prepare the vector for when number of Visible Buttons are 5
				Vector2f sizeF;

				// If there are more than three buttons, make two rows
				// Calculate suitable size for buttons
				if (nbVisible > 3)
				{
					size.x = (float)(boxSize.x / (nbVisible / 2));
					size.y = (float)(buttonSpaceHeight / 2);

					//Calculate the size for the first Row
					if (nbVisible == 5)
					{
						sizeF.x = (float)(boxSize.x / 3);
						sizeF.y = (float)(buttonSpaceHeight / 2);
					}
				}
				else
				{
					size.x = (float)(boxSize.x / nbVisible);
					size.y = (float)buttonSpaceHeight;
				}

				for (int i = 0; i < nbVisible; i++)
				{
					// Calculate the position of the button i
					// Update their position and size

					if (nbVisible == 5)
					{
						// Layout is special when 5 are active
						if (i < 3)
						{
							// Three Buttons on top row
							position.x = i * sizeF.x;
							position.y = (float)(window->getSize().y - buttonSpaceHeight);

							// Button size is different in this case
							Buttons[i].SetSize(sizeF);
						}
						else
						{
							//Two Buttons on bottom row
							position.x = (i - 3) * size.x;
							position.y = window->getSize().y - buttonSpaceHeight + size.y;

							Buttons[i].SetSize(size);
						}
					}
					else
					{
						if (nbVisible < 4 || i < nbVisible / 2)
						{
							// Calculate X position for Button
							position.x = i * size.x;
						}
						else
						{
							// Calculate X position for bottom Button
							position.x = (i - nbVisible / 2) * size.x;
						}

						// Calculate Y position for Button
						position.y = (float)(window->getSize().y - buttonSpaceHeight);

						// Move Button from top row to bottom row
						if ((nbVisible == 4 || nbVisible == 6) && i >= nbVisible / 2)
						{
							position.y += size.y;
						}

						Buttons[i].SetSize(size);
					}

					Buttons[i].SetPosition(position);
				}
			}
		}
		break;
	}
}

// Renders the UI Elements unto the referenced Window
void UIManager::DrawScreen()
{
	if (window != nullptr)
	{
		// Resets the Window to black
		window->clear();

		// Draw the Main Box into the window
		MainBox.Draw();

		// Draw the six buttons into the window
		for (int i = 0; i < 6; i++)
			{ Buttons[i].Draw(); }

		// Updates the window with the shown UI Elements
		window->display();
	}
}
