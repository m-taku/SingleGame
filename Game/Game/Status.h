#pragma once
/// <summary>
/// �X�e�[�^�X�����肷��N���X�Q
/// </summary>
#include "Ability.h"
/// <summary>
/// ���f��enemy_hero�̃X�e�[�^�X
/// </summary>
struct enemy_hero : public Ability
{
	enemy_hero()
	{
		//���N���X������������
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);
	}
	float HP = 50.0f;						//��{��HP
	float Attack = 20.0f;					//��{�̍U����
	float Defense = 10.0f;				//��{�̎����
	float Speed = 200.0f;					//��{�̃X�s�[�h	
	int Spawnnum = 5;						//�����X�|�[���̐�
	wchar_t* Name = L"enemy_hero";     		//�X�e�[�^�X��K�����郂�f���̖��O
};
/// <summary>
/// ���f��enemy_nait�̃X�e�[�^�X
/// </summary>
struct enemy_nait : public Ability
{
	enemy_nait()
	{
		//���N���X������������
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);
	}
	float HP = 30.0f;						//��{��HP
	float Attack = 50.0f;					//��{�̍U����
	float Defense = 19.0f;					//��{�̎����
	float Speed = 50.0f;					//��{�̃X�s�[�h
	int Spawnnum = 1;						//�����X�|�[���̐�
	wchar_t* Name = L"enemy_nait";     		//�X�e�[�^�X��K�����郂�f���̖��O
};
/// <summary>
/// ���f��enemy_Lance�̃X�e�[�^�X
/// </summary>
struct enemy_Lance : public Ability
{
	enemy_Lance()
	{
		//���N���X������������
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);
	}
	float HP = 50.0f;						//��{��HP
	float Attack = 15.0f;					//��{�̍U����
	float Defense = 10.0f;					//��{�̎����
	float Speed = 100.0f;					//��{�̃X�s�[�h
	int Spawnnum = 3;						//�����X�|�[���̐�
	wchar_t* Name = L"enemy_Lance";     	//�X�e�[�^�X��K�����郂�f���̖��O
};
/// <summary>
/// ���f��mking�̃X�e�[�^�X
/// </summary>
struct mking : public Ability
{
	mking()
	{
		//���N���X������������
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetSpawnnum(Spawnnum);
	}
	float HP = 100.0f;						//��{��HP
	float Attack = 30.0f;					//��{�̍U����
	float Defense = 10.0f;					//��{�̎����
	float Speed = 100.0f;					//��{�̃X�s�[�h
	int Spawnnum = 1;						//�����X�|�[���̐�
	wchar_t* Name = L"mking";     			//�X�e�[�^�X��K�����郂�f���̖��O
};
/// <summary>
/// ���f��Player�̃X�e�[�^�X
/// </summary>
struct PlyerStatus : public Ability
{
	PlyerStatus()
	{
		//���N���X������������
		SetHP(HP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
	}
	float HP = 100.0f;						//���݂�HP
	float Attack = 20.0f;					//��{�̍U����
	float Defense = 10.0f;					//��{�̎����
	float Speed = 500.0f;					//��{�̃X�s�[�h
	int Spawnnum = 1;						//�����X�|�[���̐�
	wchar_t* Name = L"Player";     			//�X�e�[�^�X��K�����郂�f���̖��O
};