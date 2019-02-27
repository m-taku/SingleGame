#pragma once
class Ability : Noncopyable
{
public:
	Ability();
	~Ability();	
	float m_HP = 10.0f;				    //現在のHP
	float m_Attack = 10.0f;				//基本の攻撃力
	float m_Defense = 10.0f;			//基本の守備力
	float m_Speed = 1.0f;				//基本のスピード
	std::wstring m_CharaName = L"NULL";     	//ステータスを適応する相手の名前
protected:
	void SetHP(float hp)
	{
		m_HP = hp;
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
private:

};


