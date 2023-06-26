#pragma once
#include "GameObject.h"

class PlayerGo;
class SceneGame;

class BallGo : public GameObject
{
public:
	sf::CircleShape ball;
	sf::Vector2f dir;
	float ballSpeed;
	PlayerGo* player;
	float x;
	float y;

	SceneGame* game;
	
	sf::Vector2f mapMaxSize;
	sf::Vector2f mapMinSize;
	bool isBounce;
	bool isCol;		// 다중 충돌 방지
	bool isScoreP;	// 벽 하나만 점수 오르도록

	BallGo(const std::string n = "");
	virtual ~BallGo() override;

	virtual void SetPosition(const sf::Vector2f& p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);


	virtual void Init() override;	// 생성자 new 역할
	virtual void Release() override;	// 소멸자 delete 역할
	virtual void Reset() override;	// 값 세팅

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetPlayer(PlayerGo*& player);
	void SetGame(SceneGame* game);

};

