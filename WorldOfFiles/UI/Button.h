#ifndef BUTTON_H
#define BUTTON_H

#include "TextBox.h"

class Button : public TextBox {

private:
	// Can button be interacted with?
	bool isInteractable;

public :
	// Constuctor
	Button();
	Button(RenderWindow *_window, Font &_font, Vector2f _position = Vector2f(), Vector2f _size = Vector2f(10.0f, 10.0f), String _string = String(L""), Color _color = Color::White);

	// 
	void SetInteractable(bool _interactable);
	void CenterString();
	
	// Interactive Funtions
	bool IsInside(Vector2i _position);

	// Inherited Draw function to add interactability
	virtual void Draw();
};

#endif // !BUTTON_H
