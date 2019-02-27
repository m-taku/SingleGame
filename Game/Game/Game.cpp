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
}
void Game::OnDestroy()
{
	g_objectManager->DereteGO(m_camera);
	g_objectManager->DereteGO(m_stage);
	g_objectManager->DereteGO(m_player);
	g_objectManager->DereteGO(m_ui);
	g_objectManager->DereteGO(m_enemyManager);
	g_objectManager->DereteGO(m_score);
	g_HitObjict->Release();
}
bool Game::Load()
{
	m_player = g_objectManager->NewGO<Player>(GameObjectPriority_Player,"player");	
	m_camera = g_objectManager->NewGO<Gamecamera>(GameObjectPriority_Camera);
	m_ui = g_objectManager->NewGO<UI>(GameObjectPriority_Default,"UI");
	m_score = g_objectManager->NewGO<Score>(GameObjectPriority_Default);
	m_stage = g_objectManager->NewGO<Stage>(GameObjectPriority_Default);
	m_enemyManager = g_objectManager->NewGO<EnemyManager>(GameObjectPriority_EnemyLeader);
	m_camera->SetPlayer(m_player);
	m_player->SetCamera(m_camera);
	m_ui->SetScore(m_score);
	//m_score->SetUI(m_ui);
	m_enemyManager->SetPlayer(m_player);
	m_enemyManager->SetScore(m_score);
	return true;
}
void Game::Update()
{

}
void Game::Draw()
{

}