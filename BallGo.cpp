#include "stdafx.h"
#include "BallGo.h"
#include "InputMgr.h"
#include "Framework.h"
#include "PlayerGo.h"
#include "SceneGame.h"

BallGo::BallGo(const std::string n)
	: GameObject(n),
	dir(1.0f, -1.0f), x(500), y(500), isBounce(false), ballSpeed(500.f),
	mapMaxSize(FRAMEWORK.GetWindowSize()), mapMinSize(0, 0), isScoreP(false), isCol(false)
{
}

BallGo::~BallGo()
{
}

void BallGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	ball.setPosition(p);
}

void BallGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	ball.setPosition(position);
}

void BallGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(ball, origin);
	}
}

void BallGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x, y);
	ball.setOrigin(x, y);
}

void BallGo::Init()
{
}

void BallGo::Release()
{
}

void BallGo::Reset()
{
	//x = player->x;
	//y = player->y - 15.f;	// 15 는 플레이어 바 y사이즈
	//ball.setPosition(x, y);
	isBounce = false;
	isScoreP = false;
	isCol = false;
	dir = { 1.f, -1.f };
}

void BallGo::Update(float dt)
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && !isBounce)
	{
		isBounce = true;
	}

	if (!isBounce)
	{
		x = player->x;
		y = player->y - 15.f;	// 15 는 플레이어 바 y사이즈
		ball.setPosition(x, y);
	}
	else
	{
		y += ballSpeed * dt * dir.y;
		x += ballSpeed * dt * dir.x;
		ball.setPosition(x, y);
	}

	// 벽 충돌시
	if (x >= mapMaxSize.x)
	{
		isCol = true;	// 다중 충돌 방지
		if (isCol)
		{
			dir.x *= -1;
			if (!isScoreP)		// 벽 하나만 점수 오르도록
				game->score++;
			isScoreP = true;
		}
		isCol = false;
	}
	if (x <= mapMinSize.x)
	{
		isCol = true;
		if (isCol)
		{
		dir.x *= -1;
		if (!isScoreP)
			game->score++;
		isScoreP = true;
		}
		isCol = false;
	}
	if (y <= mapMinSize.y)
	{
		isCol = true;
		if (isCol)
		{
		dir.y *= -1;
		if (!isScoreP)
			game->score++;
		isScoreP = true;
		}
		isCol = false;
	}
	if (y >= mapMaxSize.y)
	{
		game->life--;
		Reset();
	}

	// 플레이어 충돌시
	sf::FloatRect playerCol = player->player.getGlobalBounds();
	sf::FloatRect ballCol = ball.getGlobalBounds();
	if (ballCol.intersects(playerCol))
	{
		isScoreP = false;
		dir.y *= -1;
	}
}

void BallGo::Draw(sf::RenderWindow& window)
{
	window.draw(ball);
}

void BallGo::SetPlayer(PlayerGo*& player)
{
	this->player = player;
}

void BallGo::SetGame(SceneGame* game)
{
	this->game = game;
}
