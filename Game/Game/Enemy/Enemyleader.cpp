#include "stdafx.h"
#include "Enemyleader.h"
#include"Enemy.h"


Enemyleader::Enemyleader()
{

}
Enemyleader::~Enemyleader()
{
}
bool Enemyleader::Load()
{
	enemy.resize(SOLDIER);
	m_model.Init(L"Assets/modelData/kaka.cmo",SOLDIER);
	for (int i = 0; i < SOLDIER; i++) {
		enemy[i] = new Enemy;
		enemy[i]->Setposition(position);
		enemy[i]->Setplayer(player);
		enemy[i]->SetLeader(this);
		enemy[i]->Load();
		position += haiti[i];
	}
	//m_collider.Init(10.0f, 10.0f, position);
	Loadfrag = true;
	return true;
}
void Enemyleader::Update()
{
	m_model.BeginUpdateInstancingData();
	for (int i = 0; i < remaining; i++) {
		enemy[i]->Update();

	}
}
void Enemyleader::Draw()
{
	
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	for (int i = 0; i < remaining; i++) {
		enemy[i]->Draw();
	}
}