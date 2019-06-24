#include "stdafx.h"
#include "Status.h"
#include"EnemyManager.h"

enemy_nait::enemy_nait() {
	m_timer = new Timer;
	//Šî’êƒNƒ‰ƒX‚ð‰Šú‰»‚·‚é
	SetHP(HP);
	SetAttack(Attack);
	SetDefense(Defense);
	SetSpeed(Speed);
	SetName(Name);
	SetSpawnnum(Spawnnum);
	ka.AttackPriority = 50.0f;
	ka.DefensePriority = 50.0f;
	ka.freedomPriority = 0.0f;
	SetEnemy_Priority(&ka);
	SetWeaponSize(Size);
	m_enemymanager = g_objectManager->FindGO<EnemyManager>("EnemyManager");
}
void enemy_nait::Individuality(void* point)
{
	//‚±‚±‚Å—N‚«ˆ—
	m_timer->TimerStop();
	if (m_timer->GetAllSeconds() >= 15.0f) {
		auto leader = (Enemyleader*)point;
		m_enemymanager->SpawnEnemy(leader->GetPosition());
		m_timer->TimerStart();
	}
	else
	{
		m_timer->TimerRestart();
	}

}