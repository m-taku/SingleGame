#include "stdafx.h"
#include "Friendleader.h"
#include"Friend.h"


Friendleader::Friendleader()
{
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.Normalize();
}


Friendleader::~Friendleader()
{
	for (auto enemy : m_Friend)
	{
		delete enemy;
	}
	delete m_Status;
	delete m_path;
}
void Friendleader::Stop()
{
	for (auto enemy : m_Friend) {
		enemy->ChangeAnimation(NPC::idle);
		m_model.UpdateInstancingData(enemy->Get2DPosition(), m_angle, CVector3::One());
	}
}
bool Friendleader::Load()
{
	auto enemy = new Friend;
	enemy->SetPosition(m_position);
	//enemy->SetPlayer(m_player);
	enemy->SetLeader(this);
	enemy->SetStatus(m_Status);
	enemy->SetScore(m_Score);
	enemy->Load();
	m_Friend.push_back(enemy);
	m_position.x += 35.0f;
	//m_collider.Init(10.0f, 10.0f, position);	
	m_ninzuu++;
	if (m_ninzuu < m_Status->m_Spawnnum)
	{
		return false;
	}
	else {
		m_remaining = m_Status->m_Spawnnum;
		m_path = new Path;
		if (m_stopcount <= 0) {
			//ChangeGroup_Move();
		}
		wchar_t moveFilePath[256];
		swprintf_s(moveFilePath, L"Assets/modelData/%s.cmo", m_Status->m_CharaName.c_str());
		m_model.Init(moveFilePath, m_remaining);
		swprintf_s(moveFilePath, L"Assets/animData/%s_idle.tka", m_Status->m_CharaName.c_str());
		m_animationclip[idle].Load(moveFilePath);
		m_animationclip[idle].SetLoopFlag(true);
		swprintf_s(moveFilePath, L"Assets/animData/%s_walk.tka", m_Status->m_CharaName.c_str());
		m_animationclip[walk].Load(moveFilePath);
		m_animationclip[walk].SetLoopFlag(true);
		m_animation.Init(m_model, m_animationclip, animnum);
		m_animation.Play(walk, 0.2f);
		for (auto enemy : m_Friend) {
			m_model.UpdateInstancingData(enemy->Get2DPosition() + m_movespeed, CQuaternion::Identity(), CVector3::One());
		}
		return true;
	}
}
void Friendleader::Update()
{
	m_model.BeginUpdateInstancingData();
	//�����ŃG�l�~�[��delete
	for (auto enemy = m_Friend.begin(); enemy != m_Friend.end();) {
		if (!(*enemy)->GetLife())
		{
			m_remaining--;
			if (m_remaining <= 0)
			{
				m_position = (*enemy)->Get3DPosition();
				m_life = false;
			}
			delete *enemy;
			enemy = m_Friend.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}
	CVector3 distance = CVector3::Zero();
	switch (m_state)
	{
	case group_stop:
		//distance = m_player->Get2DPosition() - m_position;
		//�����ŌʂɕύX
		if (distance.Length() < 300.0f)
		{
			for (auto enemy : m_Friend) {
				enemy->TransitionState(NPC::State_Move);
			}
			ChangeSteat(person);
		}
		else {
			m_movespeed = CVector3::Zero();
			for (auto enemy : m_Friend) {
				m_model.UpdateInstancingData(enemy->Get2DPosition(), CQuaternion::Identity(), CVector3::One());
				enemy->SetPosition(enemy->Get2DPosition() + m_movespeed);
				enemy->SetAngle(m_angle);
				enemy->ChangeColliderPosition(enemy->Get2DPosition());
			}
			g_graphicsEngine->SetShadoCaster(&m_model);
			m_model.SetShadowReciever(true);
			m_animation.Play(idle, 0.2f);
		}
		break;
	case group_move:
		Move();
		//distance = m_player->Get2DPosition() - m_position;
		//�����ŌʂɕύX
		if (distance.Length() < 1000.0f)
		{
			for (auto enemy : m_Friend) {
				enemy->TransitionState(NPC::State_Move);
			}
			ChangeSteat(person);
			m_stopcount = 0;
		}
		else {
			for (auto enemy : m_Friend) {
				m_model.UpdateInstancingData(enemy->Get2DPosition(), m_angle, CVector3::One());
				enemy->SetPosition(enemy->Get2DPosition() + m_movespeed);
				enemy->SetAngle(m_angle);
				enemy->ChangeColliderPosition(enemy->Get2DPosition());
			}
			g_graphicsEngine->SetShadoCaster(&m_model);
			m_model.SetShadowReciever(true);
			m_animation.Play(walk, 0.2f);
		}
		break;
	case person:
		for (auto enemy = m_Friend.begin(); enemy != m_Friend.end();) {
			(*enemy)->Update();
			if (m_state == gathering)
			{
				for (auto enemy : m_Friend) {
					enemy->TransitionState(NPC::State_Gathering);
				}
				break;
			}
			enemy++;
		}
		break;
	case gathering:
	{
		m_ninzuu = 0;
		for (auto enemy : m_Friend) {
			enemy->Update();
		}
		if (m_ninzuu >= m_remaining)
		{
			//ChangeGroup_Move();
			m_state = m_group_state;
		}
	}
	break;
	default:
		break;
	}
	//m_animation.Play(idle, 0.2f);
}
void Friendleader::Draw()
{
	m_animation.Update(GetTime().GetFrameTime());
	if (m_state == m_group_state) {
		m_model.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	else
	{
		for (auto enemy : m_Friend) {
			enemy->Draw();
		}
	}
	for (auto enemy : m_Friend) {
		enemy->postDraw();
	}
}

void Friendleader::Move()
{
	CVector3 nowpos = m_position;
	m_movespeed = m_nextpos - nowpos;
	if (m_movespeed.Length() <= 50.0f)
	{
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x && m_nextpos.y == m_oldposition.y && m_nextpos.z == m_oldposition.z)
		{
			//m_path->Course(nowpos, m_player->Get2DPosition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
	}
	float speed = m_Status->m_Speed;
	if (++m_fream > 100) {
		//m_path->Course(nowpos, m_player->Get2DPosition());
		m_nextpos = m_path->PathPos();
		m_fream = 0;
	}
	m_movespeed.y = 0.0;
	m_movespeed.Normalize();
	m_Rot.MakeRotationFromQuaternion(m_angle);
	m_Front.x = m_Rot.m[2][0];
	m_Front.y = m_Rot.m[2][1];
	m_Front.z = m_Rot.m[2][2];
	m_Front.y = 0;
	m_Front.Normalize();
	auto debag = m_Front;
	auto Angle = acos(debag.Dot(m_movespeed));
	if (Angle >= CMath::DegToRad(1.0f))
	{
		speed /= 2.0f;
		auto ka5 = CVector3::Zero();
		ka5.Cross(debag, m_movespeed);
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
	m_movespeed = m_movespeed * speed*GetTime().GetFrameTime();
	m_position += m_movespeed;
}