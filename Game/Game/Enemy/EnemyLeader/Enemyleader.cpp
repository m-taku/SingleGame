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
	move();
	CVector3 distance = player->Get2Dposition() - position;
	if (distance.Length() >= 300.0f)
	{
		for (int i = 0; i < remaining; i++) {
			m_model.UpdateInstancingData(position, CQuaternion::Identity(), CVector3::One());
			enemy[i]->Setposition(position);
			position += haiti[i];
		}
	}
	else {
		for (int i = 0; i < remaining; i++) {
			enemy[i]->Update();
		}
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
		m_time += 10.0;
	}
	speed.y = 0.0;
	speed.Normalize();
	//enemy[SOLDIER-1]->Findangle(speed);
	if ((m_oldposition - nowpos).Length() <= 10.0f || (m_nextpos - nowpos).Length() <= 200.0f)
	{
		m_time++;
	}
	else
	{
		m_time = 0;
	}
	if (m_time >= 30)
	{
		path->course(position, player->Get2Dposition());
		m_time = 0;
	}
	m_oldposition = position;
	position += speed * 500.0f*1.0f / 30.0f;
}