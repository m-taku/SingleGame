#include "stdafx.h"
#include "Game.h"
#include"UI.h"
#include"Enemy/EnemyManager.h"
#include"HitObjict.h"
#include"Gameover.h"
#include"Enemy.h"
#include"Player.h"
#include"Gamecamera.h"
#include"Stage.h"
#include "Friend/FriendManager.h"
#include"ItemManager.h"
Game::Game()
{
}
Game::~Game()
{

}
void Game::OnDestroy()
{
	//持っているすべてのインスタンスを削除
	g_objectManager->DereteGO(m_camera);
	g_objectManager->DereteGO(m_stage);
	g_objectManager->DereteGO(m_player);
	g_objectManager->DereteGO(m_ui);
	g_objectManager->DereteGO(m_enemyManager);
	g_objectManager->DereteGO(m_score); 
	g_objectManager->DereteGO(m_item);
	GetHitObjict().Release();
}
bool Game::Load()
{
	//げーむのすべてのインスタンスを発生
	m_player = g_objectManager->NewGO<Player>(GameObjectPriority_Player,"player");	
	m_camera = g_objectManager->NewGO<Gamecamera>(GameObjectPriority_Camera);
	m_ui = g_objectManager->NewGO<UI>(GameObjectPriority_Default,"UI");
	m_score = g_objectManager->NewGO<Score>(GameObjectPriority_Default,"Score");
	m_stage = g_objectManager->NewGO<Stage>(GameObjectPriority_Default);
	m_enemyManager = g_objectManager->NewGO<EnemyManager>(GameObjectPriority_EnemyLeader,"EnemyManager");
	//auto m = g_objectManager->NewGO<FriendManager>(GameObjectPriority_EnemyLeader);
	m_camera->SetPlayer(m_player);
	m_player->SetCamera(m_camera); 
	m_ui->SetScore(m_score);
	m_item = g_objectManager->NewGO<ItemManager>(GameObjectPriority_Default,"item");
	m_enemyManager->SetPlayer(m_player);
	m_enemyManager->SetScore(m_score);
	//m->SetScore(m_score);
	return true;
}
void Game::Update()
{
	//if (m_lood ==false && m_enemyManager->GetLodefrag())

}
void Game::PostDraw()
{

}