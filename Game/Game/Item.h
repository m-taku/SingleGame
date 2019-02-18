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
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load() override;
	/// <summary>
 	/// 毎フレーム呼ばれる関数。
	/// </summary>
	void Update() override;
	/// <summary>
	/// 表示用関数。
	/// </summary>
	void Draw() override;
private:	
	SkinModel m_model;								//モデルデータ
	Player* m_prayer = nullptr;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rotetion = CQuaternion::Identity();
	item_group m_item;  
	wchar_t moveFilePath[256];
	bool m_hit = true;
	Timer* m_timer = nullptr;
};

