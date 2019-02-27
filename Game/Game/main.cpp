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
#include "RenderTarget.h"
//#if _DEBUG
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
GameobjectManager* g_objectManager;
HitObjict* g_HitObjict;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	CSoundEngine soundEngine;				//�T�E���h�G���W���B
	soundEngine.Init();
#ifdef _DEBUG
	//::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 150.0f, -1000.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(1000000.0f);	
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	//g_camera2D.SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
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
	//�v���C���[
	//Player player;
	g_HitObjict = new HitObjict;
	GameobjectManager objectManage;
	g_objectManager = &objectManage;
	g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	auto tittle = g_objectManager->NewGO<title>(0,"title");
	int debak = 0;

	float m_time = 0;
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
		float ka;
		m_timeTotal += (float)m_timer->GetSeconds();
		count++;
		if (count == 30) {
			m_fps = count / m_timeTotal;
			m_timeTotal = 0.0f;
			count = 0;
		}
		m_font->BeginDraw();	//�t�H���g�̕`��J�n�B
		wchar_t fps[256];
		swprintf_s(fps, L"FPS = %.2f", m_fps);
		float w = FRAME_BUFFER_W;
		float h = FRAME_BUFFER_H;
		m_font->Draw(
			fps,
			{ w*-0.5f,h*0.5f },
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,															//�e�o�r�\���A�A�A�܂��i�Q�c���烆�E�Z���j
			2.0f,
			{ 0.0f, 1.0f }
		);
		wchar_t Seconds[256];
		m_time += m_timer->GetSeconds();
		swprintf_s(Seconds, L"�b�@�� %.2f", m_time);
		m_font->Draw(
			Seconds,
			{ w*0.5f,h*0.5f },
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,															//�e�o�r�\���A�A�A�܂��i�Q�c���烆�E�Z���j
			2.0f,
			{ 1.0f, 1.0f }
		);
		m_font->EndDraw();
		//�v���C���[�̍X�V�B
		//player.Update();
		//�v���C���[�̕`��B
		//player.Draw();

		//objectManager->DereteGO(ks);
		//�J�����̍X�V�B
		//�`��I���B
		g_graphicsEngine->EndRender();
		m_timer->TimerStop();
	}
	delete g_HitObjict;
    delete g_graphicsEngine;
	delete m_font;
	delete m_timer;
	//soundEngine.Release();
}
