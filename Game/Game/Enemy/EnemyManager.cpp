#include "stdafx.h"
#include "EnemyManager.h"
#include"level/Level.h"
#include "Item.h"
#include "title.h"
#include"Status.h"


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
	//‚±‚±‚Å‚ÍŒo˜H’T¸‚µ‚È‚¢‚ÅII
	m_timer->TimerStart();
	auto mode = g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"Assets/level/Enemy_lever0%d.tkl", (int)(mode->Getmode())*4);
	m_player = g_objectManager->FindGO<Player>("player");
	Level level;
	int hoge = 0;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{
		////‚Æ‚è‚ ‚¦‚¸ƒvƒŒƒCƒ„[‚à
		auto No = wcscmp(objData.name, (L"unityChan"));
		if (No == 0) {
			m_player->SetPosition(/*objData.position*/{ 0.0f,0.0f,0.0f }/*{ -14203.2344f,403.032990f,-6998.72070f}*/);
			return true;
		}
		No = wcscmp(objData.name, (L"Bricks"));
		if (No == 0) {
			m_spawnpos.push_back(objData.position);
			return true;
		}
		else
		{
			if (hoge <= 1) {
				SpawnEnemy(objData.position,new enemy_Lance);
			}
			return true;
		}
	});
	m_No = 0;
	return true;
}
void EnemyManager::Update()
{
	//‚±‚±‚Å—N‚«ˆ—‚µ‚½‚¢
	m_timer->TimerStop();
	if (m_timer->GetAllSeconds()>=10.0f)
	{
		if (m_Maxsporn >=m_enemy.size()) {
			m_No = (m_No + 1) % 2;
			SpawnEnemy(m_spawnpos[m_No], new enemy_hero);
		}			
		m_timer->TimerStart();
	}
	for (auto enemy = m_enemy.begin(); enemy != m_enemy.end();)
	{
		if (!(*enemy)->Getlife())
		{
			g_objectManager->DereteGO(*enemy);
			//auto item = g_objectManager->NewGO<Item>(GameObjectPriority_Default, "Item");
			//item->SetPosition((*enemy)->GetPosition());
			enemy = m_enemy.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}
}
void EnemyManager::SpawnEnemy(CVector3 pos,Ability* k)
{ 
	m_enemy.push_back(g_objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader"));
	auto No = m_enemy.size() - 1;
	m_enemy[No]->SetPosition(pos);
	m_enemy[No]->SetStatus(k);
	m_enemy[No]->SetScore(m_Score);
	m_enemy[No]->SetPlayer(m_player);
}