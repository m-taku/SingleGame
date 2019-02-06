#include "stdafx.h"
#include "EnemyManager.h"
#include"level/Level.h"
#include "title.h"


EnemyManager::EnemyManager()
{
	m_timer = new Timer;
}


EnemyManager::~EnemyManager()
{
	for (auto enemy = m_enemy.begin(); enemy != m_enemy.end();)
	{
		g_objectManager->DereteGO(*enemy);
		enemy = m_enemy.erase(enemy);
	}
	delete m_timer;
}
bool EnemyManager::Load()
{
	//ここでは経路探査しないで！！
	m_timer->TimerStart();
	auto mode = g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"Assets/level/Enemy_lever0%d.tkl", 5-mode->Getmode());
	m_player = g_objectManager->FindGO<Player>("player");
	Level level;
	int hoge = 0;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{
		//とりあえずプレイヤーも
		auto No = wcscmp(objData.name, (L"unityChan"));
		if (No == 0) {
			m_player->SetPosition(objData.position/*{0.0f,0.0f,0.0f}*//*{ -14203.2344f,403.032990f,-6998.72070f}*/);
			return true;
		}
		No = wcscmp(objData.name, (L"Bricks")); 
		if(No == 0){
			m_spawnpos.push_back(objData.position);
			return true;
		}
		else
		{
			if (++hoge <= 1) {
				SpawnEnemy(objData.position,L"Assets/modelData/ToonRTS_demo_Knight.cmo");
			}
			return true;
		}
	});
	m_No = 0;
	return true;
}
void EnemyManager::Update()
{
	//ここで湧き処理したい
	m_timer->TimerStop();
	if (m_timer->GetAllSeconds()>=1000.0f)
	{
		if (m_No <m_enemy.size()) {
			m_No = (m_No + 1) % 2;
			SpawnEnemy(m_spawnpos[m_No], L"Assets/modelData/ToonRTS_demo_Knight.cmo");
			m_timer->TimerStart();
		}
	}
	for (auto enemy = m_enemy.begin(); enemy != m_enemy.end();)
	{
		if (!(*enemy)->Getlife())
		{
			g_objectManager->DereteGO(*enemy);
			enemy = m_enemy.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}
}
void EnemyManager::SpawnEnemy(CVector3 pos,const wchar_t* fileName)
{ 
	m_enemy.push_back(g_objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader"));
	auto No = m_enemy.size() - 1;
	m_enemy[No]->SetPosition(pos);
	m_enemy[No]->SetfileName(fileName);
	m_enemy[No]->SetPlayer(m_player);
}