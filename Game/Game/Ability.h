#pragma once
#include"Enemy_ActionPriority.h"
/// <summary>
/// ステータスの基底クラス
/// </summary>
class Ability : Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Ability()
	{

	}
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Ability()
	{

	}
	virtual void Individuality(void* point) 
	{
	
	};
	float m_HP = 10.0f;					    //現在のHP
	float m_Attack = 10.0f;					//基本の攻撃力
	float m_MP = 0.0f;						//基本のMP
	float m_Defense = 10.0f;				//基本の守備力
	float m_Speed = 1.0f;					//基本のスピード
	CVector3 m_WeaponSize = CVector3::Zero();					//基本のスピード
	int m_Spawnnum = 1;						//基本のスポーン数
	Enemy_ActionPriority* m_Enemy_Priority=nullptr;	//エネミーの優先順位
	std::wstring m_CharaName = L"NULL";		//ステータスを適応する相手の名前
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


