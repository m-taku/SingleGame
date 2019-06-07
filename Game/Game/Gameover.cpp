#include "stdafx.h"
#include "Gameover.h"
#include"title.h"


Gameover::Gameover()
{
}


Gameover::~Gameover()
{
}
bool Gameover::Load()
{

	wchar_t moveFilePath[256];		
	if (m_fur) {
		swprintf_s(moveFilePath, L"Resource/sprite/over.dds");
	}
	else
	{
		swprintf_s(moveFilePath, L"Resource/sprite/kuraa.dds");
	}
	//ゲームおーばのスプライトのデータをロードする。
	m_texture_font.CreateFromDDSTextureFromFile(moveFilePath);
	m_over_font.Init(m_texture_font.GetBody(), FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_over_font.Updete(m_pos, CQuaternion::Identity(), CVector3::One());
	//すべての関数をストップさせ、Drawのみにする
	g_objectManager->AllStoporComeback();		
	m_fade.Fadein();
	return true;
}
void Gameover::Stop()
{
	this->isStop();
}
void Gameover::Update()
{
	
	//if (m_fade.GetState() == Fade::idel) {
	//	if (m_pos.y <= 0.0f)
	//	{
	//		//文字が所定の場所についたのでフェードをスタートさせる

	//	}
	//	else
	//	{
	//		m_pos.y -= 20.0f;
	//	}
	//}
	if (m_fade.Update())
	{
		switch (m_fade.GetState())
		{
		case Fade::fadein:	
			m_pos.y = 0.0f;
			m_over_font.Updete(m_pos, CQuaternion::Identity(), CVector3::One());
			//フェードが完了し見えない状態になっているので
			//ゲームを終了しタイトルを発生させる
			if (g_pad[0].IsTrigger(enButtonA)) {
				g_objectManager->DereteGO("Game");
				g_objectManager->NewGO<title>(GameObjectPriority_ta, "title");
				m_over_font.SetclearColor(0.0f);
				m_fade.Fadeout(50.0f);
			}
			break;
		case Fade::fadeout:

			//すべての処理が終了したのでゲームおーばをDeleteする
			g_objectManager->DereteGO(this);
			break;
		default:
			break;
		}
	}

}
void Gameover::PostDraw()
{

	m_fade.Draw();
	m_over_font.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetProjectionMatrix()
	);

}
