#pragma once

#include"Item.h"
class ItemManager:public Gameobject
{
public:
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load();
	/// <summary>
	/// ���t���[���Ă΂��֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobject����p������OnDestroy�֐�
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// �\���p�֐��B
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

