#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "../SFML.h"


class TextBox {

private:
	// Reference to the main window, giving option to draw
	RenderWindow *window;
	
	// TextBox's drawables variables, giving it a shape for the window
	RectangleShape outsideBox;
	RectangleShape insideBox;
	Text text;

	// Variables
	bool isVisible; // Is Text Box Visible/Active
	bool isCentered; // Is Text centered

protected:

	// Size of the TextBox layout, and position
	Vector2f size;
	Vector2f position;

	// Give Ability to Children to change box Colors, and Text position
	void SetBackColor(Color _color);
	void SetTextPosition(Vector2f _position);
	// Text Getable, giving string and size to Children
	Text GetText();

public:
	// Constructor for the button
	TextBox();
	TextBox(RenderWindow *_window, Font &_font, Vector2f _position = Vector2f(), Vector2f _size = Vector2f(10.0f, 10.0f), String _string = String(L""), Color _color = Color::White);

	// Setters for Position, Size, Text, and Visibility
	void SetPosition(Vector2f _position);
	void SetSize(Vector2f _size);
	void SetString(String _string);
	void SetColor(Color _color);
	void SetVisible(bool _visible);
	void SetCentered(bool _centered);
	void CenterString();

	// Getters for Visibility
	bool GetVisible();

	// Draw the two rectangles and text to the referenced window
	virtual void Draw();
};

#endif // !TEXTBOX_H
