#pragma once
#include "NPCState.h"
class NPCStateMove :public NPCState
{
public:
	NPCStateMove(NPC* enemy_point, const CVector3* pos);
	~NPCStateMove();
	/// <summary>
	/// EnemyState����p�������A�b�v�f�[�g�֐��B
	/// </summary>
	void Update();
private:
	Path * m_path = nullptr;										//�o�H�T���̃C���X�^���X
	CVector3 m_oldposition = CVector3::Zero();					//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	CVector3 m_nextpos = CVector3::Zero();						//�o�H�T���ŏo�����̃|�W�V����
	int m_fream = 0;
};



