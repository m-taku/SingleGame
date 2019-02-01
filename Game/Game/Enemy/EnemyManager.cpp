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
	m_timer->TimerStart();
	int kuku = 0;
	auto mode = g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"Assets/level/Enemy_lever0%d.tkl", 5-mode->Getmode());
	m_player = g_objectManager->FindGO<Player>("player");
	Level level;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{
		//‚Æ‚è‚ ‚¦‚¸ƒvƒŒƒCƒ„[‚à
		auto No = wcscmp(objData.name, (L"unityChan"));
		if (No == 0) {
			m_player->SetPosition(objData.position/*{0.0f,0.0f,0.0f}*//*{ -14203.2344f,403.032990f,-6998.72070f}*/);
			return true;
		}
		else {
			if (++kuku <= 3) {
				m_enemy.push_back(g_objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader"));
				auto No = m_enemy.size() - 1;
				//objData.position
				m_enemy[No]->SetPosition(objData.position);
				m_enemy[No]->Sethit(m_hit);
				m_enemy[No]->SetPlayer(m_player);

			}
			return true;
		}
	});
	return true;
}
void EnemyManager::Update()
{
	m_timer->TimerStop();
	if (m_timer->GetAllSeconds()>=60.0f)
	{
		if (m_No <m_enemy.size()) {
			m_enemy[m_No++]->ChangeGroup_state();
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