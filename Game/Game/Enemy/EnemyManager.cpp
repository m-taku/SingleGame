#include "stdafx.h"
#include "EnemyManager.h"
#include"level/Level.h"
#include "title.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}
bool EnemyManager::Load()
{
	int kuku = 0;
	auto mode = g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"Assets/level/Enemy_lever0%d.tkl", mode->Getmode() + 3);
	m_player = g_objectManager->FindGO<Player>("player");
	Level level;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{
		//とりあえずプレイヤーも
		auto No = wcscmp(objData.name, (L"unityChan"));
		if (No == 0) {
		//	m_player->SetPosition(objData.position);
			return true;
		}
		else {
			kuku++;
			if (kuku != 2) {
				//デバック用判定
				return true;
			}
			m_enemy.push_back(g_objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader"));
			auto No=m_enemy.size()-1;
			m_enemy[No]->SetPosition(objData.position);
			m_enemy[No]->SetPlayer(m_player);
			return true;
		}
	});
	return true;
}
void EnemyManager::Update()
{

}