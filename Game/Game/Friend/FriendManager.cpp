#include "stdafx.h"
#include "FriendManager.h"
#include"level/Level.h"
#include "title.h"
#include"Status.h"
//基底クラス浮かべば実装忘れずに！！！！

FriendManager::FriendManager()
{
}


FriendManager::~FriendManager()
{
}
bool FriendManager::Load()
{
	//ここでは経路探査しないで！！
	//m_timer->TimerStart();
	auto mode = g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"Assets/level/Friend_lever0%d.tkl", (int)(mode->GetMode()) * 4);
	//m_player = g_objectManager->FindGO<Player>("player");
	Level level;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{
		//auto name = objData.name;
		//auto No = wcscmp(name, (L"Bricks"));
		//if (No == 0) {
		//	m_spawnpos.push_back(objData.position);
		//}
		//else if (0 == wcscmp(name, (L"enemy_Lance"))) {
		SpawnFriend(objData.position, new enemy_Lance);
			//Lance_count++;
		//}
		//else if (0 == wcscmp(name, (L"enemy_hero")))
		//{
		//	SpawnEnemy(objData.position, new enemy_hero, hero_count);
		//	hero_count++;
		//}
		//else if (0 == wcscmp(name, (L"enemy_nait")))
		//{

		//	SpawnEnemy(objData.position, new enemy_nait, nait_count);
		//	nait_count++;

		//}
		return true;
	});
	return true;
}
void FriendManager::Update()
{
	//ここからエネミーのdelete処理
	for (auto Friend = m_Friend.begin(); Friend != m_Friend.end();)
	{
		if (!(*Friend)->Getlife())
		{
			//死んでいるのでdelete
			g_objectManager->DereteGO(*Friend);
			Friend = m_Friend.erase(Friend);
		}
		else
		{
			Friend++;
		}
	}
}
void FriendManager::SpawnFriend(CVector3 pos, Ability* k)
{
	auto Spawn_Friend = g_objectManager->NewGO<Friendleader>(GameObjectPriority_EnemyLeader, "Friendleader");
	Spawn_Friend->SetPosition(pos);
	Spawn_Friend->SetStatus(k);
	Spawn_Friend->SetScore(m_Score);
	m_Friend.push_back(Spawn_Friend);
}
