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
	if (m_flag) {
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
			if (m_flag)
			{
				if (m_font == nullptr)
				{
					m_font = new Font;
					m_scoa.push_back(new wchar_t[256]);
					swprintf_s(*m_scoa.begin(), 256, L"Aボタンでタイトルに戻ります");
				}
				if (g_pad[0].IsTrigger(enButtonA)) {
					g_objectManager->DereteGO("Game");
					g_objectManager->NewGO<title>(GameObjectPriority_ta, "title");
					m_over_font.SetclearColor(0.0f);
					m_fade.Fadeout(50.0f);
				}
			}
			else
			{
				clear();
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
	if (m_font != nullptr&&m_fade.GetState()!= Fade::fadeout)
	{

		m_font->BeginDraw();	//フォントの描画開始。
		float pos = -50.0f;
		for (const auto& moji : m_scoa) {
			m_font->Draw(moji, { 0.0f,pos }, {0.0f,0.0f,0.0f,1.0f},0.0f,3.0f);
			pos -= 50.0f;
		}
		m_font->EndDraw();	//フォントの描画開始。
	}

}
void Gameover::clear()
{
	static int minit = 0;
	static int second = 0;
	static float count = 0;
	auto ka = m_scoa.begin();
	wchar_t k[256];
	switch (m_scorenum)
	{
	case start:
		m_font = new Font;
		m_score = g_objectManager->FindGO<Score>("Score");
		m_scoa.push_back(new wchar_t[256]);
		swprintf_s(*m_scoa.begin(), 256, L"討伐数      |　　%4d体", m_count);
		m_scorenum = toubatu;
		count = m_score->GetNum();
		break;
	case toubatu:
		m_count += count * GetTime().GetFrameTime() /2.0f;
		m_count = min(m_score->GetNum(), m_count);
		swprintf_s(*ka, 256, L"討伐数      |　　%4d体", (int)m_count);
		if (m_score->GetNum() <= m_count)
		{
			m_scoa.push_back(new wchar_t[256]);
			ka++;
			m_count = 0;
			swprintf_s(*ka, 256, L"残り時間    |　　%d分%02d秒", (int)m_count / 60, (int)m_count % 60);
			minit = 0;
			second = 0;
			m_score->Gettime(minit, second);

			count = minit * 60 + second ;
			m_scorenum = nokorijikann;
		}
		break;
	case nokorijikann:
		m_count += count* GetTime().GetFrameTime() / 2.0f;
		m_count = min(minit * 60 + second, m_count);
		ka++;
		swprintf_s(*ka, 256, L"残り時間    |　　%d分%02d秒",(int)m_count / 60, (int)m_count % 60);
		if (minit * 60 + second <= m_count)
		{
			m_flag = true;
			m_scoa.push_back(new wchar_t[256]);
			ka++;
			swprintf_s(*ka, 256, L"Aボタンでタイトルに戻ります");
		}
		break;
	default:
		break;
	}
}