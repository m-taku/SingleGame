#pragma once
#include "character/CharacterController.h"
#include"UI.h"
#include"Status.h"
#include"status_sani.h"
class Player_State;
class Gamecamera;
class Navimake;
/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Player();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Player();
	const Ability* p_status = new PlyerStatus;
	/// <summary>
	/// �A�j���[�V�����p��enum�B
	/// </summary>
	enum animation {
		walk,		//�����A�j���[�V����
		idle,		//��~�A�j���[�V����
		run,		//����A�j���[�V����
		hit,		//�q�b�g�A�j���[�V����
		ded,		//���S�A�j���[�V����
		defens,		//�h��A�j���[�V����
		attack,		//�U���A�j���[�V����
		combo1,		//�U���A�j���[�V����(�R���{1)
		combo2,		//�U���A�j���[�V����(�R���{2)
		combo3,		//�U���A�j���[�V����(�R���{3)
		animnum		//�A�j���[�V�������
	};
	/// <summary>
	/// ��Ԃ�Enum
	/// </summary>
	enum State {
		State_Attack,		//�U����
		State_Move,			//�ړ���
		State_Guard,		//�h�䒆
		State_Hit,			//�q�b�g��
		State_did			//���S��
	};
	/// <summary>
	/// Gameobject����p������OnDestroy�֐�
	/// </summary>
	void OnDestroy() override;
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobject����p������Update�֐�
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������Draw�֐�
	/// </summary>
	void Draw() override;
	/// <summary>
	/// Gameobject����p������Stop�֐�
	/// </summary>
	void Stop()override;
	/// <summary>
	/// Hit����HitObjict����Ă΂��֐�
	/// </summary>
	void Hit(float damage);
	/// <summary>
	/// 2D�i���A���j�ł̌��݂̃|�W�V�����B
	/// </summary>
	/// <remarks>
	/// 3D�����ŕԂ��֐�������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <returns>
	/// 2D�ł̃|�W�V�����B�iCVector3�j
	/// </returns>
	CVector3 Get2DPosition() const
	{
		auto position = m_position;
		position.y = 0.0f;
		return position;
	}
	/// <summary>
	/// �A�j���[�V�����̕ύX
	/// </summary>
	/// <param name="Animation">
	/// �ς������A�j���[�V����
	/// </param>
	/// <param name="taim">
	/// �ۊǎ��ԁi�w��Ȃ���0.2�j
	/// </param>
	void ChangeAnimation(animation Animation, float taim = 0.2f)
	{
		m_animation.Play(Animation, taim);
	}
	/// <summary>
	/// �A�j���[�V�����C�x���g�̎擾
	/// </summary>
	/// <returns>
	/// teue�ŃC�x���g����
	/// </returns>
	const bool IsEvent(int No=0)
	{
		return m_animation.IsEvent(No);
	}
	/// <summary>
	/// �A�j���[�V�����C�x���g�̎擾
	/// </summary>
	/// <returns>
	/// teue�ŃC�x���g����
	/// </returns>
	const wchar_t* IsEventName()
	{
		return m_animation.GetEventName();
	}
	/// <summary>
	/// �O�����̍X�V�i�p�x�ύX��ɌĂ�ł��������j
	/// </summary>
	void UpdateFront()
	{
		m_mRot.MakeRotationFromQuaternion(m_rotation);
		m_Front.x = m_mRot.m[2][0];
		m_Front.y = m_mRot.m[2][1];
		m_Front.z = m_mRot.m[2][2];
		m_Front.Normalize();
	}
	/// <summary>
	/// �A�j���[�V�������Đ������ǂ���
	/// </summary>
	/// <returns>
	/// true�ōĐ���
	/// </returns>
	const bool GetAnimationPlaying()
	{
		return m_animation.IsPlaying();
	}

	/// <summary>
	/// 3D�i���A���A���j�ł̌��݂̃|�W�V�����B
	/// </summary>
	/// <remarks>
	/// 2D�����ŕԂ��֐���������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <returns>
	/// 3D�ł̃|�W�V�����B�iCVector3�j
	/// </returns>
	const CVector3& Get3DPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �X�s�[�h�̃Z�b�g
	/// </summary>
	/// <param name="speed">
	/// �����Ő��䂵�܂��i1�ōő�j
	/// </param>
	void SetSpeed(float speed)
	{
		m_speed = speed;
	}
	/// <summary>
	/// �X�s�[�h�̃Q�b�g
	/// </summary>
	/// <returns>
	/// �����ŕԂ�܂��i1�ōő�j
	/// </returns>
	const float GetSpeed()const
	{
		return m_speed;
	}
	/// <summary>
	/// ��]�s����擾�B
	/// </summary>
	/// <returns>
	/// ��]�s��B(CMatrix)
	/// </returns>
	const CMatrix& GetMatrix() const
	{
		return m_mRot;
	}
	/// <summary>
	/// �X�e�B�b�N�̈ړ��ʂ̎擾�B
	/// </summary>
	/// <returns>
	/// �ړ��ʂ̃x�N�g���B(CVector3)
	/// </returns>
	const CVector3& GetMoveStick() const
	{
		return m_amount;
	}
	/// <summary>
	/// ���f���̑O�����B
	/// </summary>
	/// <returns>
	/// �����x�N�g���B�iCVector3�j
	/// </returns>
	const CVector3& GetFront() const
	{
		return m_Front;
	}
	/// <summary>
	/// Gamecamera�̃|�C���^���擾�B
	/// </summary>
	/// <param name="camera">
	/// �Z�b�g�������J�����̃C���X�^���X�B(Gamecamera*)
	/// </param>
	void SetCamera(Gamecamera* camera)
	{
		m_camera = camera;
	}
	/// <summary>
	/// �X�e�[�^�X�̃Q�b�g
	/// </summary>
	/// <returns>
	/// �X�e�[�^�X�̃C���X�^���X�iAbility�j
	/// </returns>
	const Ability& GetStatu()
	{
		return *m_plyerStatus;
	}
	/// <summary>
	/// �J�����̃C���X�^���X�̃Q�b�g
	/// </summary>
	/// <returns>
	/// �J�����̃C���X�^���X�iGamecamera*�j
	/// </returns>
	Gamecamera* GetCamera()
	{
		return m_camera;
	}
	/// <summary>
	/// �|�W�V�����̃Z�b�g
	/// </summary>
	/// <param name="position">
	/// �Z�b�g�������|�W�V�����iCVector3�j
	/// </param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
		ChangeColliderPosition(m_position);
	}
	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="damage">
	/// �v���C���[�ɗ^����_���[�W�i�_���[�W�ʂ��̂܂܁j�ifloat�j
	/// </param>
	void Damage(float damage)
	{
		float hidame = damage - m_plyerStatus->m_Defense * GetBairitu(defense1);
		if (hidame > 0.0f) {
			m_plyerStatus->m_HP -= hidame;
			auto wariai = m_plyerStatus->m_HP / p_status->m_HP;
			m_ui->SetDamage(1.0f - wariai);
		}
	}
	/// <summary>
	/// �L�����N�^�[�R���g���[���[�̌��̍X�V
	/// </summary>
	/// <remarks>
	/// �����蔻��͎���Ă��܂���B�����������ł��B
	/// </remarks>
	/// <param name="position">
	/// �X�V��̃|�W�V�����B�iCVector3�j
	/// </param>
	void ChangeColliderPosition(CVector3 position)
	{
		m_collider.SetPosition(position);
	}
	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	void InitAnimation();
	/// <summary>
	/// �p�x�̃Z�b�g
	/// </summary>
	/// <param name="rotation">
	/// �ύX��̊p�x�iCQuaternion�j
	/// </param>
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// �f�o�b�N�p�̓_�\��
	/// </summary>
	/// <param name="pos">
	/// �\���������_�iCVector3�j
	/// </param>
	void SetDebegVector(const CVector3& pos)
	{
		m_debugVector->Update(pos);
	}
	/// <summary>
	/// �X�e�[�g�̑J��
	/// </summary>
	/// <param name="m_state">
	/// �J�ڌ�̃X�e�[�g�iPlayer::State�j
	/// </param>
	void TransitionState(State m_state);
	/// <summary>
	/// �U���p�Ɏ�̃{�[��������
	/// </summary>
	void FindArm();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const CMatrix& GetArmMatrix()
	{
		return m_model.GetSkeleton().GetBone(m_armboneNo)->GetWorldMatrix();
	}
	/// <summary>
	/// �����蔻��𔽓]������
	/// </summary>
	void ReverseHit()
	{
		m_Hit = !m_Hit;
	}
	/// <summary>
	/// �A�j���[�V�����̎�ނ̃Z�b�g
	/// </summary>
	/// <param name="Type">
	/// ���������A�j���[�V����
	/// </param>
	void SetAnimType(animation Type)
	{
		m_animtype = Type;
	}
	/// <summary>
	/// �A�j���[�V�����̎�ނ̃Z�b�g
	/// </summary>
	/// <param name="Type">
	/// ���������A�j���[�V����
	/// </param>
	const animation GetAnimType()
	{
		return m_animtype;
	}
	void ItemTimeUpdate()
	{
		for (int i = 0; i < num; i++) {
			if (m_taim[i].GetAllSeconds() <= 5.0f)
			{
				m_taim[i].TimerStop();
				m_taim[i].TimerRestart();
			}
			else
			{

				auto type = static_cast<Status_bairitu>(i);
				m_ui->SetStetus(type, 0.3f);
				m_bairitu.find(type)->second = 1.0f;
			}
		}
	}
	void SetBairitu(Status_bairitu status,float baisuu)
	{
		m_bairitu.find(status)->second = baisuu;
		m_ui->SetStetus(status, 1.0f);
		m_taim[status].TimerStart();
	}
	const float GetBairitu(Status_bairitu status)
	{
		return m_bairitu.find(status)->second;
	}
	void AddStatu_NowHP(float now_HP)
	{
		m_plyerStatus->m_HP = min(p_status->m_HP, m_plyerStatus->m_HP + now_HP);
		auto wariai = m_plyerStatus->m_HP / p_status->m_HP;
		m_ui->SetDamage(1.0f - wariai);
	}
private:
	CharacterController m_collider;						//�L�����N�^�[�R���g���[���[
	SkinModel m_model;									//���f���f�[�^
	AnimationClip m_animationclip[animnum];				//�A�j���[�V�����N���b�v
	Animation m_animation;								//�A�j���[�V����
	UI* m_ui = nullptr;									//�A�j���[�V�����̃C���X�^���X
	Gamecamera* m_camera = nullptr;						//�J�����̃|�C���^
	VectorDraw* m_debugVector = nullptr;				//�f�o�b�N�p�̃x�N�g���\��
	Player_State* m_State = nullptr;					//�X�e�[�g�̃C���X�^���X
	Ability* m_plyerStatus = new PlyerStatus;			//�X�e�[�^�X
	CVector3 m_movespeed = CVector3::Zero();			//�ړ����x
	CVector3 m_playerUp = CVector3::AxisY();			//�����
	CVector3 m_Front = CVector3::Zero();				//�O����
	CVector3 m_position = { 0.0f,150.0f,-30.0f };		//���݈ʒu
	CVector3 m_amount = { 0.0f,0.0f,0.0f };				//�X�e�B�b�N�̈ړ���
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�N�I�[�^�j�I��
	CMatrix m_mRot = CMatrix::Identity();				//��]�s��
	animation m_animtype = idle;
	int m_armboneNo = -1;								//��̃{�[���ԍ�
	float m_speed = 0.0f;								//�ړ����x
	float m_angle = 0.0f;								//��]�p�x�i���W�A���j
	bool m_Hit = false;									//���Ă��Ԃ��ǂ���
	std::map<Status_bairitu,float> m_bairitu;					//
	Timer m_taim[num];												//
};