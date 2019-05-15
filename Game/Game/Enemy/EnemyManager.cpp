#include "stdafx.h"
#include "EnemyManager.h"
#include"level/Level.h"
#include "title.h"
#include"Status.h"
#include"ItemManager.h"

const int Boss = 30;
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
void EnemyManager::Comeback()
{
	m_timer->TimerRestart();
}
bool EnemyManager::Load()
{
	//ここでは経路探査しないで！！
	m_timer->TimerStart();
	auto mode = g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"Assets/level/Enemy_lever0%d.tkl", (int)(mode->GetMode())*4);
	m_player = g_objectManager->FindGO<Player>("player");
	Level level;
	int Lance_count = 0;
	int hero_count = 0;
	int nait_count = 0;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{

		auto name = objData.name;
		auto No = wcscmp(name, (L"Bricks"));
		if (No == 0) {
			m_spawnpos.push_back(objData.position);
			return true;
		}
		else
		{
			if (0==wcscmp(name, (L"enemy_Lance"))) {
				SpawnEnemy(objData.position, new enemy_Lance, Lance_count);
				Lance_count++;	
			}
			else if(0==wcscmp(name, (L"enemy_hero")))
			{
				SpawnEnemy(objData.position, new enemy_hero, hero_count);
				hero_count++;
			}
			else if (0==wcscmp(name, (L"enemy_nait")))
			{
				SpawnEnemy(objData.position, new enemy_nait, nait_count);
				nait_count++;
			}
			return true;
		}
	});
	return true;
}
void EnemyManager::Update()
{
	//ここで湧き処理
	m_timer->TimerStop();
	//十秒経過したら
	if (m_timer->GetAllSeconds()>=10.0f)
	{		

		//沸きの上限に達していなければ
		if (m_Maxsporn >= m_enemy.size()) {

				m_No = ++m_No % m_spawnpos.size();
				SpawnEnemy(m_spawnpos[m_No], new enemy_hero);	//スポーン
		}
		m_timer->TimerStart();	
		for (auto enemy : m_enemy)
		{
			enemy->Stop_count();
		}

	}
	else {
		m_timer->TimerRestart();
	}
	if(m_BossSpoon==false&&m_Score->GetNum()>= Boss) {
		SpawnEnemy(m_spawnpos[m_spawnpos.size() - 1], new mking);	//ボスのスポーン
		m_BossSpoon = true;
	}
	//ここからエネミーのdelete処理
	for (auto enemy = m_enemy.begin(); enemy != m_enemy.end();)
	{
		if (!(*enemy)->Getlife())
		{
			//死んでいるのでdelete
			g_objectManager->FindGO<ItemManager>("item")->SpawnItem((*enemy)->GetPosition());
			g_objectManager->DereteGO(*enemy);

			enemy = m_enemy.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}

}
void EnemyManager::SpawnEnemy(CVector3 pos,Ability* k,int count)
{ 
	auto Spawn_enemy = g_objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader");
	Spawn_enemy->SetPosition(pos);
	Spawn_enemy->SetStatus(k);
	Spawn_enemy->SetScore(m_Score);
	Spawn_enemy->SetPlayer(m_player);
	Spawn_enemy->ChangeGroup_stop(count);
	m_enemy.push_back(Spawn_enemy);
}