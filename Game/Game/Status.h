#pragma once
/// <summary>
/// ステータスを決定するクラス群
/// </summary>
#include "Ability.h"
class Enemy;
class EnemyManager;
/// <summary>
/// モデルenemy_heroのステータス
/// </summary>
struct enemy_hero : public Ability
{
	enemy_hero()
	{
		//基底クラスを初期化する
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);		
		SetWeaponSize(Size);
		ka.AttackPriority =100.0f;
		ka.DefensePriority = 0.0f;
		ka.freedomPriority = 0.0f;
		SetEnemy_Priority(&ka);
	}
	float HP = 50.0f;						//基本のHP
	float Attack = 20.0f;					//基本の攻撃力
	float Defense = 5.0f;				    //基本の守備力
	float Speed = 200.0f;					//基本のスピード	
	int Spawnnum = 5;						//初期スポーンの数
	CVector3 Size = { 10.0f, 10.0f,60.0f };	
	Enemy_ActionPriority ka;
	wchar_t* Name = L"enemy_hero";     		//ステータスを適応するモデルの名前
};
/// <summary>
/// モデルenemy_naitのステータス
/// </summary>
struct enemy_nait : public Ability
{
	enemy_nait();
	~enemy_nait()
	{
		delete m_timer;
	}
	void Individuality(void* point) override;
	float HP = 30.0f;						//基本のHP
	float Attack = 30.0f;					//基本の攻撃力
	float Defense = 19.0f;					//基本の守備力
	float Speed = 50.0f;					//基本のスピード
	int Spawnnum = 3;						//初期スポーンの数
	Enemy_ActionPriority ka;
	CVector3 Size = { 10.0f, 10.0f,60.0f };
	wchar_t* Name = L"enemy_nait";     		//ステータスを適応するモデルの名前
private:
	EnemyManager * m_enemymanager = nullptr;
	Timer* m_timer = nullptr;
};
/// <summary>
/// モデルenemy_Lanceのステータス
/// </summary>
struct enemy_Lance : public Ability
{
	enemy_Lance()
	{
		//基底クラスを初期化する
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);
		ka.AttackPriority = 70.0f;
		ka.DefensePriority = 30.0f;
		ka.freedomPriority = 0.0f;
		SetEnemy_Priority(&ka);
		SetWeaponSize(Size);
	}
	float HP = 50.0f;						//基本のHP
	float Attack = 15.0f;					//基本の攻撃力
	float Defense = 7.5f;					//基本の守備力
	float Speed = 100.0f;					//基本のスピード
	int Spawnnum = 3;						//初期スポーンの数
	Enemy_ActionPriority ka;
	CVector3 Size = { 10.0f, 10.0f,100.0f };
	wchar_t* Name = L"enemy_Lance";     	//ステータスを適応するモデルの名前
};
/// <summary>
/// モデルmkingのステータス
/// </summary>
struct mking : public Ability
{
	mking()
	{
		//基底クラスを初期化する
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);
		ka.AttackPriority = 100.0f;
		ka.DefensePriority = 0.0f;
		ka.freedomPriority = 0.0f;
		SetEnemy_Priority(&ka);
		SetWeaponSize(Size);
	}
	void Individuality(void* point)
	{

	}
	float HP = 100.0f;						//基本のHP
	float Attack = 20.0f;					//基本の攻撃力
	float Defense = 15.0f;					//基本の守備力
	float Speed = 100.0f;					//基本のスピード
	int Spawnnum = 1;						//初期スポーンの数
	Enemy_ActionPriority ka;
	CVector3 Size = { 10.0f, 10.0f,90.0f };
	wchar_t* Name = L"mking";     			//ステータスを適応するモデルの名前
};
/// <summary>
/// モデルPlayerのステータス
/// </summary>
struct PlyerStatus : public Ability
{
	PlyerStatus()
	{
		//基底クラスを初期化する
		SetHP(HP);
		SetMP(MP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetWeaponSize(Size);
	}
	float HP = 500.0f;						//最大のHP
	float MP = 100.0f;						//最大のMP
	float Attack = 20.0f;					//基本の攻撃力
	float Defense = 10.0f;					//基本の守備力
	float Speed = 400.0f;					//基本のスピード
	int Spawnnum = 1;						//初期スポーンの数
	CVector3 Size = { 10.0f,10.0f,80.0f };	//
	wchar_t* Name = L"Player";     			//ステータスを適応するモデルの名前
};