#pragma once
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
	~Ability()
	{

	}
	float m_HP = 10.0f;					    //���݂�HP
	float m_Attack = 10.0f;					//��{�̍U����
	float m_Defense = 10.0f;				//��{�̎����
	float m_Speed = 1.0f;					//��{�̃X�s�[�h
	int Spawnnum = 1;						//��{�̃X�|�[����
	std::wstring m_CharaName = L"NULL";		//�X�e�[�^�X��K�����鑊��̖��O
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
	void SetSpawnnum(int num)
	{
		Spawnnum = num;
	}
private:

};


