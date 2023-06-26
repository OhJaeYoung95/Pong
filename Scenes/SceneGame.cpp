#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"
#include "PlayerGo.h"
#include "TextGo.h"
#include "BallGo.h"

SceneGame::SceneGame() : Scene(SceneId::Game), score(0), life(3)
{
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));
}

void SceneGame::Init()
{
	Release();
	//RESOURCE_MGR.Load(resources);
	AddGo(new TextGo("Score"));
	AddGo(new TextGo("Life"));
	AddGo(new PlayerGo("Player"));
	AddGo(new BallGo("Ball"));

	//AddGo(new PlayerGo("Player"));
	//player.setSize(sf::Vector2f(50.f, 50.f));
	//player.setFillColor(sf::Color::Red);
	//player.setPosition(FRAMEWORK.GetWindowSize());
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	//RESOURCE_MGR.Unload(resources);
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}

}

void SceneGame::Enter()
{
	Scene::Enter();

	life = 3;
	score = 0;

	auto text = (TextGo*)FindGo("Score");
	text->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	text->text.setString("SCORE: ");
	text->text.setFillColor(sf::Color::Blue);
	text->text.setOutlineThickness(5);
	text->text.setOutlineColor(sf::Color::White);
	text->text.setCharacterSize(60);
	text->SetOrigin(Origins::TL);
	text->SetPosition(sf::Vector2f(50.f, 50.f));
	text->sortLayer = 0;

	text = (TextGo*)FindGo("Life");
	text->text.setFont(*RESOURCE_MGR.GetFont("fonts/DS-DIGI.ttf"));
	text->text.setString("LIFE: ");
	text->text.setFillColor(sf::Color::Blue);
	text->text.setOutlineThickness(5);
	text->text.setOutlineColor(sf::Color::White);
	text->text.setCharacterSize(60);
	text->SetOrigin(Origins::TL);
	text->SetPosition(sf::Vector2f(330.f, 50.f));
	text->sortLayer = 0;

	auto player = (PlayerGo*)FindGo("Player");
	player->player.setSize(sf::Vector2f(100.f, 15.f));
	player->SetOrigin(Origins::BC);
	player->SetPosition(sf::Vector2f(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y - 20.f));
	player->sortLayer = 0;

	auto ball = (BallGo*)FindGo("Ball");
	ball->ball.setRadius(10.f);
	ball->SetOrigin(Origins::BC);
	sf::Vector2f test = player->GetPosition();
	ball->ball.setPosition(player->GetPosition().x, player->GetPosition().y - 15.f);
	ball->SetPlayer(player);
	ball->SetGame(this);
	//ball->SetPosition(sf::Vector2f(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y - 20.f));
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}

	//if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	//{
	//	score++;
	//	life--;
	//}

	if (life == 0)
	{
		SCENE_MGR.ChangeScene(SceneId::Game);
	}

	std::stringstream strS;
	strS << "SCORE: " << score;
	auto text = (TextGo*)FindGo("Score");
	text->text.setString(strS.str());
	
	std::stringstream strL;
	strL << "LIFE: " << life;
	text = (TextGo*)FindGo("Life");
	text->text.setString(strL.str());
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}
