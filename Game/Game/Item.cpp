#include "stdafx.h"
#include "Item.h"
#include<random>


Item::Item()
{
}


Item::~Item()
{
	if (m_sampleEffect != nullptr) {
		m_sampleEffect->Release();
		if (g_graphicsEngine->GetEffekseerManager() != NULL) {
			g_graphicsEngine->GetEffekseerManager()->StopEffect(m_playEffectHandle);
		}
	}
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
			m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/efect/attcak.efk");
			break;
		case defense:
			swprintf_s(moveFilePath, L"Assets/modelData/Dagger4_2.cmo");
			m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/efect/defense.efk");
			break;
		case life:
			swprintf_s(moveFilePath, L"Assets/modelData/portion.cmo");
			m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/efect/moya.efk");
			break;
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
		}
		m_model.Init(moveFilePath);
		m_model.UpdateWorldMatrix(m_pos, m_rotetion, {1.0,1.0f,1.0});	
		m_playEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(m_sampleEffect,  m_pos.x,m_pos.y,m_pos.z);
		g_graphicsEngine->GetEffekseerManager();
		m_hit = true;
		return true;
	}
	return false;
}
bool Item::Update()
{
	if (m_hit||Load()) {
		CQuaternion rod;
		rod.SetRotationDeg(CVector3::AxisY(), 2.0f);
		m_rotetion.Multiply(rod);
		m_model.UpdateWorldMatrix(m_pos, m_rotetion, CVector3::One());
		//�������v���C���[�ɓ������Ă��Ȃ��Ȃ�

		if ((m_prayer->Get3DPosition() - m_pos).Length() <= 90.0f) {
			//�v���C���[�ɓ���������
			//�A�C�e�����Ƃ̓��ꏈ�����s��
			switch (m_item)
			{
			case ataac:
				m_prayer->SetBairitu(attakc1, 1.2f);
				break;
			case defense:
				m_prayer->SetBairitu(defense1, 1.2f);
				break;
			case life:
				m_prayer->AddStatu_NowHP(50.0f);
				break;
			default:
				break;
			}
			//m_hit = true;		
			//m_taim.TimerStart();
			//���ꏈ�����I�������̂ŏ���
			return true;
		}
		//else
		//{
		//	m_taim.TimerStop();
		//	if (m_taim.GetSeconds() <= 10.0f) {
		//		return true;
		//	}
		//}
		return false;
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