#include "stdafx.h"
#include "Enemyleader.h"
#include"../Enemy.h"

Enemyleader::Enemyleader()
{

}
Enemyleader::~Enemyleader()
{
	for (auto enemy : m_enemy)
	{
		delete enemy;
	}
	delete m_path;
}
bool Enemyleader::Load()
{
	m_model.Init(L"Assets/modelData/ToonRTS_demo_Knight.cmo",SOLDIER);
	m_path = new Path;
	for (int i = 0; i < SOLDIER; i++) {
		auto k= new Enemy;
		k->SetPosition(m_position);
		k->SetPlayer(m_player);
		k->SetLeader(this);
		k->Load();
		m_enemy.push_back(k);
		m_position += m_haiti[i];
	}
	//m_collider.Init(10.0f, 10.0f, position);
	m_animationclip[idle].Load(L"Assets/animData/enemy_idel.tka");
	m_animationclip[idle].SetLoopFlag(true);
	m_animationclip[attack].Load(L"Assets/animData/enemy_attack1.tka");
	m_animationclip[attack].SetLoopFlag(true);
	m_animationclip[walk].Load(L"Assets/animData/enemy_walk.tka");
	m_animationclip[walk].SetLoopFlag(true);
	m_animation.Init(m_model, m_animationclip, animnum);
	m_animation.Play(idle, 0.2f);
	return true;
}
void Enemyleader::Update()
{
	m_model.BeginUpdateInstancingData();
	/*for (int i = 0; i < m_remaining; i++) {
		m_enemy[i]->Update();
	}*/
	int i = 0;
	CVector3 distance = CVector3::Zero();
	switch (m_state)
	{
	case group_stop:
		distance = m_player->Get2Dposition() - m_position;
		if (distance.Length() < 500.0f)
		{
			for (auto enemy: m_enemy) {
				enemy->TransitionState(Enemy::State_Move);
			}
			ChangeSteat(person);
		}
		else {
			for (auto enemy : m_enemy) {
				m_model.UpdateInstancingData(m_position + m_haiti[i], CQuaternion::Identity(), CVector3::One());
				enemy->SetPosition(m_position + m_haiti[i++]);
				enemy->ChangeColliderPosition(m_position + m_haiti[i]);
				m_state = m_group_state;
			}
		}
		break;
	case group_move:
		Move();
		distance = m_player->Get2Dposition() - m_position;
		if (distance.Length() < 500.0f)
		{
			for (auto enemy : m_enemy) {
				enemy->TransitionState(Enemy::State_Move);
			}
			ChangeSteat(person);
		}
		else {
			for (auto enemy : m_enemy) {
				m_model.UpdateInstancingData(m_position + m_haiti[i], CQuaternion::Identity(), CVector3::One());
				enemy->SetPosition(m_position + m_haiti[i++]);
				enemy->ChangeColliderPosition(m_position + m_haiti[i]);
			}
		}
		break;
	case person:
		for (auto enemy : m_enemy) {
			enemy->Update();
			if (m_state == gathering)
			{
				for (auto enemy : m_enemy) {
					enemy->TransitionState(Enemy::State_Gathering);
				}
				break;
			}
		}
		break;
	case gathering:
	{
		m_ninzuu = 0;
		for (auto enemy : m_enemy) {
			enemy->Update();
		}
		if (m_ninzuu >= m_remaining)
		{
			m_state = m_group_state;
			//for (int i = 0; i < SOLDIER; i++) {
			//	m_enemy[i]->TransitionState(Enemy::State_Attack);			//デバックで追加.製品ではいらない初期化。
			//}
		}
	}
	break;
	default:
		break;
	}
	m_enemy.begin();
	for (auto enemy = m_enemy.begin(); enemy != m_enemy.end();) {
		if (!(*enemy)->GetLife())
		{
			delete *enemy;
			m_remaining--;
			enemy = m_enemy.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}
	if (m_remaining <= 0)
	{
		m_life = false;
	}
	m_animation.Play(idle, 0.2f);
	m_animation.Update(0.1f);
	g_graphicsEngine->SetShadoCaster(&m_model);
	m_model.SetShadowReciever(true);
}
void Enemyleader::Draw()
{

	if (m_state == m_group_state) {
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	else
	{
		for (auto enemy : m_enemy) {
			enemy->Draw();
		}
	}
	for (auto enemy : m_enemy) {
		enemy->postDraw();
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
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			m_path->Course(nowpos, m_player->Get2Dposition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	m_position += speed * 1.0f / 30.0f *100.0f;
	//m_Front.y = 0;
	//m_Front.Normalize();
	//auto debag = m_Front;
	//auto Angle = acos(debag.Dot(Vector));
	//if (Angle >= CMath::DegToRad(1.0f))
	//{
	//	SetSpeed(0.0f);
	//	auto ka5 = CVector3::Zero();
	//	ka5.Cross(debag, Vector);
	//	CQuaternion ma3;
	//	if (ka5.y < 0)
	//	{
	//		ka5 = CVector3::AxisY()*-1;
	//	}
	//	else
	//	{
	//		ka5 = CVector3::AxisY();
	//	}
	//	if (Angle <= m_margin)
	//	{
	//		ma3.SetRotation(ka5, Angle);
	//	}
	//	else
	//	{
	//		ma3.SetRotationDeg(ka5, m_kaku);
	//	}
	//	m_angle.Multiply(ma3, m_angle);
	//}
}