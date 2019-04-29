#pragma once

#include"Item.h"
class ItemManager:public Gameobject
{
public:
	/// <summary>
	/// Gemeobjectから継承したLoat関数。
	/// </summary>
	/// <returns>
	/// 成功でtrue、失敗でfalse。
	/// </returns>
	bool Load();
	/// <summary>
	/// 毎フレーム呼ばれる関数。
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobjectから継承したOnDestroy関数
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// 表示用関数。
	/// </summary>
	void Draw();
	void Rereas();
	void SpawnItem(CVector3 m_pos,item_group item_type= itemnum)
	{
		Item* item = new Item;
		item->SetPosition(m_pos);
		item->Setitemtype(item_type);
		item->Load();
		m_item.push_back(item);
	}
	ItemManager();
	~ItemManager();
private:
	std::list<Item*> m_item;
};

