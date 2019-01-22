#include "stdafx.h"
#include "Game.h"
#include"level/Level.h"
#include"UI.h"
#include"Enemy/EnemyManager.h"
#include"HitObjict.h"
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
	//g_objectManager->NewGO<title>(0);
}
void Game::OnDestroy()
{
	//g_objectManager->Release();
	delete m_hitobjict;
}
bool Game::Load()
{
	m_hitobjict = new HitObjict;
	m_player = g_objectManager->NewGO<Player>(GameObjectPriority_Player,"player");	
	m_camera = g_objectManager->NewGO<Gamecamera>(GameObjectPriority_Camera);
	m_camera->SetPlayer(m_player);
	m_player->SetCamera(m_camera);
	m_player->Sethit(m_hitobjict);
	g_objectManager->NewGO<Stage>(GameObjectPriority_Default);
	auto Enemy = g_objectManager->NewGO<EnemyManager>(GameObjectPriority_EnemyLeader);
	Enemy->SetPlayer(m_player);
	Enemy->Sethit(m_hitobjict);
	return true;
}
void Game::Update()
{
}
void Game::Draw()
{

}