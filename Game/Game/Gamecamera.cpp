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
	m_debugVecor = new VectorDraw(m_position);
	m_position = m_player->Get3Dposition(); 
	m_position.y += 2.0f;
	m_position.z -= 200.0f;
	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y += 2.0f;
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	return true;
}
void Gamecamera::ExecuteTracking()
{
	float kakudo = 0.0f;
	auto ka = m_front;
	ka.y = 0.0f;
	ka.Normalize();
	kakudo = acos(m_playerFront.Dot(ka));
	if (kakudo > (CMath::DegToRad(20.0f)) && m_player->Getangle().Length() > 0.0f&&kakudo < (CMath::DegToRad(100.0f)))
	{
		if (m_angle.Length() <= 0) {
			m_axis = CVector3::Zero();
			m_axis.Cross(m_front, m_playerFront);
			if (m_axis.y >= 0.0f)
			{
				m_nowangle.y = 1.0f;
			}
			else
			{
				m_nowangle.y = -1.0f;
			}
			m_nowangle.y += kakudo / 1.0 *m_nowangle.y;
			m_reg.SetRotationDeg(m_playerUp, m_nowangle.y);
			m_reg.Multiply(m_front);
		}
	}
}
void Gamecamera::Update()
{
	m_front = CVector3::AxisZ();
	UpdateBasisInPlayerSpace();
	m_nowangle.y += g_pad->GetRStickXF()*1.0f;
	m_nowangle.x += g_pad->GetRStickYF()*1.0f;
	m_reg = CQuaternion::Identity();
	m_reg.SetRotationDeg(m_playerUp, m_nowangle.y);
	//m_playerFront.Normalize();
	m_reg.Multiply(m_front);
	ExecuteTracking();
	m_front.Normalize();
	m_reg = CQuaternion::Identity();
	float kakudo2 = acos(m_front.Dot(CVector3::AxisZ()));
	m_reg.SetRotation(m_playerUp, kakudo2);
	m_mRot.MakeRotationFromQuaternion(m_reg);
	m_right.x = m_mRot.m[0][0];
	m_right.y = m_mRot.m[0][1];
	m_right.z = m_mRot.m[0][2];
	m_right.Normalize();
	m_nowangle.x = min(m_nowangle.x, XMAX);
	m_nowangle.x = max(m_nowangle.x, XMIN);
	m_reg = CQuaternion::Identity();
	m_reg.SetRotationDeg(m_right, m_nowangle.x);
	m_front.Normalize();
	m_reg.Multiply(m_front);
	m_front.Normalize();
	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y += 50.0f;
	m_position = m_player->Get3Dposition();
	m_position += m_front * -100.0f;
	m_position.y += 50.0f;
	//m_reg = CQuaternion::Identity();
	//g_camera3D.SetTarget(m_position);
	//g_camera3D.SetPosition(m_targetpos);
	//-nan(ind);
	//g_camera3D.SetUp(m_Up);
	m_debugVecor->Update(m_targetpos, m_position,3.0f);
	g_camera3D.Update();
}
void Gamecamera::Draw()
{
	m_debugVecor->Draw();
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
	//m_playerUp.y = 1.0f;
	m_playerFront.x = m_mRot.m[2][0];
	m_playerFront.y = m_mRot.m[2][1];
	m_playerFront.z = m_mRot.m[2][2];
}