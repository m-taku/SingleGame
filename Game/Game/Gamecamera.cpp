#include "stdafx.h"
#include "Gamecamera.h"


Gamecamera::Gamecamera()
{
}


Gamecamera::~Gamecamera()
{
	delete m_debugVecor;
	delete m_aebugVecor;
}

bool Gamecamera::Load()
{
	m_debugVecor = new VectorDraw(m_position);
	m_aebugVecor = new VectorDraw(m_position);
	m_position = m_player->Get3Dposition(); 
	m_position.y = 10.0f;
	m_position.z -= 200.0f;
	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y = 10.0f;
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	return true;
}
void Gamecamera::ExecuteTracking()
{
	float kakudo = 0.0f;
	auto front = m_front;
	front.y = 0.0f;
	front.Normalize();
	kakudo = acos(m_playerFront.Dot(front));
	if (kakudo > (CMath::DegToRad(20.0f)) && m_player->Getangle().Length() > 0.0f&&kakudo < (CMath::DegToRad(100.0f)))
	{
		if (m_nowangle.y <= 0|| m_nowangle.x<=0) {
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
	UpdateBasisInPlayerSpace();
	m_nowangle.y = g_pad->GetRStickXF()*5.0f;
	m_nowangle.x = g_pad->GetRStickYF()*5.0f;
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
	m_maxangle += m_nowangle.x;
	m_reg = CQuaternion::Identity();
	if (m_maxangle < XMAX)
	{
		if (m_maxangle > XMIN)
		{
			//m_reg.SetRotationDeg(CVector3::AxisX(), m_nowangle.x);
			//m_front.Normalize();
			//m_reg.Multiply(m_front);
			//CVector3 hoge = CVector3::AxisZ();
			//m_reg.Multiply(hoge);
		}
		else
		{
			m_maxangle = XMIN;
		}
	}
	else
	{
		m_maxangle = XMAX;
	}
	m_front.Normalize();
	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y += 50.0f;
	m_position = m_player->Get3Dposition();
	m_position += m_front * -100.0f;
	m_position.y += 70.0f;
	//m_reg = CQuaternion::Identity();
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	//-nan(ind);
	//g_camera3D.SetUp(m_Up);
	m_debugVecor->Update(m_targetpos,m_front*100,30.0f);
	//m_aebugVecor->Update(m_targetpos, hoge * 100, 30.0f);
	g_camera3D.Update();
}
void Gamecamera::Draw()
{
	
	//m_debugVecor->Draw();
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
	//m_playerUp.y = 1.0f;
	m_playerFront.x = m_mRot.m[2][0];
	m_playerFront.y = m_mRot.m[2][1];
	m_playerFront.z = m_mRot.m[2][2];
}