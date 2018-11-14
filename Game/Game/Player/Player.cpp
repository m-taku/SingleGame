#include "stdafx.h"
#include "Player.h"
#include"Gamecamera.h"
Player::Player()
{
	//m_collider.Init(15.0f, 80.0f, m_position);
	//m_model.Init(L"Assets/modelData/unityChan.cmo");
}
Player::~Player()
{
	delete vector;
}
bool Player::Load()
{
	//cmoファイルの読み込み。
	m_collider.Init(15.0f, 80.0f, m_position);
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	vector = new VectorDraw(m_position);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 0.0f);
	Ui = objectManager->NewGO<UI>(0);
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
	m_Front.Normalize();
	m_model.UpdateWorldMatrix(m_position, m_rotation, {0.1f,0.1f,0.1f});
	return true;
}
void Player::Update()
{

	//ワールド行列の更新。	
	m_amount.x = g_pad->GetLStickXF();
	m_amount.z = g_pad->GetLStickYF();
	m_amount.y = 0.0f;
	if (m_amount.Length() > 0.0f)
	{
		CVector3 amount = m_amount;
		amount.Normalize();
		CVector3 camer_front = m_camer->GetCameraFront();
		camer_front.y = 0.0f;
		camer_front.Normalize();
		m_kaiten = acos(amount.Dot(CVector3::AxisZ()));
		if (amount.x < 0)
		{
			m_kaiten *= -1;
		}
		float camer_angle = acos(camer_front.Dot(CVector3::AxisZ()));
		CVector3 camer_jiku;
		camer_jiku.Cross(camer_front, CVector3::AxisZ());
		if (camer_jiku.y > 0)
		{
			camer_angle *= -1;
		}
		m_kaiten += camer_angle;
		m_rotation.SetRotation(CVector3::AxisY(), m_kaiten);
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
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 0.5f,0.5f,0.5f });
	vector->Update(m_position, m_Front, m_amount.Length()*3.0f); 
}
void Player::Draw()
{
	vector->Draw();
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}