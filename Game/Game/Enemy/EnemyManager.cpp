#include "stdafx.h"
#include "EnemyManager.h"
#include"level/Level.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}
bool EnemyManager::Load()
{
	int kuku = 0;
	Level level;
	level.Init(L"Assets/level/Enemy_lever03.tkl", [&](LevelObjectData objData)
	{
		//�Ƃ肠�����v���C���[��
		auto No = wcscmp(objData.name, (L"unityChan"));
		if (No == 0) {
			m_player->SetPosition(objData.position);
			return true;
		}
		else {
			kuku++;
			if (kuku != 2) {
				//�f�o�b�N�p����
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