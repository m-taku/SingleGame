#include"stdafx.h"
#include"system/system.h"
#include"title.h"
#include"level/Level.h"
#include"UI.h"
#include"Stage.h"
#include"Enemy/EnemyLeader/Enemyleader.h"
#include"Enemy/Enemy.h"
#include"Player/Player.h"
#include"Gamecamera.h"
#include"RenderTarget.h"


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////

GameobjectManager* g_objectManager;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	CSoundEngine soundEngine;				//�T�E���h�G���W���B
	soundEngine.Init();
#ifdef _DEBUG
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 150.0f, -1000.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000000.0f);	
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetNear(0.1f);
	g_camera2D.SetFar(1000.0f);
	g_camera2D.Setcamera2D(true);
	g_camera2D.Update();	
	Timer* m_timer = nullptr;
	Font* m_font = nullptr;											//�����\���̃C���X�^���X
	m_font = new Font;
	m_timer = new Timer;
	m_timer->TimerStart();	
	float m_fps = 0.0f;
	g_objectManager = new GameobjectManager();
	g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	auto tittle = g_objectManager->NewGO<title>(GameObjectPriority_ta,"title");
	int debak = 0;
	while (DispatchWindowMessage() == true)
	{
		m_timer->TimerRestart();
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//���y�f�[�^�̍X�V
		soundEngine.Update();
		g_objectManager->Execute();
		static int count = 0;
		static float m_timeTotal = 0;
		m_timeTotal += (float)m_timer->GetSeconds();
		count++;
		GetTime().PushFrameDeltaTime((float)m_timer->GetSeconds());
		if (count == 30) {
			m_fps = 1.0f / GetTime().GetFrameTime();
			m_timeTotal = 0.0f;
			count -= 1;
		}

#ifdef _DEBUG
		m_font->BeginDraw();	//�t�H���g�̕`��J�n�B
		wchar_t fps[256];
		swprintf_s(fps, L"FPS = %.2f", m_fps);
		float w = FRAME_BUFFER_W;
		float h = FRAME_BUFFER_H;
		m_font->Draw(
			fps,
			{ 0.0f,h*0.5f },
			{ 1.0f,1.0f,1.0f,1.0f },
			0.0f,															//�e�o�r�\���A�A�A�܂��i�Q�c���烆�E�Z���j
			2.0f,
			{ 0.0f, 1.0f }
		);
		wchar_t Seconds[256];
		swprintf_s(Seconds, L"�b�@�� %.2f", m_timer->GetAllSeconds());
		m_font->Draw(
			Seconds,
			{ w*0.5f,h*0.5f },
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,															//�e�o�r�\���A�A�A�܂��i�Q�c���烆�E�Z���j
			2.0f,
			{ 1.0f, 1.0f }
		);
		m_font->EndDraw();
#endif
		//�`��I���B
		g_graphicsEngine->EndRender();
		m_timer->TimerStop();
	}
	//g_graphicsEngine->Release();
	delete g_objectManager;
	delete g_graphicsEngine;
	delete m_font;
	delete m_timer;
}
