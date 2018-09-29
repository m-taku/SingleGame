#pragma once
#include"physics/MeshCollider.h"
class Navimake
{
public:
	Navimake();
	~Navimake();
	struct SData {
		SData(){
		}
		CVector3				position[3];		//!<�O�p�`1�̍��W
		//CVector3				normal;				//!<�@��
		CVector3                Halfposition;		//!<�ӂ̔����̒���
		CVector3				center;				//!<���S���W
		int	                    linkNoList[3];		//!<�����N�̃��X�g
		int                     No;					//!<�����̔ԍ�
	};
	MeshCollider m_meshCollider;
	SkinModel m_model;									//���f���f�[�^
	std::vector<SData> seru;							//�O�p�`�P�̃f�[�^
};

