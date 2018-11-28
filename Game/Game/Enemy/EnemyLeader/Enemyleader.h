#pragma once
#include"../../Player/Player.h"
#include "character/CharacterController.h"
#include"../../Path.h"
#include <array> 
/// <summary>
/// Enemy1�O���[�v�̓���N���X�B
/// </summary>
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
	/// �A�j���[�V�����p��enum�B
	/// </summary>
	enum animation 	{
		idle,		//��~�A�j���[�V����
		attack,
		animnum		//�A�j���[�V�������
	};
	/// <summary>
	/// �O���[�v�̏�Ԃ�enum�B
	/// </summary>
	enum State{
		group,		//�O���[�v���
		person,		//�l���
		gathering	//�W�������
	};
	/// <summary>
	/// �|�W�V�����̃Z�b�g�B
	/// </summary>
	/// <param name="Position">
	/// �Z�b�g�������|�W�V�����B(CVector3)
	/// </param>
	void SetPosition(CVector3 Position)
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
	CVector3 GetPosition()
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
private:
	static const int SOLDIER = 3;								//���[�_�[���܂ޕ����̑����i�萔�j
	CVector3 m_haiti[5] = {
	{ 70.0f,0.0f,0.0f },
	{-70.0f,0.0f,70.0f},
	{-70.0f,0.0f,-70.0f},
	{0.0f,0.0f,70.0f},
	{0.0f,0.0f,0.0f}
	};														    //�����ʒu�̒����̂��߂̐��l			
	CVector3 m_haiti2[5] = {
		{ 70.0f,0.0f,0.0f },
	{ -70.0f,0.0f,70.0f },
	{ -70.0f,0.0f,-70.0f },
	{ 70.0f,0.0f,-70.0f },
	{ 0.0f,0.0f,70.0f }
	};													        //���S����ړ���
	SkinModel m_model;											//�C���X�^���V���O�p�̕`��C���X�^���X
	//CharacterController m_collider;							//�L�����N�^�[�R���g���[���[
	AnimationClip m_animationclip[animnum];						//�A�j���[�V�����N���b�v
	Animation m_animation;										//�A�j���[�V�����̃C���X�^���X
	Path* m_path=nullptr;									    //�o�H�T���p�̃C���X�^���X
	Player* m_player = nullptr;									//�v���C���[�̃C���X�^���X
	std::array<Enemy*, SOLDIER> m_enemy;						//�G�l�~�[�̃C���X�^���X�iSOLDIER�j
	CVector3 m_position = { 0.0f,100.0f,0.0f };				    //�ˋ�̃��[�_�[�̃|�W�V����
	CVector3 m_nextpos = CVector3::Zero();						//�p�X�ړ��p�̎��|�W�V����
	CVector3 m_oldposition = CVector3::Zero();					//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	State m_state = { group };									//�O���[�v�̍��̏��
	int m_remaining = SOLDIER;									//�����݂̃G�l�~�[����		
	int m_ninzuu = 0;											//�����݂̃O���[�v��Ԃ̐l���i�W�����Ɏg�p�j
};

