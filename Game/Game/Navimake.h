#pragma once
#include"physics/MeshCollider.h"
class Navimake
{
public:

	enum {
		CVector3 ka;		//���_�o�b�t�@�B
	}serr;
	Navimake();
	~Navimake();
	MeshCollider m_meshCollider;
	SkinModel m_model;									//���f���f�[�^
	CVector3 vertexpos[3];

	std::vector<CVector3[3]> seru;
};

