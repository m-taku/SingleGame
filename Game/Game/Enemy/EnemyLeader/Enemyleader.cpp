#include "stdafx.h"
#include "Enemyleader.h"
#include"../Enemy.h"

Enemyleader::Enemyleader()
{
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.Normalize();

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
	auto enemy = new Enemy;
	enemy->SetPosition(m_position);
	enemy->SetPlayer(m_player);
	enemy->SetLeader(this);
	enemy->SetfileName(m_Name);
	enemy->SetScore(m_Score);
	enemy->Load();
	m_enemy.push_back(enemy);
	m_position.x += 100.0f;
	//m_collider.Init(10.0f, 10.0f, position);	
	m_ninzuu++;
	if (m_ninzuu < SOLDIER)
	{
		return false;
	}
	else {
		m_path = new Path;
		ChangeGroup_state();
		wchar_t moveFilePath[256];
		swprintf_s(moveFilePath, L"Assets/modelData/%s.cmo", m_Name);
		m_model.Init(moveFilePath, SOLDIER);
		swprintf_s(moveFilePath, L"Assets/animData/%s_idle.tka", m_Name);
		m_animationclip[idle].Load(moveFilePath);
		m_animationclip[idle].SetLoopFlag(true);
		swprintf_s(moveFilePath, L"Assets/animData/%s_attack.tka", m_Name);
		m_animationclip[attack].Load(moveFilePath);
		m_animationclip[attack].SetLoopFlag(true);
		swprintf_s(moveFilePath, L"Assets/animData/%s_walk.tka", m_Name);
		m_animationclip[walk].Load(moveFilePath);
		m_animationclip[walk].SetLoopFlag(true);
		m_animation.Init(m_model, m_animationclip, animnum);
		m_animation.Play(walk, 0.2f);
		for (auto enemy : m_enemy) {
			m_model.UpdateInstancingData(enemy->Get2DPosition() + m_speed, CQuaternion::Identity(), CVector3::One());
		}
		return true;
	}
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
		m_position += m_speed;
		//ここで個別に変更
		if (distance.Length() < 500.0f)
		{
			for (auto enemy: m_enemy) {
				enemy->TransitionState(Enemy::State_Move);
			}
			ChangeSteat(person);
		}
		else {
			for (auto enemy : m_enemy) {
				m_model.UpdateInstancingData(enemy->Get2DPosition() + m_speed, CQuaternion::Identity(), CVector3::One());
				enemy->SetPosition(enemy->Get2DPosition() + m_speed);
				enemy->SetAngle(m_angle);
				enemy->ChangeColliderPosition(enemy->Get2DPosition());
				m_state = m_group_state;
			}
			g_graphicsEngine->SetShadoCaster(&m_model);
			m_model.SetShadowReciever(true);
			//m_animation.Play(idle, 0.2f);
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
				m_model.UpdateInstancingData(enemy->Get2DPosition() /*+ m_speed*/, m_angle/* CQuaternion::Identity()*//*enemy->GetAngle()*/, {5.0f,5.0f,5.0f});
				enemy->SetPosition(enemy->Get2DPosition() + m_speed);
				enemy->SetAngle(m_angle);
				enemy->ChangeColliderPosition(enemy->Get2DPosition());
				m_state = m_group_state;
			}
			g_graphicsEngine->SetShadoCaster(&m_model);
			m_model.SetShadowReciever(true);
			//m_animation.Play(walk, 0.2f);
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
			m_remaining--;		
			if (m_remaining <= 0)
			{
				m_position = (*enemy)->Get3DPosition();

				m_life = false;
			}
			delete *enemy;
			enemy = m_enemy.erase(enemy);

		}
		else
		{
			enemy++;
		}
	}

	//m_animation.Play(idle, 0.2f);

}
void Enemyleader::Draw()
{

	m_animation.Update(1.0f/30.0f)
		;
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
	m_speed = CVector3::Zero();
	CVector3 nowpos = m_position;
	m_speed = m_nextpos - nowpos;
	if (m_speed.Length() <= 50.0f)
	{
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			m_path->Course(nowpos, m_player->Get2Dposition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
	}
	float speed = 100.0f;
	static int m_fream = 0;
	if (++m_fream > 100) {
		m_path->Course(nowpos, m_player->Get2Dposition());
		m_nextpos = m_path->PathPos();
		m_fream = 0;
	}	
	m_speed.y = 0.0;
	m_speed.Normalize();
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.y = 0;
	m_Front.Normalize();
	auto debag = m_Front;
	auto Angle = acos(debag.Dot(m_speed));
	if (Angle >= CMath::DegToRad(1.0f))
	{
		speed /= 2;
		auto ka5 = CVector3::Zero();
		ka5.Cross(debag, m_speed);
		CQuaternion ma3;
		if (ka5.y < 0)
		{
			ka5 = CVector3::AxisY()*-1;
		}
		else
		{
			ka5 = CVector3::AxisY();
		}
		if (Angle <= m_margin)
		{
			ma3.SetRotation(ka5, Angle);
		}
		else
		{
			ma3.SetRotationDeg(ka5, m_kaku);
		}
		m_angle.Multiply(ma3, m_angle);
	}
	m_speed = m_speed * speed*1.0f / 30.0f;
	m_position += m_speed;
}