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
	//サウンドのロード
	m_bgmA.Init(L"Assets/sound/taitor.wav");
	m_bgmA.Play(true);
	//タイトルのスプライトのデータをロードする。
	m_texture_moji.CreateFromDDSTextureFromFile(L"Resource/sprite/taitoru.dds");
	m_title_haikei.Init(m_texture_moji.GetBody(), FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_title_haikei.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_texture_haikei.CreateFromDDSTextureFromFile(L"Resource/sprite/yellow.dds");
	m_title_moji.Init(m_texture_haikei.GetBody(), FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_title_moji.Updete(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//タイトルの矢印用のデータをロードする。
	m_texture_yaji.CreateFromDDSTextureFromFile(L"Resource/sprite/yaji.dds");							//タイトルの矢印用のリソース
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
		//スタートの条件になったのでフェードを開始する
		m_fade.Fadein();
	}
	if (moudo == sturt &&g_pad[0].IsPress(enButtonRight))
	{
		//メニューを指す矢印を変更する。
		m_pos.x +=600.0f;
		moudo = test;
	}
	else
	{
		if (moudo == test &&g_pad[0].IsPress(enButtonLeft))
		{
			//メニューを指す矢印を変更する。
			m_pos.x -= 600.0f;
			moudo = sturt;
		}
	}
	//矢印の位置の変更
	m_yajiSprite.Updete(m_pos, CQuaternion::Identity(), CVector3::One());

	if (m_fade.Update())
	{
		//フェードの状態遷移
		switch (m_fade.GetState())
		{
		case Fade::fadein:
			//フェードが完了し見えない状態になっているので
			//ゲーム読み込みをスタートさせる
			m_bgmA.Stop();
			g_objectManager->NewGO<Game>(GameObjectPriority_Game,"Game");
			//タイトルのスプライトを透明にし見えないようにする。
			m_title_moji.SetclearColor(0.0f);
			m_title_haikei.SetclearColor(0.0f);
			m_yajiSprite.SetclearColor(0.0f);
			//フェードを明ける
			m_fade.Fadeout();
			break;
		case Fade::fadeout:
			//すべての処理が終了したのでタイトルをDeleteする
			g_objectManager->DereteGO(this);
			break;
		default:
			break;
		}
	}
}
void title::PostDraw()
{
	//タイトルのスプライトをDrawする。
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
	//フェードをDrawする。
	m_fade.Draw();
}