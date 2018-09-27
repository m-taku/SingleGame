#include "stdafx.h"
#include "VectorDraw.h"


VectorDraw::~VectorDraw()
{
}
void VectorDraw::Update(CVector3 posotion, CVector3 Vector,float power)
{
	vector = Vector;
	Power = power;
	CQuaternion Rot;
	vector.y = 0.0f;
	vector.Normalize();
	float kakuo = acos(vector.Dot(CVector3::AxisZ()));
	kakuo = CMath::RadToDeg(kakuo);
	CVector3 jiku;
	jiku.Cross(CVector3::AxisZ(), vector);
	if (jiku.y > 0.0f)
	{
		Rot.SetRotationDeg(CVector3::AxisY(), kakuo);
	}
	else
	{
		Rot.SetRotationDeg(CVector3::AxisY()*-1, kakuo);
	}
	m_position = posotion;
	m_position.y += 10.0f;
	m_vector.UpdateWorldMatrix(m_position, Rot, { Power*5.0f,Power*5.0f,1.0f });
}
void VectorDraw::Draw()
{
	m_vector.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}