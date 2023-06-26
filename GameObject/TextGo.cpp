#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo(const std::string n) : GameObject(n)
{
}

TextGo::~TextGo()
{
}

void TextGo::SetPosition(const sf::Vector2f p)
{
	position = p;
	text.setPosition(p);
}

void TextGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	text.setPosition(position);
}

void TextGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(text, origin);
	}
}

void TextGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	text.setOrigin(x, y);
}

void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::Reset()
{
}

void TextGo::Update(float dt)
{
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
