#include "stdafx.h"
#include "PlayerGo.h"
#include "InputMgr.h"
#include "Framework.h"

PlayerGo::PlayerGo(const std::string n) 
	: GameObject(n),
	x(FRAMEWORK.GetWindowSize().x * 0.5f),
	y(FRAMEWORK.GetWindowSize().y - 20.f),
	mapSizeX(FRAMEWORK.GetWindowSize().x)
{
}

PlayerGo::~PlayerGo()
{
}

void PlayerGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	player.setPosition(p);
}

void PlayerGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	player.setPosition(position);
}

void PlayerGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(player, origin);
	}
}

void PlayerGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	player.setOrigin(x, y);
}

void PlayerGo::Init()
{
}

void PlayerGo::Release()
{
}

void PlayerGo::Reset()
{
	x = FRAMEWORK.GetWindowSize().x * 0.5f;
	y = FRAMEWORK.GetWindowSize().y - 20.f;

	player.setPosition(x, y);
}

void PlayerGo::Update(float dt)
{
	if (INPUT_MGR.GetKey(sf::Keyboard::A) && x > 0 + 50.f)
	{
		x -= 1;
		player.setPosition(x, y);
	}	
	if (INPUT_MGR.GetKey(sf::Keyboard::D) && x < mapSizeX - 50.f)
	{
		x += 1;
		player.setPosition(x, y);

	}
}

void PlayerGo::Draw(sf::RenderWindow& window)
{
	window.draw(player);
}