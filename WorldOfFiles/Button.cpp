#include "pch.h"
#include "UI/Button.h"

Button::Button()
	: TextBox()
{
}

Button::Button(RenderWindow * _window, Font & _font, Vector2f _position, Vector2f _size, String _string, Color _color)
	: TextBox(_window, _font, _position, _size, _string, _color)
{
	isInteractable = true;
	SetVisible(false);
	SetCentered(false);

}

void Button::SetInteractable(bool _interactable)
{
	isInteractable = _interactable;
}

bool Button::IsInside(Vector2i _position)
{
	if (isInteractable &&
		_position.x > position.x && _position.x < position.x + size.x &&
		_position.y > position.y && _position.y < position.y + size.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::Draw()
{
	if (GetVisible())
	{
		if (isInteractable)
		{
			TextBox::Draw();
		}
		else
		{
			SetBackColor(Color(20, 20, 20));
			TextBox::Draw();
			SetBackColor(Color::Black);
		}
	}
}
