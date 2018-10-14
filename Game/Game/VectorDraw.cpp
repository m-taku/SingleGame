#include "stdafx.h"
#include "VectorDraw.h"


VectorDraw::~VectorDraw()
{
}
void VectorDraw::Update(CVector3 posotion, CVector3& Vector, float power)
{
	vector = std::move(Vector);
	Power = power;
	vector.y = 0.0f;
	CQuaternion Rot;
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
	m_vector.UpdateWorldMatrix(m_position, Rot, { 5.0f,Power*1.0f,1.0f });
}
void VectorDraw::Update(std::vector<CVector3>::iterator posotion, std::vector<CVector3>::iterator& Vector, std::vector<float>::iterator power)
{
	int count = 0;
	do {
		vector = *Vector;
		Power = *power;
		vector.y = 0.0f;
		CQuaternion Rot;
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
		m_position = *posotion;
		m_vector.UpdateInstancingData(m_position, Rot, { 5.0f,Power*1.0f,1.0f });
		Vector++;
		posotion++;
		power++;
	} while (++count<m_count);
}
void VectorDraw::Update()
{
	CQuaternion Rot;
	Rot.SetRotationDeg(CVector3::AxisX(), -90.0f);
	m_vector.UpdateWorldMatrix(m_position, Rot, {1.0f,20.0f,1.0f});
}
void VectorDraw::Update(std::vector<CVector3>& posotion)
{
	CQuaternion Rot;
	Rot.SetRotationDeg(CVector3::AxisX(), -90.0f);
	m_vector.BeginUpdateInstancingData();
	for (auto ka = posotion.begin(); ka < posotion.end(); ka++)
	{
	
		m_vector.UpdateInstancingData(*ka, Rot, { 1.0f,20.0f,1.0f });
	}
}
void VectorDraw::Draw()
{
	m_vector.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}