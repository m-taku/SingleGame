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
	m_position.y = 10.0f;
	m_position.z -= 200.0f;
	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y = 10.0f;
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	return true;
}
void Gamecamera::ExecuteTracking(CVector3 front)
{
	if (m_player->Getspeed() > 0.0f) {
		float kakudo = 0.0f;
		auto front2D = m_front;
		front2D.y = 0.0f;
		front2D.Normalize();
		kakudo = acos(m_playerFront.Dot(front2D));
		if (kakudo > (CMath::DegToRad(20.0f)) && kakudo < (CMath::DegToRad(100.0f)))
		{
			if (m_nowangle.x == 0.0f) {
				m_axis = CVector3::Zero();
				m_axis.Cross(front2D, m_playerFront);
				if (m_axis.y >= 0.0f)
				{
					m_nowangle.x = 1.0f;
				}
				else
				{
					m_nowangle.x = -1.0f;
				}
				m_maxangle.x += CMath::RadToDeg(kakudo)/10.0f * m_nowangle.x;
			}
		}
	}
}
void Gamecamera::Update()
{
	CVector3 front=CVector3::AxisZ();
	UpdateBasisInPlayerSpace();
	m_nowangle.x = g_pad->GetRStickXF()*5.0f;
	m_nowangle.y = g_pad->GetRStickYF()*5.0f;
	m_maxangle.x += m_nowangle.x;
	m_reg = CQuaternion::Identity();
	ExecuteTracking(front);
	if (abs(m_maxangle.x)>=360.0f)
	{
		if (m_maxangle.x <= 0.0f) {
			m_maxangle.x += 360.0f;
		}
		else
		{
			m_maxangle.x -= 360.0f;
		}
	}
	m_reg.SetRotationDeg(CVector3::AxisY(), m_maxangle.x);
	m_maxangle.y += m_nowangle.y;
	m_maxangle.y = min(XMAX, m_maxangle.y);
	m_maxangle.y = max(XMIN, m_maxangle.y);
	CQuaternion m_sk = CQuaternion::Identity();
	m_sk.SetRotationDeg(CVector3::AxisX(), m_maxangle.y);
	front.Normalize();
	m_reg.Multiply(m_reg,m_sk);
	m_reg.Multiply(front);
	front.Normalize();
	m_front = front;
	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y += 50.0f;
	m_position = m_player->Get3Dposition();
	m_position += m_front * -200.0f;
	m_position.y += 140.0f;
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	g_camera3D.Update();
}
void Gamecamera::Draw()
{
	//m_aebugVecor->Draw();
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
	m_playerFront.x = m_mRot.m[2][0];
	m_playerFront.y = m_mRot.m[2][1];
	m_playerFront.z = m_mRot.m[2][2];
}