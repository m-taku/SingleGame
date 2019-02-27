#pragma once
#include "Ability.h"
struct enemy_hero : public Ability
{
	enemy_hero()
	{
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
	}
	float HP = 100.0f;				//基本のHP
	float Attack = 15.0f;			//基本の攻撃力
	float Defense = 10.0f;			//基本の守備力
	float Speed = 200.0f;			//基本のスピード
	wchar_t* Name = L"enemy_hero";     	//ステータスを適応する相手の名前
};
struct enemy_nait : public Ability
{
	enemy_nait()
	{
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
	}
	float HP = 50.0f;				//基本のHP
	float Attack = 50.0f;			//基本の攻撃力
	float Defense = 1.0f;			//基本の守備力
	float Speed = 50.0f;			//基本のスピード
	wchar_t* Name = L"enemy_nait";     	//ステータスを適応する相手の名前
};
struct enemy_Lance : public Ability
{
	enemy_Lance()
	{
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
	}
	float HP = 100.0f;				//基本のHP
	float Attack = 20.0f;			//基本の攻撃力
	float Defense = 60.0f;			//基本の守備力
	float Speed = 10.0f;			//基本のスピード
	wchar_t* Name = L"enemy_Lance";     	//ステータスを適応する相手の名前
};
struct PlyerStatus : public Ability
{
	PlyerStatus(){
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
	}
	float HP = 100.0f;				//現在のHP
	float Attack = 20.0f;				//基本の攻撃力
	float Defense = 10.0f;			//基本の守備力
	float Speed = 500.0f;				//基本のスピード
	wchar_t* Name = L"Player";     	//ステータスを適応する相手の名前
};