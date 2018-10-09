#include"stdafx.h"
#include"system/system.h"
#include"level/Level.h"
#include"UI.h"
#include"Stage.h"
#include"Enemy/Enemy.h"
#include"Enemy/Enemyleader.h"
#include"Player.h"
#include"Gamecamera.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
GameobjectManager* objectManager;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

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
	//g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	//g_camera3D.SetPosition({ 0.0f, 100.0f, 0.0f });
	//g_camera3D.SetUp({ 1.0f, 0.0f, 0.0f });
	//g_camera3D.SetFar(10000.0f);


	//�v���C���[
	//Player player;
	GameobjectManager objectManage;
	objectManager = &objectManage;
	objectManager->NewGO<Stage>(0);
	//Navimake* navimake = nullptr;
	//�Q�[�����[�v�B
	UI* Ui = objectManager->NewGO<UI>(0);
	Player* player = objectManager->NewGO<Player>(0);
	Gamecamera* Camera = objectManager->NewGO<Gamecamera>(10);
	Camera->SetPlayer(player);
	player->SetCamera(Camera);
	Level level;

	g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	static int kuku = 0;
	//Player* ks = objectManager->NewGO<Player>(1);
	level.Init(L"Assets/level/Enemy_lever.tkl", [&](LevelObjectData objData)
	{
		kuku++;
		if (kuku != 2) {
			return true;
		}
		Enemyleader* enemy = objectManager->NewGO<Enemyleader>(1, "Enemyleader");
		enemy->Setposition(objData.position);
		enemy->Setplayer(player);
		return true;
	});
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		int debak = 1;
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}

     //   auto ks = objectManager->NewGO<Player>(0);
		//�����G���W���̍X�V�B
		objectManager->Execute();
		g_physics.Update();
		if (debak==1)
		{
			g_physics.DebubDrawWorld();
		}
		//�v���C���[�̍X�V�B
		//player.Update();
		//�v���C���[�̕`��B
		//player.Draw();

	//    objectManager->DereteGO(ks);
		//�J�����̍X�V�B
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}