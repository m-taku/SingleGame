#pragma once
/// <summary>
/// ステータスを決定するクラス群
/// </summary>
#include "Ability.h"
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
	}
	float HP = 50.0f;						//基本のHP
	float Attack = 20.0f;					//基本の攻撃力
	float Defense = 10.0f;				//基本の守備力
	float Speed = 200.0f;					//基本のスピード	
	int Spawnnum = 5;						//初期スポーンの数
	wchar_t* Name = L"enemy_hero";     		//ステータスを適応するモデルの名前
};
/// <summary>
/// モデルenemy_naitのステータス
/// </summary>
struct enemy_nait : public Ability
{
	enemy_nait()
	{
		//基底クラスを初期化する
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);
	}
	float HP = 30.0f;						//基本のHP
	float Attack = 50.0f;					//基本の攻撃力
	float Defense = 19.0f;					//基本の守備力
	float Speed = 50.0f;					//基本のスピード
	int Spawnnum = 1;						//初期スポーンの数
	wchar_t* Name = L"enemy_nait";     		//ステータスを適応するモデルの名前
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
	}
	float HP = 50.0f;						//基本のHP
	float Attack = 15.0f;					//基本の攻撃力
	float Defense = 10.0f;					//基本の守備力
	float Speed = 100.0f;					//基本のスピード
	int Spawnnum = 3;						//初期スポーンの数
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
	}
	float HP = 100.0f;						//基本のHP
	float Attack = 30.0f;					//基本の攻撃力
	float Defense = 10.0f;					//基本の守備力
	float Speed = 100.0f;					//基本のスピード
	int Spawnnum = 1;						//初期スポーンの数
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
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
	}
	float HP = 100.0f;						//現在のHP
	float Attack = 20.0f;					//基本の攻撃力
	float Defense = 10.0f;					//基本の守備力
	float Speed = 500.0f;					//基本のスピード
	int Spawnnum = 1;						//初期スポーンの数
	wchar_t* Name = L"Player";     			//ステータスを適応するモデルの名前
};