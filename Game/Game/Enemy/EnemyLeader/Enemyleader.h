#pragma once
#include"../../Player/Player.h"
#include "character/CharacterController.h"
#include"Path.h"
#include"Score.h"
#include <array> 
#include"Status.h"
/// <summary>
/// Enemy��1�O���[�v�P�ʂł̓���N���X�B
/// </summary>
class HitObjict;
class Enemy;
class Enemyleader:public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Enemyleader();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Enemyleader();	
	/// <summary>
	/// Gameobject����p�������ŏ��ɌĂ΂��֐��B
	/// </summary>
	/// <returns>
	/// Load������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobject����p���������t���[���Ă΂��֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p�������\���p�֐��B
	/// </summary>
	void Draw() override;
	/// <summary>
	/// Gameobject����p������stop�֐�
	/// </summary>
	void Stop() override;
	/// <summary>
	/// �A�j���[�V�����p��enum�B
	/// </summary>
	enum animation 	{
		idle,		//��~�A�j���[�V����	
		walk,
		animnum		//�A�j���[�V�������
	};
	/// <summary>
	/// �O���[�v�̏�Ԃ�enum�B
	/// </summary>
	enum State{
		group_stop,		//�O���[�v���
		group_move,		
		person,		//�l���
		gathering	//�W�������
	};
	/// <summary>
	/// �|�W�V�����̃Z�b�g�B
	/// </summary>
	/// <param name="Position">
	/// �Z�b�g�������|�W�V�����B(CVector3)
	/// </param>
	void SetPosition(const CVector3& Position)
	{
		m_position = Position;

	}
	/// <summary>
	/// �X�L�����f���C���X�^���X�̎擾�B
	/// �iconst�Ȃ��̂��ߒ��ӁI�I�j
	/// </summary>
	/// <remarks>
	/// �C���X�^���V���O�p�̃f�[�^�J�ڎ��Ɏg�p�B
	/// </remarks>
	/// <returns>
	/// �X�L�����f���̃C���X�^���X�B(SkinModel*)
	/// </returns>
	SkinModel& CopySkinModel()
	{
		return m_model;
	}
	/// <summary>
	/// �v���C���[�̃C���X�^���X�̃Z�b�g�B
	/// </summary>
	/// <param name="player">
	/// �Z�b�g�������v���C���[�̃C���X�^���X�B(Player*)
	/// </param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	/// <summary>
	/// �O���[�v�̏�ԑJ�ځB
	/// </summary>
	/// <param name="steat">
	/// �ύX��������ԁB(Enemyleader::State)
	/// </param>
	void ChangeSteat(State steat)
	{
		m_state = steat;
	}
	/// <summary>
	/// ���[�_�[�̃|�W�V�����̃Q�b�g�B
	/// </summary>
	/// <returns>
	/// ���[�_�[�̃|�W�V�����B(CVector3)
	/// </returns>
	const CVector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// �O���[�v���̔���B
	/// </summary>
	/// <remarks>
	/// ���ׂĂ̓G���W�܂����ꍇ�O���[�v��ԂɂȂ�B
	/// </remarks>
	void RollCall()
	{
		m_ninzuu++;
	}
	/// <summary>
	/// �O���[�v��Ԃł̈ړ��v�Z�����B
	/// </summary>
	void Move();
	/// <summary>
	/// �X�e�[�g���O���[�v�ł̈ړ��ɕύX����
	/// </summary>
	void ChangeGroup_Move()
	{
		if (m_stopcount == 0) {
			m_group_state = group_move;
			m_path->Course(m_position, m_player->Get2DPosition());
			m_nextpos = m_path->PathPos();
		}
	}
	/// <summary>
	/// �X�e�[�g���O���[�v�ł̒�~�ɕύX����
	/// </summary>
	void ChangeGroup_stop(int count)
	{
		if (count != 0) {
			m_group_state = group_stop;
			m_stopcount = count;
		}
	}
	/// <summary>
	/// �X�e�[�g���O���[�v�ł̒�~�ɕύX����
	/// </summary>
	void Stop_count()
	{
		m_stopcount--;
		if(m_stopcount==0)
		{
			m_group_state = group_move;
			m_stopcount = 0;
		}

	}
	/// <summary>
	/// �O���[�v�S�̂������Ă��邩�ǂ���
	/// </summary>
	/// <returns>
	/// true�Ő������Ă܂�
	/// </returns>
	const bool Getlife()
	{
		return m_life;
	}
	/// <summary>
	/// �X�e�[�^�X�̃Z�b�g
	/// </summary>
	/// <param name="Status">
	/// �X�e�[�^�X�N���X�iAbility�j
	/// </param>
	void SetStatus(Ability* Status)
	{
		m_Status = Status;
	}
	/// <summary>
	/// �X�R�A�W�v�N���X�̃Z�b�g
	/// </summary>
	/// <param name="score">
	/// �X�R�A�W�v�N���X�iScore�j
	/// </param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
private:
	SkinModel m_model;											//�C���X�^���V���O�p�̕`��C���X�^���X
	AnimationClip m_animationclip[animnum];						//�A�j���[�V�����N���b�v
	Animation m_animation;										//�A�j���[�V�����̃C���X�^���X
	State m_state = { group_stop };								//�O���[�v�̍��̏��
	State m_group_state = { group_stop };						//�O���[�v�ł̍��̏��
	Ability* m_Status = nullptr;								//�X�e�[�^�X�̃C���X�^���X
	Score* m_Score = nullptr;									//�X�R�A�W�v�N���X�̃C���X�^���X
	Path* m_path=nullptr;									    //�o�H�T���p�̃C���X�^���X
	Player* m_player = nullptr;									//�v���C���[�̃C���X�^���X
	std::list<Enemy*> m_enemy;						            //�G�l�~�[�̃C���X�^���X�iSOLDIER�j
	CVector3 m_position = { 0.0f,100.0f,0.0f };				    //�ˋ�̃��[�_�[�̃|�W�V����
	CVector3 m_nextpos = CVector3::Zero();						//�p�X�ړ��p�̎��|�W�V����
	CVector3 m_movespeed = { 0.0f,0.0f,0.0f };					//�ړ����x
	CVector3 m_oldposition = CVector3::Zero();					//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	CVector3 m_Front = CVector3::Zero();						//�G�l�~�[�̑O����
	CMatrix m_Rot;												//�p�x�Ɋւ���s��
	CQuaternion m_angle = CQuaternion::Identity();				//��]�p�x
	int m_fream = 0;											//�ړ������p�̃t���[���v�Z
	int m_remaining = 5;										//�����݂̃G�l�~�[����		
	int m_ninzuu = 0;											//�����݂̃O���[�v��Ԃ̐l���i�W�����Ɏg�p�j
	bool m_life = true;											//�����t���O
	int m_stopcount = 0;
	const float m_kaku = 10.0f;									//1�t���[���ŉ�]������ő�p�x(degree)
	const float m_margin = CMath::DegToRad(m_kaku);				//1�t���[���ŉ�]������ő�p�x(radian)
										
};

