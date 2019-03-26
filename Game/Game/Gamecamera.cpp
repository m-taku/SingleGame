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
	//プレイヤーの位置からカメラの位置を決定
	m_position = m_player->Get3DPosition(); 
	m_position.y = 10.0f;
	m_position.z -= 200.0f;
	m_targetpos = m_player->Get3DPosition();
	m_targetpos.y = 10.0f;
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	return true;
}
void Gamecamera::ExecuteTracking(CVector3 front)
{
	if (m_player->GetSpeed() > 0.0f) {
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
				m_maxangle.x += max(-5.0f,min(5.0f, CMath::RadToDeg(kakudo)/10.0f * m_nowangle.x));
			}
		}
	}
}
void Gamecamera::Update()
{
	CVector3 front=CVector3::AxisZ();
	UpdateBasisInPlayerSpace();
	//スティックの入力を受け取る
	m_nowangle.x = g_pad->GetRStickXF()*5.0f;
	m_nowangle.y = g_pad->GetRStickYF()*5.0f;
	m_maxangle.x += m_nowangle.x;
	m_reg = CQuaternion::Identity();
	ExecuteTracking(front);
	//回転角度が360を超えたら０度に戻す
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
	//縦軸は上限を設定
	m_maxangle.y += m_nowangle.y;
	m_maxangle.y = min(XMAX, m_maxangle.y);
	m_maxangle.y = max(XMIN, m_maxangle.y);
	CQuaternion m_sk = CQuaternion::Identity();
	m_sk.SetRotationDeg(CVector3::AxisX(), m_maxangle.y);
	front.Normalize();
	m_reg.Multiply(m_sk);
	m_reg.Multiply(front);
	front.Normalize();
	m_front = front;
	//できた角度でカメラの位置を決定
	m_targetpos = m_player->Get3DPosition();
	m_targetpos.y += 50.0f;
	m_position = m_player->Get3DPosition();
	m_position += m_front * -200.0f;
	m_position.y += 140.0f;
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
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
	m_playerFront.x = m_mRot.m[2][0];
	m_playerFront.y = m_mRot.m[2][1];
	m_playerFront.z = m_mRot.m[2][2];
}