#include "stdafx.h"
#include "Item.h"
#include<random>


Item::Item()
{
}


Item::~Item()
{
}
bool Item::Load()
{
	m_prayer = g_objectManager->FindGO<Player>("player");
	if (m_prayer != nullptr)
	{
		wchar_t moveFilePath[256];		
		switch (m_item)
		{
		case ataac:
			swprintf_s(moveFilePath, L"Assets/modelData/Axe_2.cmo");
			break;
		case ataacM2:
			swprintf_s(moveFilePath, L"Assets/modelData/Axe_2.cmo");
			break;
		case defense:
			swprintf_s(moveFilePath, L"Assets/modelData/Dagger4_2.cmo");
			break;
		case defenseM2:
			swprintf_s(moveFilePath, L"Assets/modelData/Dagger4_2.cmo");
			break;
		//case life:
		//	swprintf_s(moveFilePath, L"Assets/modelData/jimennabi1.cmo");
		//	m_item = life;
		//	break;
		default:
			//�������A�C�e���̎�ނ̐ݒ肪�Ȃ����
			//����randam�֐��ŗ����𔭐�
			std::random_device baka;
			std::mt19937 randam(baka());
			//���̊֐��ŕ��z�𕽋ω��i��l���U���z�j����
			std::uniform_int_distribution<> rand10(0, item_group::itemnum);
			auto m_itemtype = rand10(randam);
			//���������l���A�C�e���̎�ނƂ���
			m_item = (item_group)m_itemtype;
			return false;
			//break;
		}
		m_model.Init(moveFilePath);
		m_model.UpdateWorldMatrix(m_pos, m_rotetion, {1.0,1.0f,1.0});
		return true;
	}
	return false;
}
void Item::Update()
{
	CQuaternion rod;
	rod.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_rotetion.Multiply(rod);
	m_model.UpdateWorldMatrix(m_pos, m_rotetion, { 1.0,1.0f,1.0f });
	//�������v���C���[�ɓ������Ă��Ȃ��Ȃ�
	if ((m_prayer->Get2Dposition() - m_pos).Length() <= 100.0f) {
		//�v���C���[�ɓ���������
		//�A�C�e�����Ƃ̓��ꏈ�����s��
		switch (m_item)
		{
		case ataac:
			m_prayer->SetStatu_Attack(m_prayer->p_status->m_Attack*1.5f);
			break;
		case ataacM2:
			m_prayer->SetStatu_Attack(m_prayer->p_status->m_Attack*2.0f);
			break;
		case defense:
			m_prayer->SetStatu_Defense(m_prayer->p_status->m_Defense*1.5f);
			break;
		case defenseM2:
			m_prayer->SetStatu_Defense(m_prayer->p_status->m_Defense*2.0f);
			break;
		case life:
			m_prayer->AddStatu_NowHP(50.0f);
			break;
		default:
			break;
		}
		//���ꏈ�����I�������̂ŏ���
		g_objectManager->DereteGO(this);
	}
}
void Item::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}