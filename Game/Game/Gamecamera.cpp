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

	m_position = player->Get3Dposition(); 
	m_position.z -= 500.0f;
	return true;
}
void Gamecamera::Update()
{

	camerfront.Normalize();
	m_position = player->Get3Dposition();
	Jiku();
	m_angle.y = g_pad->GetRStickXF()*3.0f;
	m_angle.x = g_pad->GetRStickYF()*3.0f;
	m_reg = CQuaternion::Identity();
	m_reg.SetRotationDeg(m_Up, m_angle.y);
	//angle.y = max(angle.y, -30.0f);
	//angle.y = min(angle.y, 20.0f);
	m_Front.Normalize();
	m_reg.Multiply(camerfront);
	float kakudo = acos(camerfront.Dot(m_Front));
	if (kakudo > (20.0f*3.14159/180)&& player->Getangle().Length()>0.0f&&kakudo <(160.0f*3.14159 / 180))
	{
		if (m_angle.Length() <= 0) {
			CVector3 ka;
			ka.Cross(camerfront, m_Front);
			ka.Normalize();
			m_angle.y += kakudo / 0.5f * ka.y;
			m_reg.SetRotationDeg(m_Up, m_angle.y);
			m_reg.Multiply(camerfront);
		}
	}
	float kakudo2 = acos(camerfront.Dot(CVector3::AxisZ()));
	m_reg.SetRotation(m_Up, kakudo2);
	mRot.MakeRotationFromQuaternion(m_reg);
	m_right.x = mRot.m[0][0];
	m_right.y = mRot.m[0][1];
	m_right.z = mRot.m[0][2];
	m_right.Normalize();
	m_Front.y = 0;
	m_reg = CQuaternion::Identity();
	m_reg.SetRotationDeg(m_right, m_angle.x);
	m_angle.x = max(m_angle.x, -30.0f);
	m_angle.x = min(m_angle.x, 20.0f);
	m_reg.Multiply(camerfront);
	m_targetpos = player->Get3Dposition();;
	m_targetpos.y += 100.0f;
	m_position += camerfront * -500.0f;
	m_position.y += 100.0f;
	g_camera3D.SetTarget(m_targetpos);
	g_camera3D.SetPosition(m_position);
	//g_camera3D.SetUp(m_Up);
	g_camera3D.Update();
}
void Gamecamera::Draw()
{

}
void Gamecamera::Jiku()
{
	mRot = player->GetMatrix();
	m_Up.x = mRot.m[1][0];
	m_Up.y = mRot.m[1][1];
	m_Up.z = mRot.m[1][2];
	m_Front.x = mRot.m[2][0];
	m_Front.y = mRot.m[2][1];
	m_Front.z = mRot.m[2][2];
}