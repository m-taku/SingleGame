#include "stdafx.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
	Rereas();
}
bool ItemManager::Load()
{
	if (nullptr != g_objectManager->FindGO<Player>("player"))
	{
		return true;
	}
	return false;
}
void ItemManager::Rereas()
{
	for (auto item : m_item)
	{
		delete item;
	}
	m_item.clear();
}
void ItemManager::OnDestroy()
{

}
void ItemManager::Update()
{
	for (auto k = m_item.begin(); k != m_item.end();)
	{
		if ((*k)->Update())
		{
			delete *k;
			k = m_item.erase(k);
			continue;
		}
		k++;
	}
}
void ItemManager::Draw()
{
	for (auto k : m_item)
	{
		k->Draw();
	}
}