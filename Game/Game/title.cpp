#include "stdafx.h"
#include "title.h"
#include"Game.h"

title::title()
{
}


title::~title()
{
}
bool title::Load()
{
	//�T�E���h�̃��[�h
	m_bgmA.Init(L"Assets/sound/taitor.wav");
	m_bgmA.Play(true);
	//�^�C�g���̃X�v���C�g�̃f�[�^�����[�h����B
	m_texture_moji.CreateFromDDSTextureFromFile(L"Resource/sprite/taitoru.dds");
	m_title_haikei.Init(m_texture_moji.GetBody(), FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_texture_haikei.CreateFromDDSTextureFromFile(L"Resource/sprite/yellow.dds");
	m_title_moji.Init(m_texture_haikei.GetBody(), FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//�^�C�g���̖��p�̃f�[�^�����[�h����B
	m_texture_yaji.CreateFromDDSTextureFromFile(L"Resource/sprite/yaji.dds");							//�^�C�g���̖��p�̃��\�[�X
	m_yajiSprite.Init(m_texture_yaji.GetBody(), 100.0f, 72.0f);								
	m_yajiSprite.Updete(m_pos, CQuaternion::Identity(), CVector3::One());
	return true;
}
void title::Update()
{
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), { 1.0f,1.0f,1.0f });
	if (g_pad[0].IsTrigger(enButtonA)&& m_fade.GetState()==Fade::idel)
	{
		//�X�^�[�g�̏����ɂȂ����̂Ńt�F�[�h���J�n����
		m_fade.Fadein();
	}
	if (moudo == sturt &&g_pad[0].IsPress(enButtonRight))
	{
		//���j���[���w������ύX����B
		m_pos.x +=600.0f;
		moudo = test;
	}
	else
	{
		if (moudo == test &&g_pad[0].IsPress(enButtonLeft))
		{
			//���j���[���w������ύX����B
			m_pos.x -= 600.0f;
			moudo = sturt;
		}
	}
	//���̈ʒu�̕ύX
	m_yajiSprite.Updete(m_pos, CQuaternion::Identity(), CVector3::One());

	if (m_fade.Update())
	{
		//�t�F�[�h�̏�ԑJ��
		switch (m_fade.GetState())
		{
		case Fade::fadein:
			//�t�F�[�h�������������Ȃ���ԂɂȂ��Ă���̂�
			//�Q�[���ǂݍ��݂��X�^�[�g������
			m_bgmA.Stop();
			g_objectManager->NewGO<Game>(GameObjectPriority_Game,"Game");
			//�^�C�g���̃X�v���C�g�𓧖��ɂ������Ȃ��悤�ɂ���B
			m_title_moji.SetclearColor(0.0f);
			m_title_haikei.SetclearColor(0.0f);
			m_yajiSprite.SetclearColor(0.0f);
			//�t�F�[�h�𖾂���
			m_fade.Fadeout();
			break;
		case Fade::fadeout:
			//���ׂĂ̏������I�������̂Ń^�C�g����Delete����
			g_objectManager->DereteGO(this);
			break;
		default:
			break;
		}
	}
}
void title::PostDraw()
{
	//�^�C�g���̃X�v���C�g��Draw����B
	m_title_moji.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_title_haikei.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	m_yajiSprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);
	//�t�F�[�h��Draw����B
	m_fade.Draw();
}