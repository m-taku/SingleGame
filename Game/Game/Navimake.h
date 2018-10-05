#pragma once
#include"physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include"character/CharacterController.h"
#include"Path.h"
class Navimake
{
public:
	Navimake();
	~Navimake();
	void Up();
	/*
	*@brief	�|�W�V�������g�����o�X�ԍ�����
	*@return int�i�p�X�ԍ��j
	*/
	int FindNo_pos(CVector3 position)
	{
		CVector3 closepos=CVector3::Zero();
		int No = 0;
		for (int i = 0; i < seru.size(); i++)
		{
			CVector3 pos = position - seru[i]->centerposition;
			if (closepos.Length() <= pos.Length())
			{
				No = seru[i]->No;
				closepos = pos;
			}
		}
		return No;
	}
	void FindnearestNo_No(Path::PasDate& no,int end,float costtttttttt);
private:	
	struct SData {
		//CVector3				normal;				//!<�@��
		CVector3				position[3];		//!<�O�p�`1�̍��W
		CVector3				centerposition;		//!<���S���W
		int	                    linkNoList[3];		//!<�����N�̃��X�g
		int                     No;					//!<�����̔ԍ�
		float                   cost[3];			//!<�����N��ɍs���ۂ̃R�X�g
	};
	CVector3 Searchcenter(const CVector3 (&pos)[3]);	//���_�����߂�֐�
	MeshCollider m_meshCollider;						//
	CharacterController *m_collider = nullptr;			//�L�����N�^�[�R���g���[���[
	SkinModel m_model;									//���f���f�[�^
	std::vector<SData*> seru;							//�O�p�`�P�̃f�[�^
	RigidBody m_rigidBody;			                 	//!<���́B
	VectorDraw* vector;									//���_�`��p�̃f�[�^
	VectorDraw* vector2;								//�����N���\���p�̃f�[�^
};

