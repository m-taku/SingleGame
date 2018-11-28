#include "stdafx.h"
#include "Game.h"
#include"level/Level.h"
#include"UI.h"
#include"Enemy/EnemyManager.h"
#include"Enemy/Enemy.h"
#include"Player/Player.h"
#include"title.h"
#include"Gamecamera.h"
#include"Stage.h"

Game::Game()
{
}
Game::~Game()
{
	g_objectManager->NewGO<title>(0);
}
void Game::OnDestroy()
{
	g_objectManager->Release();
}
bool Game::Load()
{
	//デバック用の変数（１部隊だけ出したい）
	//Level level;
	m_player = g_objectManager->NewGO<Player>(GameObjectPriority_Player);	
	m_camera = g_objectManager->NewGO<Gamecamera>(GameObjectPriority_Camera);
	m_camera->SetPlayer(m_player);
	m_player->SetCamera(m_camera);
	g_objectManager->NewGO<Stage>(GameObjectPriority_Default);
	auto ka= g_objectManager->NewGO<EnemyManager>(GameObjectPriority_Default);
	ka->SetPlayer(m_player);
	//level.Init(L"Assets/level/Enemy_lever03.tkl", [&](LevelObjectData objData)
	//{
	//	auto No = wcscmp(objData.name, (L"unityChan"));
	//	if (No == 0) {
	//		m_player->SetPosition(objData.position);
	//		return true;
	//	}
	//	else {
	//		kuku++;
	//		if (kuku != 2) {
	//			//デバック用判定
	//			return true;
	//		}
	//		//auto pos = objData.position;
	//		enemy->SetPosition(objData.position);
	//		enemy->SetPlayer(m_player);
	//		return true;
	//	}
	//});

	return true;
}
void Game::Update()
{
	if (g_pad[0].IsPress(enButtonLB3))
	{
		g_objectManager->DereteGO(this);
	}
}
void Game::Draw()
{

}