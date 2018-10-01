#include "stdafx.h"
#include "Player.h"
#include"Gamecamera.h"
Player::Player()
{
}
Player::~Player()
{
}
bool Player::Load()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_collider.Init(10.0f, 20.0f, m_position);
	vector = new VectorDraw(m_position);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 0.0f);
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
	m_Front.Normalize();
	return true;
}
void Player::Update()
{

	//���[���h�s��̍X�V�B	
	m_amount.x = g_pad->GetLStickXF();
	m_amount.z = g_pad->GetLStickYF();
	m_amount.y = 0.0f;
	if (m_amount.Length() > 0.0f)
	{
		CVector3 amount = m_amount;
		amount.Normalize();
		CVector3 camer_front = m_camer->Getcamerafront();
		camer_front.y = 0.0f;
		camer_front.Normalize();
		kaiten = acos(amount.Dot(CVector3::AxisZ()));
		if (amount.x < 0)
		{
			kaiten *= -1;
		}
		float camer_angle = acos(camer_front.Dot(CVector3::AxisZ()));
		CVector3 camer_jiku;
		camer_jiku.Cross(camer_front, CVector3::AxisZ());
		if (camer_jiku.y > 0)
		{
			camer_angle *= -1;
		}
		kaiten += camer_angle;
		m_rotation.SetRotation(CVector3::AxisY(), kaiten);
	}
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
	m_Front.Normalize();
	m_movespeed.x = m_Front.x * 500.0f*m_amount.Length();
	m_movespeed.z = m_Front.z * 500.0f*m_amount.Length();
	m_movespeed.y -= GRAVITY;
	if (g_pad[0].IsTrigger(enButtonA)&& m_collider.IsOnGround())
	{
		m_movespeed.y = 2000.0f;
	}
	m_position = m_collider.Execute(1.0f / 30.0f, m_movespeed);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
	vector->Update(m_position, m_Front, m_amount.Length());
}
void Player::postDraw()
{	
}
void Player::Draw()
{
	vector->Draw();
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}