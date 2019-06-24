#pragma once
/// <summary>
/// �X�e�[�^�X�����肷��N���X�Q
/// </summary>
#include "Ability.h"
class Enemy;
class EnemyManager;
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
		SetWeaponSize(Size);
		ka.AttackPriority =100.0f;
		ka.DefensePriority = 0.0f;
		ka.freedomPriority = 0.0f;
		SetEnemy_Priority(&ka);
	}
	float HP = 50.0f;						//��{��HP
	float Attack = 20.0f;					//��{�̍U����
	float Defense = 5.0f;				    //��{�̎����
	float Speed = 200.0f;					//��{�̃X�s�[�h	
	int Spawnnum = 5;						//�����X�|�[���̐�
	CVector3 Size = { 10.0f, 10.0f,60.0f };	
	Enemy_ActionPriority ka;
	wchar_t* Name = L"enemy_hero";     		//�X�e�[�^�X��K�����郂�f���̖��O
};
/// <summary>
/// ���f��enemy_nait�̃X�e�[�^�X
/// </summary>
struct enemy_nait : public Ability
{
	enemy_nait();
	~enemy_nait()
	{
		delete m_timer;
	}
	void Individuality(void* point) override;
	float HP = 30.0f;						//��{��HP
	float Attack = 30.0f;					//��{�̍U����
	float Defense = 19.0f;					//��{�̎����
	float Speed = 50.0f;					//��{�̃X�s�[�h
	int Spawnnum = 3;						//�����X�|�[���̐�
	Enemy_ActionPriority ka;
	CVector3 Size = { 10.0f, 10.0f,60.0f };
	wchar_t* Name = L"enemy_nait";     		//�X�e�[�^�X��K�����郂�f���̖��O
private:
	EnemyManager * m_enemymanager = nullptr;
	Timer* m_timer = nullptr;
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
		ka.AttackPriority = 70.0f;
		ka.DefensePriority = 30.0f;
		ka.freedomPriority = 0.0f;
		SetEnemy_Priority(&ka);
		SetWeaponSize(Size);
	}
	float HP = 50.0f;						//��{��HP
	float Attack = 15.0f;					//��{�̍U����
	float Defense = 7.5f;					//��{�̎����
	float Speed = 100.0f;					//��{�̃X�s�[�h
	int Spawnnum = 3;						//�����X�|�[���̐�
	Enemy_ActionPriority ka;
	CVector3 Size = { 10.0f, 10.0f,100.0f };
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
		ka.AttackPriority = 100.0f;
		ka.DefensePriority = 0.0f;
		ka.freedomPriority = 0.0f;
		SetEnemy_Priority(&ka);
		SetWeaponSize(Size);
	}
	void Individuality(void* point)
	{

	}
	float HP = 100.0f;						//��{��HP
	float Attack = 20.0f;					//��{�̍U����
	float Defense = 15.0f;					//��{�̎����
	float Speed = 100.0f;					//��{�̃X�s�[�h
	int Spawnnum = 1;						//�����X�|�[���̐�
	Enemy_ActionPriority ka;
	CVector3 Size = { 10.0f, 10.0f,90.0f };
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
		SetMP(MP);
		SetAttack(Attack);
		SetDefense(Defense);
		SetSpeed(Speed);
		SetName(Name);
		SetWeaponSize(Size);
	}
	float HP = 500.0f;						//�ő��HP
	float MP = 100.0f;						//�ő��MP
	float Attack = 20.0f;					//��{�̍U����
	float Defense = 10.0f;					//��{�̎����
	float Speed = 400.0f;					//��{�̃X�s�[�h
	int Spawnnum = 1;						//�����X�|�[���̐�
	CVector3 Size = { 10.0f,10.0f,80.0f };	//
	wchar_t* Name = L"Player";     			//�X�e�[�^�X��K�����郂�f���̖��O
};