#include "stdafx.h"
#include "Enemyleader.h"
#include"../Enemy.h"


Enemyleader::Enemyleader()
{

}
Enemyleader::~Enemyleader()
{
	for (int i = 0; i < m_remaining; i++)
	{
		delete m_enemy[i];
	}
	delete m_path;
}
bool Enemyleader::Load()
{
	m_model.Init(L"Assets/modelData/ToonRTS_demo_Knight.cmo",SOLDIER);
	for (int i = 0; i < SOLDIER; i++) {
		m_enemy[i] = new Enemy;
		m_enemy[i]->SetPosition(m_position);
		m_enemy[i]->SetPlayer(m_player);
		m_enemy[i]->SetLeader(this);
		m_enemy[i]->Load();
		m_position += m_haiti[i];
	}
	//m_collider.Init(10.0f, 10.0f, position);
	m_path = new Path;
	m_path->Course(m_position, m_player->Get2Dposition());
	m_nextpos = m_path->PathPos();
	m_animationclip[idle].Load(L"Assets/animData/enemy_idel.tka");
	m_animationclip[idle].SetLoopFlag(true);
	m_animationclip[attack].Load(L"Assets/animData/enemy_attack.tka");
	m_animationclip[attack].SetLoopFlag(true);
	m_animation.Init(m_model, m_animationclip, animnum);

	m_animation.Play(attack, 0.2f);
	return true;
}
void Enemyleader::Update()
{
	m_model.BeginUpdateInstancingData();
	//for (int i = 0; i < remaining; i++) {
	//	enemy[i]->Update();
	//}
	CVector3 distance = CVector3::Zero();
	switch (m_state)
	{
	case group:
		Move();
		distance = m_player->Get2Dposition() - m_position;
		if (distance.Length() < 500.0f)
		{
			for (int i = 0; i < m_remaining; i++) {
				m_enemy[i]->TransitionState(Enemy::State_Move);
			}
			ChangeSteat(person);
		}
		else {
			for (int i = 0; i < m_remaining; i++) {
				m_model.UpdateInstancingData(m_position + m_haiti[i], CQuaternion::Identity(), CVector3::One());
				m_enemy[i]->SetPosition(m_position + m_haiti[i]);
				m_enemy[i]->SetColliderPosition(m_position + m_haiti[i]);
			}
		}
		break;
	case person:
		for (int i = 0; i < m_remaining; i++) {
			m_enemy[i]->Update();
			if (m_state == gathering)
			{
				for (int i = 0; i < m_remaining; i++) {
					m_enemy[i]->TransitionState(Enemy::State_Gathering);
				}
				break;
			}
		}
		break;
	case gathering:
	{
		m_ninzuu = 0;
		for (int i = 0; i < m_remaining; i++) {
			m_enemy[i]->Update();
		}
	}
	break;
	default:
		break;
	}
	m_animation.Play(attack, 0.2f);
	m_animation.Update(0.1f);
}
void Enemyleader::Draw()
{

	if (m_state == group) {
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	else
	{
		for (int i = 0; i < m_remaining; i++) {
			m_enemy[i]->Draw();
		}
	}
	for (int i = 0; i < m_remaining; i++) {
		m_enemy[i]->postDraw();
	}
}
void Enemyleader::Move()
{
	CVector3 speed = CVector3::Zero();
	CVector3 nowpos = m_position;
	speed = m_nextpos - nowpos;
	if (speed.Length() <= 50.0f)
	{
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.y&&m_nextpos.y == m_oldposition.x&&m_nextpos.z == m_oldposition.z)
		{
			m_path->Course(nowpos, m_player->Get2Dposition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	m_position += speed*1.0f/30.0f *100.0f;
}