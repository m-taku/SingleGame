#include "stdafx.h"
#include "Gamecamera.h"


Gamecamera::Gamecamera()
{
}


Gamecamera::~Gamecamera()
{
}

bool Gamecamera::Load()
{

	m_position = m_player->Get3Dposition(); 
	m_position.z -= 500.0f;
	return true;
}
void Gamecamera::ExecuteTracking()
{
	float kakudo = 0.0f;
	kakudo = acos(m_playerFront.Dot(m_front));
	if (kakudo > (CMath::DegToRad(20.0f)) && m_player->Getangle().Length() > 0.0f&&kakudo < (CMath::DegToRad(100.0f)))
	{
		if (m_angle.Length() <= 0) {
			m_axis = CVector3::Zero();
			m_axis.Cross(m_front, m_playerFront);
			if (m_axis.y >= 0.0f)
			{
				m_axis.y = 1.0f;
			}
			else
			{
				m_axis.y = -1.0f;
			}
			m_angle.y += kakudo / 1.0 *m_axis.y;
			m_reg.SetRotationDeg(m_playerUp, m_angle.y);
			m_reg.Multiply(m_front);
		}
	}
}
void Gamecamera::Update()
{
	m_position = m_player->Get3Dposition();
	UpdateBasisInPlayerSpace();
	m_angle.y = g_pad->GetRStickXF()*5.0f;
	m_angle.x = g_pad->GetRStickYF()*5.0f;
	m_reg = CQuaternion::Identity();
	m_reg.SetRotationDeg(m_playerFront, m_angle.y);
	m_playerFront.Normalize();
	m_reg.Multiply(m_front);
	m_front.Normalize();

	ExecuteTracking();
	
	m_front.Normalize();
	float kakudo2 = acos(m_front.Dot(CVector3::AxisZ()));
	m_reg.SetRotation(m_playerUp, kakudo2);
	m_mRot.MakeRotationFromQuaternion(m_reg);
	m_right.x = m_mRot.m[0][0];
	m_right.y = m_mRot.m[0][1];
	m_right.z = m_mRot.m[0][2];
	m_right.Normalize();
	//m_reg = CQuaternion::Identity();
	//m_reg.SetRotationDeg(m_right, m_angle.x);
	//m_angle.x = max(m_angle.x, -30.0f);
	//m_angle.x = min(m_angle.x, 20.0f);
	//m_reg.Multiply(camerfront);

	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y += 50.0f;
	m_position += m_front * -100.0f;
	m_position.y += 50.0f;
	//m_reg = CQuaternion::Identity();
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	//-nan(ind);
	//g_camera3D.SetUp(m_Up);
	g_camera3D.Update();
}
void Gamecamera::Draw()
{

}
void Gamecamera::UpdateBasisInPlayerSpace()
{
	m_mRot = m_player->GetMatrix();
	//プレイヤーの回転行列の0行目～2行目に
	//プレイヤー座標系の基底軸が入っているので、
	//それを抜き出す。
	m_playerUp.x = m_mRot.m[1][0];
	m_playerUp.y = m_mRot.m[1][1];
	m_playerUp.z = m_mRot.m[1][2];
	m_playerUp.y = 1.0f;
	m_playerFront.x = m_mRot.m[2][0];
	m_playerFront.y = m_mRot.m[2][1];
	m_playerFront.z = m_mRot.m[2][2];
}