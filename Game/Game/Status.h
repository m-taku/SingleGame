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
	float HP = 100.0f;				//��{��HP
	float Attack = 15.0f;			//��{�̍U����
	float Defense = 10.0f;			//��{�̎����
	float Speed = 200.0f;			//��{�̃X�s�[�h
	wchar_t* Name = L"enemy_hero";     	//�X�e�[�^�X��K�����鑊��̖��O
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
	float HP = 50.0f;				//��{��HP
	float Attack = 50.0f;			//��{�̍U����
	float Defense = 1.0f;			//��{�̎����
	float Speed = 50.0f;			//��{�̃X�s�[�h
	wchar_t* Name = L"enemy_nait";     	//�X�e�[�^�X��K�����鑊��̖��O
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
	float HP = 100.0f;				//��{��HP
	float Attack = 20.0f;			//��{�̍U����
	float Defense = 60.0f;			//��{�̎����
	float Speed = 10.0f;			//��{�̃X�s�[�h
	wchar_t* Name = L"enemy_Lance";     	//�X�e�[�^�X��K�����鑊��̖��O
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
	float HP = 100.0f;				//���݂�HP
	float Attack = 20.0f;				//��{�̍U����
	float Defense = 10.0f;			//��{�̎����
	float Speed = 500.0f;				//��{�̃X�s�[�h
	wchar_t* Name = L"Player";     	//�X�e�[�^�X��K�����鑊��̖��O
};