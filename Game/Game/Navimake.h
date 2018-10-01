#pragma once
#include"physics/MeshCollider.h"
#include "physics/RigidBody.h"
class Navimake
{
public:
	Navimake();
	~Navimake();
	void Up();
	struct SData {
		SData(){
		}
		CVector3				position[3];		//!<�O�p�`1�̍��W
		//CVector3				normal;				//!<�@��
		CVector3                Halfposition;		//!<�ӂ̔����̒���
		CVector3				centerposition;		//!<���S���W
		int	                    linkNoList[3];		//!<�����N�̃��X�g
		int                     No;					//!<�����̔ԍ�
	};
	CVector3 Searchcenter(const CVector3 (&pos)[3]);
	MeshCollider m_meshCollider;
	SkinModel m_model;									//���f���f�[�^
	std::vector<SData> seru;							//�O�p�`�P�̃f�[�^
	RigidBody m_rigidBody;				//!<���́B
	std::vector<VectorDraw*> vector;
};

