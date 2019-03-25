#include "stdafx.h"
#include "EnemyManager.h"
#include"level/Level.h"
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
	int hoge = 0;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{

		////とりあえずプレイヤーも
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
			if (hoge++ <= 1) {
				SpawnEnemy(objData.position,new enemy_Lance);
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
	//十秒立ったら
	if (m_timer->GetAllSeconds()>=10.0f)
	{
		//沸きの上限以外なら
		if (m_Maxsporn >= m_enemy.size()) {
			m_count++;
			if (m_count < 5) {
				m_No = ++m_No % m_spawnpos.size()-1;
				SpawnEnemy(m_spawnpos[m_No], new enemy_hero);	//スポーン
			}
			else
			{
				SpawnEnemy(m_spawnpos[m_spawnpos.size()-1], new mking);	//ボスのスポーン
				m_count = -114514;
			}
		}
		m_timer->TimerStart();
	}
	else {
		m_timer->TimerRestart();
	}
	//ここからエネミーのdelete処理
	for (auto enemy = m_enemy.begin(); enemy != m_enemy.end();)
	{
		if (!(*enemy)->Getlife())
		{
			//死んでいるのでdelete
			g_objectManager->DereteGO(*enemy);

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
	auto Spawn_enemy = g_objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader");
	Spawn_enemy->SetPosition(pos);
	Spawn_enemy->SetStatus(k);
	Spawn_enemy->SetScore(m_Score);
	Spawn_enemy->SetPlayer(m_player);
	m_enemy.push_back(Spawn_enemy);
}