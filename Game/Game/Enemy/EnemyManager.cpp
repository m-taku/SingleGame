#include "stdafx.h"
#include "EnemyManager.h"
#include"level/Level.h"
#include "title.h"
#include"Status.h"
#include"ItemManager.h"
#include <random>

const int BossCount = 100;
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
	int Lance_count = 2;
	int hero_count = 0;
	int nait_count = 1000;
	level.Init(moveFilePath, [&](LevelObjectData objData)
	{
		auto name = objData.name;
		auto No = wcscmp(name, (L"Bricks"));
		if (No == 0) {
			m_spawnpos.push_back(objData.position);
		}
		else if (0 == wcscmp(name, (L"enemy_Lance"))) {
			SpawnEnemy(objData.position, new enemy_Lance, objData.rotation, Lance_count);
			Lance_count+=2;
		}
		else if (0 == wcscmp(name, (L"enemy_hero")))
		{
			SpawnEnemy(objData.position, new enemy_hero, objData.rotation, (int)hero_count/4);
			hero_count++;
		}
		else if (0 == wcscmp(name, (L"enemy_nait")))
		{

			SpawnEnemy(objData.position, new enemy_nait, objData.rotation, nait_count);
			nait_count++;

		}
		else if (0 == wcscmp(name, (L"player1")))
		{
			auto pos = objData.position;
			pos.y = 100.0;
			m_player->SetPosition(pos);
		}
		return true;
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
		for (auto enemy : m_enemy)
		{
			enemy->Stop_count();
		}
		m_timer->TimerStart();

	}
	else {
		m_timer->TimerRestart();
	}
	if(m_BossSpoon == false && m_Score->GetNum() >= BossCount) {
		SpawnEnemy(m_spawnpos[m_spawnpos.size() - 1], new mking);	//ボスのスポーン
		m_BossSpoon = true;
	}
	//ここからエネミーのdelete処理
	for (auto enemy = m_enemy.begin(); enemy != m_enemy.end();)
	{
		if (!(*enemy)->Getlife())
		{
			//死んでいるのでdelete
			std::random_device rnd;     // 非決定的な乱数生成器を生成
			std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
			std::uniform_int_distribution<> rand2(0,1);        // [0, 99] 範囲の一様乱数
			int No = rand2(mt);
			if (No) {
				g_objectManager->FindGO<ItemManager>("item")->SpawnItem((*enemy)->GetPosition());
			}
			g_objectManager->DereteGO(*enemy);
			enemy = m_enemy.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}

}
void EnemyManager::SpawnEnemy(CVector3 pos, Ability* ability, CQuaternion angle,int count)
{ 
	auto Spawn_enemy = g_objectManager->NewGO<Enemyleader>(GameObjectPriority_EnemyLeader, "Enemyleader");
	Spawn_enemy->SetPosition(pos);
	Spawn_enemy->SetAngle(angle);
	Spawn_enemy->SetStatus(ability);
	Spawn_enemy->SetScore(m_Score);
	Spawn_enemy->SetPlayer(m_player);
	Spawn_enemy->ChangeGroup_stop(count);
	m_enemy.push_back(Spawn_enemy);
}