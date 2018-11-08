#include "stdafx.h"
#include "Game.h"
#include"level/Level.h"
#include"UI.h"
#include"Stage.h"
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
	objectManager->NewGO<Stage>(0);
	//ゲームループ。
	player = objectManager->NewGO<Player>(1);
	Camera = objectManager->NewGO<Gamecamera>(10);
	Camera->SetPlayer(player);
	player->SetCamera(Camera);
	static int kuku = 0;
	Level level;
	level.Init(L"Assets/level/Enemy_lever00.tkl", [&](LevelObjectData objData)
	{
		//kuku++;
		//if (kuku != 2) {
		//	return true;

		//}
		Enemyleader* enemy = objectManager->NewGO<Enemyleader>(1, "Enemyleader");
		auto pos = objData.position;

		enemy->Setposition(pos);
		enemy->Setplayer(player);
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