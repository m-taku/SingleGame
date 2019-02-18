#pragma once
class Item:public Gameobject
{
public:
	Item();
	~Item();	
	//struct item_group
	//{
	//	int ataac[5] = {0,0,0,0,0};
	//	int ataacM2 =  1;
	//	int defense=2;
	//	int defenseM2=3;
	//	int life=4;
	//	int itemnum=5;
	//};
	enum item_group {
		ataac,
		ataacM2,
		defense,
		defenseM2,
		life,
		itemnum
	};
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
	}
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
 	/// ���t���[���Ă΂��֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �\���p�֐��B
	/// </summary>
	void Draw() override;
private:	
	SkinModel m_model;								//���f���f�[�^
	Player* m_prayer = nullptr;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rotetion = CQuaternion::Identity();
	item_group m_item;  
	wchar_t moveFilePath[256];
	bool m_hit = true;
	Timer* m_timer = nullptr;
};

