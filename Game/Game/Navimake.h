#pragma once
#include"physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include"character/CharacterController.h"
#include"Path.h"
class Navimake:public Gameobject
{
public:
	Navimake();
	~Navimake();
	void Draw();
	/*
	*@brief	�|�W�V�������g�����o�X�ԍ�����
	*@param[in] CVector3(�|�W�V����)
	*@return int�i�p�X�ԍ��j
	*/
	int Findpos_No(CVector3 position)
	{
		CVector3 closepos;
		closepos.x = FLT_MAX;
		closepos.y = FLT_MAX;
		closepos.z = FLT_MAX;
		int No = 0;
		for (int i = 0; i < seru.size(); i++)
		{
			CVector3 pos = position - seru[i]->centerposition;
			if (closepos.Length() >= pos.Length())
			{
				No = seru[i]->No;
				closepos = pos;
			}
		}
		return No;
	}
	/*
	*@brief	�ԍ����킩���Ă���Ƃ��̒��S���W����
	*@param[in]  std::vector<int>
	*@return CVector3
	*/
	CVector3 FindNo_pos(int No)
	{
		return seru[No]->centerposition;
	}
	/*
	*@brief	�p�X�̓������z����g�����f�o�b�N�\���p�֐�
	*@param[in]  std::vector<int>
	*/
	void DebugVector(std::vector<int>* a);
	/*
	*@brief	�e��PasDate�ƃR�X�g�ƖړI�n���g���ă����N����������
	*@return std::vector<Path::PasDate*>[3]�i�����N���PasDate*3�j
	*/
	const std::vector<Path::PasDate*> FindLinc(Path::PasDate& date, int endNo,float cost) const;
	/*
	*@brief	�X���[�Y�����̎��̒n�`�Ƃ̓����蔻��
	*@return bool�itrue�Ńq�b�g�j
	*/
	bool CollisionTest(int sturtNo, int nextNo);
private:	
	static const int high = 100;
	static const int ballsize = 5;
	struct SData {
		//CVector3				normal;				//!<�@��
		CVector3				position[3];		//!<�O�p�`1�̍��W
		CVector3				centerposition;		//!<���S���W
		int	                    linkNoList[3];		//!<�����N�̃��X�g
		int                     No;					//!<�����̔ԍ�
		float                   cost[3];			//!<�����N��ɍs���ۂ̃R�X�g
	};
	CVector3 Searchcenter(const CVector3 (&pos)[3]);	//���_�����߂�֐�
	MeshCollider m_meshCollider;						//���b�V�����
	CharacterController *m_collider = nullptr;			//�L�����N�^�[�R���g���[���[
	SkinModel m_model;									//���f���f�[�^
	std::vector<SData*> seru;							//�O�p�`�P�̃f�[�^
	RigidBody m_rigidBody;			                 	//���́B
	std::vector<VectorDraw*> vector;					//���_�`��p�̃f�[�^
};

