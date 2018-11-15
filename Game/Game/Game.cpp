#include "stdafx.h"
#include "Game.h"
#include"level/Level.h"
#include"UI.h"
#include"Enemy/EnemyLeader/Enemyleader.h"
#include"Enemy/Enemy.h"
#include"Player/Player.h"
#include"Gamecamera.h"

Game::Game()
{
}


Game::~Game()
{
}
bool Game::Load()
{

	//ゲームループ。
	player = objectManager->NewGO<Player>(GameObjectPriority_Player);
	Camera = objectManager->NewGO<Gamecamera>(GameObjectPriority_Camera);
	Camera->SetPlayer(player);
	player->SetCamera(Camera);
	static int kuku = 0;
	Level level;
	level.Init(L"Assets/level/Enemy_lever00.tkl", [&](LevelObjectData objData)
	{
		kuku++;
		if (kuku != 2) {
			return true;
		}
		Enemyleader* enemy = objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader");
		auto pos = objData.position;
		enemy->SetPosition(pos);
		enemy->SetPlayer(player);
		return true;
	});
	return true;
}
void Game::Update()
{

}
void Game::Draw()
{

}