#include "stdafx.h"
#include "Enemyleader.h"
#include"Enemy.h"


Enemyleader::Enemyleader()
{

}
Enemyleader::~Enemyleader()
{
	for (int i = 0; i < remaining; i++)
	{
		delete enemy[i];
	}
	delete path;
}
bool Enemyleader::Load()
{

	m_model.Init(L"Assets/modelData/Enemy.cmo",SOLDIER);
	for (int i = 0; i < SOLDIER; i++) {
		enemy[i] = new Enemy;
		enemy[i]->Setposition(position);
		enemy[i]->Setplayer(player);
		enemy[i]->SetLeader(this);
		enemy[i]->Load();
		position += haiti[i];
	}
	//m_collider.Init(10.0f, 10.0f, position);
	path = new Path;
	path->course(position, player->Get2Dposition());
	m_nextpos = path->Pathpos();
	Loadfrag = true;
	return true;
}
void Enemyleader::Update()
{
	m_model.BeginUpdateInstancingData();
	//for (int i = 0; i < remaining; i++) {
	//	enemy[i]->Update();
	//}
	CVector3 distance = CVector3::Zero();
	switch (state)
	{
	case group:
		move();
		distance = player->Get2Dposition() - position;
		if (distance.Length() < 500.0f)
		{
			for (int i = 0; i < remaining; i++) {
				enemy[i]->transitionState(Enemy::State_Move);
			}
			SetSteat(person);
		}
		else {
			for (int i = 0; i < remaining; i++) {
				m_model.UpdateInstancingData(position + haiti[i], CQuaternion::Identity(), CVector3::One());
				enemy[i]->Setposition(position + haiti[i]);
			}
		}
		break;
	case person:
		for (int i = 0; i < remaining; i++) {
			enemy[i]->Update();	
			if (state == gathering)
			{
				for (int i = 0; i < remaining; i++) {
					enemy[i]->transitionState(Enemy::State_Gathering);
				}
				break;
			}
		}
		break;
	case gathering:
	{
		ninzuu = 0;
		for (int i = 0; i < remaining; i++) {
			enemy[i]->Update();
		}
	}
		break;
	default:
		break;
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
void Enemyleader::move()
{
	CVector3 speed = CVector3::Zero();
	CVector3 nowpos = position;
	speed = m_nextpos - nowpos;
	if (speed.Length() <= 250.0f)
	{
		m_nextpos = path->Pathpos();	
		if (m_nextpos.x == m_oldposition.y&&m_nextpos.y == m_oldposition.x&&m_nextpos.z == m_oldposition.z)
		{
			path->course(nowpos, player->Get2Dposition());
			m_nextpos = path->Pathpos();
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	position += speed*1.0f/30.0f *100.0f;
}