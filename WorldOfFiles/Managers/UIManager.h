#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "../UI/TextBox.h"
#include "../UI/Button.h"

enum ButtonLayout
{
	Normal,
	Vertical

};

class UIManager 
{
private:
	// Reference to the main window, giving option to draw
	RenderWindow *window;
	
	// Important Variables
	Font font;
	ButtonLayout layout;

	// UI Elements
	TextBox MainBox;
	Button Buttons[6];
	
public:
	// Constructor for Initializing the Manager
	UIManager();
	UIManager(RenderWindow *_window, Font & _font);

	// Setters for the different Text Strings
	void SetMainString(String _string);
	void SetButtonString(String _string, int _number);
	void SetButtonLayout(ButtonLayout _layout);

	// Funtions that use Buttons
	void SetNBButtonVisible(int _number);
	void SetButtonInteractable(int _number, bool _interactable);
	int IsButtonPressed(Vector2i _position); // Button pressed (-1, if none)


	// Resizes the TextBoxes and Buttons
	void ResizeUI();

	// Draw the elements of the state to the window
	void DrawScreen();
};


#endif // !UIMANAGER_H
