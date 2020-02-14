#include "pch.h"
#include "UI/TextBox.h"

TextBox::TextBox()
{
	window = nullptr;
}

TextBox::TextBox(RenderWindow * _window, Font &_font, Vector2f _position, Vector2f _size, String _string, Color _color)
{
	window = _window;
	isVisible = true;
	isCentered = false;

	outsideBox = RectangleShape(_size);
	outsideBox.setFillColor(Color::Black);
	outsideBox.setOutlineThickness(4);

	insideBox = RectangleShape(_size - Vector2f(10,10));
	insideBox.setFillColor(Color::Transparent);
	insideBox.setOutlineThickness(3);
	
	text = Text(_string, _font, 24);
	text.setStyle(sf::Text::Regular);

	SetPosition(_position);
	SetSize(_size);
	SetColor(_color);
}

void TextBox::SetPosition(Vector2f _position)
{
	position = _position;
	outsideBox.setPosition(position + Vector2f(10, 10));
	insideBox.setPosition(position + Vector2f(15, 15));
	if (isCentered)
		CenterString();
	else
		text.setPosition(position + Vector2f(25, 25));
}

void TextBox::SetSize(Vector2f _size)
{
	size = _size;
	outsideBox.setSize(_size - Vector2f(20, 20));
	insideBox.setSize(_size - Vector2f(30, 30));

	SetString(text.getString());
}

void TextBox::SetString(String _string)
{
	String stringBlock = _string;
	/* TODO, break string if line if too long
	unsigned int minLength = (text.getCharacterSize() * stringBlock.getSize());
	printf("%d - ", minLength);
	printf("%f\n", insideBox.getSize().x);

	if (true)
	{
		String line = _string;

	}
	//*/
	text.setString(stringBlock);
}

void TextBox::SetColor(Color _color)
{
	outsideBox.setOutlineColor(_color);
	insideBox.setOutlineColor(_color);
	text.setFillColor(_color);
}

void TextBox::SetVisible(bool _visible)
{
	isVisible = _visible;
}

void TextBox::SetCentered(bool _centered)
{
	isCentered = _centered;
}

void TextBox::SetBackColor(Color _color)
{
	outsideBox.setFillColor(_color);
}

void TextBox::SetTextPosition(Vector2f _position)
{
	text.setPosition(_position);
}

Text TextBox::GetText()
{
	return text;
}

bool TextBox::GetVisible()
{
	return isVisible;
}

void TextBox::CenterString()
{
	Vector2f centered = position;
	centered.x += size.x / 2;
	centered.y += size.y / 2;

	String buttonString = GetText().getString();
	if (buttonString.getSize() > 0)
	{
		int charSize = GetText().getCharacterSize();
		centered.x -= buttonString.getSize() * charSize / 3;
		centered.y -= charSize / 2;
	}

	SetTextPosition(centered);
}

void TextBox::Draw()
{
	if (isVisible && window != nullptr)
	{
		window->draw(outsideBox);
		window->draw(insideBox);
		window->draw(text);
	}
}
