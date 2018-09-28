#pragma once
#include"physics/MeshCollider.h"
class Navimake
{
public:

	enum {
		CVector3 ka;		//頂点バッファ。
	}serr;
	Navimake();
	~Navimake();
	MeshCollider m_meshCollider;
	SkinModel m_model;									//モデルデータ
	CVector3 vertexpos[3];

	std::vector<CVector3[3]> seru;
};

