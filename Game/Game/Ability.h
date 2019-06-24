#pragma once
#include"Enemy_ActionPriority.h"
/// <summary>
/// �X�e�[�^�X�̊��N���X
/// </summary>
class Ability : Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Ability()
	{

	}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Ability()
	{

	}
	virtual void Individuality(void* point) 
	{
	
	};
	float m_HP = 10.0f;					    //���݂�HP
	float m_Attack = 10.0f;					//��{�̍U����
	float m_MP = 0.0f;						//��{��MP
	float m_Defense = 10.0f;				//��{�̎����
	float m_Speed = 1.0f;					//��{�̃X�s�[�h
	CVector3 m_WeaponSize = CVector3::Zero();					//��{�̃X�s�[�h
	int m_Spawnnum = 1;						//��{�̃X�|�[����
	Enemy_ActionPriority* m_Enemy_Priority=nullptr;	//�G�l�~�[�̗D�揇��
	std::wstring m_CharaName = L"NULL";		//�X�e�[�^�X��K�����鑊��̖��O
protected:
	void SetHP(float hp)
	{
		m_HP = hp;
	}
	void SetMP(int MP)
	{
		m_MP = MP;
	}
	void SetAttack(float Attack)
	{
		m_Attack = Attack;
	}	
	void SetDefense(float Defense)
	{
		m_Defense = Defense;
	}
	void SetSpeed(float Speed)
	{
		m_Speed = Speed;
	}
	void SetName(const std::wstring& Name)
	{
		m_CharaName = Name;
	}
	void SetSpawnnum(int num)
	{
		m_Spawnnum = num;
	}
	void SetEnemy_Priority(Enemy_ActionPriority* ActionPriority)
	{
		m_Enemy_Priority = ActionPriority;
	}
	void SetWeaponSize(const CVector3& Size)
	{
		m_WeaponSize = Size;
	}
private:
};


