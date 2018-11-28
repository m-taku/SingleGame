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

//#if _DEBUG
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
GameobjectManager* g_objectManager;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

#ifdef _DEBUG
	//::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 150.0f, -1000.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);	
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	//g_camera2D.SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetNear(0.1f);
	g_camera2D.SetFar(1000.0f);
	g_camera2D.Setcamera2D(true);
	g_camera2D.Update();
	
	//�v���C���[
	//Player player;
	GameobjectManager objectManage;
	g_objectManager = &objectManage;
	g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	
	auto tittle = g_objectManager->NewGO<title>(0,"title");
	int debak = 0;
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
        //auto ks = objectManager->NewGO<Player>(0);
		//�����G���W���̍X�V�B
		g_objectManager->Execute();
		if (debak==0)
		{
			g_physics.DebubDrawWorld();
		}
		g_physics.Update();
		//�v���C���[�̍X�V�B
		//player.Update();
		//�v���C���[�̕`��B
		//player.Draw();

	    //objectManager->DereteGO(ks);
		//�J�����̍X�V�B
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
    delete g_graphicsEngine;
}