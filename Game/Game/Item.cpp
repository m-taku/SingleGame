#include "stdafx.h"
#include "Item.h"
#include<random>


Item::Item()
{
	m_timer = new Timer;
}


Item::~Item()
{
	delete m_timer;
}
bool Item::Load()
{
	m_prayer = g_objectManager->FindGO<Player>("player");
	if (m_prayer != nullptr)
	{
		std::random_device baka;
		//このrandam関数で乱数を発生
		std::mt19937 randam(baka());
		//この関数で分布を平均化（一様離散分布）する
		std::uniform_int_distribution<> rand10(0,3);
		int item = rand10(randam);
		switch (item)
		{
		case ataac:
			swprintf_s(moveFilePath, L"Assets/modelData/Axe_2.cmo");
			m_item = ataac;
			break;
		case ataacM2:
			swprintf_s(moveFilePath, L"Assets/modelData/Axe_2.cmo");
			m_item = ataacM2;
			break;
		case defense:
			swprintf_s(moveFilePath, L"Assets/modelData/Dagger4_2.cmo");
			m_item = defense;
			break;
		case defenseM2:
			swprintf_s(moveFilePath, L"Assets/modelData/Dagger4_2.cmo");
			m_item = defenseM2;
			break;
		//case life:
		//	swprintf_s(moveFilePath, L"Assets/modelData/jimennabi1.cmo");
		//	m_item = life;
		//	break;
		default:
			break;
		}
		m_model.Init(moveFilePath);
		m_model.UpdateWorldMatrix(m_pos, m_rotetion, {1.0,1.0f,1.0});
		return true;
	}
	return false;
}
void Item::Update()
{
	if (m_hit) {
		if ((m_prayer->Get2Dposition() - m_pos).Length()<=100.0f) {
			switch (m_item)
			{
			case ataac:
				m_prayer->SetStatu_Attack(m_prayer->p_status.Attack*1.5f);
				break;
			case ataacM2:
				m_prayer->SetStatu_Attack(m_prayer->p_status.Attack*2.0f);
				break;
			case defense:
				m_prayer->SetStatu_Defense(m_prayer->p_status.Defense*1.5f);
				break;
			case defenseM2:
				m_prayer->SetStatu_Defense(m_prayer->p_status.Defense*2.0f);
				break;
			case life:
				m_prayer->AddStatu_NowHP(50.0f);
				g_objectManager->DereteGO(this);
				break;
			default:
				break;
			}
			m_timer->TimerStart();
			m_hit = false;
		}
		CQuaternion rod;
		rod.SetRotationDeg(CVector3::AxisY(),2.0f);
		m_rotetion.Multiply(rod);
		m_model.UpdateWorldMatrix(m_pos, m_rotetion, { 5.0,5.0f,5.0f });
	}
	else
	{
		m_timer->TimerStop();
		if (m_timer->GetAllSeconds() >= 10.0f)
		{
			switch (m_item)
			{
			case ataac:
			case ataacM2:
				m_prayer->SetStatu_Attack(m_prayer->p_status.Attack);
				break;
			case defense:
			case defenseM2:
				m_prayer->SetStatu_Defense(m_prayer->p_status.Defense);
				break;
			default:
				break;
			}
			g_objectManager->DereteGO(this);
		}
	}
}
void Item::Draw()
{
	if (m_hit) {
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
}