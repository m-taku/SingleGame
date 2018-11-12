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
void Gamecamera::Update()
{

	camerfront.Normalize();
	m_position = m_player->Get3Dposition();
	Jiku();
	m_angle.y = g_pad->GetRStickXF()*3.0f;
	m_angle.x = g_pad->GetRStickYF()*3.0f;
	m_reg = CQuaternion::Identity();
	m_reg.SetRotationDeg(m_Up, m_angle.y);
	m_Front.Normalize();
	m_reg.Multiply(camerfront);
	camerfront.Normalize();
	float kakudo = 0.0f;
	kakudo = acos(camerfront.Dot(m_Front));
	if (kakudo > (20.0f*3.14159/180)&& m_player->Getangle().Length()>0.0f&&kakudo <(100.0f*3.14159 / 180))
	{
		if (m_angle.Length() <= 0) {
			m_jiku = CVector3::Zero();
			m_jiku.Cross(camerfront, m_Front);
			if (m_jiku.y >= 0.0f)
			{
				m_jiku.y = 1.0f;
			}
			else
			{
				m_jiku.y = -1.0f;
			}
			m_angle.y += kakudo / 0.5 *m_jiku.y;
			m_reg.SetRotationDeg(m_Up, m_angle.y);
			m_reg.Multiply(camerfront);
		}
	}
	camerfront.Normalize();
	float kakudo2 = acos(camerfront.Dot(CVector3::AxisZ()));
	m_reg.SetRotation(m_Up, kakudo2);
	mRot.MakeRotationFromQuaternion(m_reg);
	m_right.x = mRot.m[0][0];
	m_right.y = mRot.m[0][1];
	m_right.z = mRot.m[0][2];
	m_right.Normalize();
	//m_reg = CQuaternion::Identity();
	//m_reg.SetRotationDeg(m_right, m_angle.x);
	//m_angle.x = max(m_angle.x, -30.0f);
	//m_angle.x = min(m_angle.x, 20.0f);
	//m_reg.Multiply(camerfront);
	camerfront.Normalize();
	m_targetpos = m_player->Get3Dposition();
	m_targetpos.y += 50.0f;
	m_position += camerfront * -100.0f;
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
void Gamecamera::Jiku()
{
	mRot = m_player->GetMatrix();
	m_Up.x = mRot.m[1][0];
	m_Up.y = mRot.m[1][1];
	m_Up.z = mRot.m[1][2];
	m_Up.y = 1.0f;
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
}