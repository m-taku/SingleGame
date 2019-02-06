#pragma once
#include "character/CharacterController.h"
#include"UI.h"
class Player_State;
class Gamecamera;
class Navimake;
/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player: public Gameobject
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
	struct PlyerStatus
	{
		float Max_HP = 100.0f;				//�}�b�N�X��HP
		float Attack = 10.0f;				//��{�̍U����
		float defense = 10.0f;				//��{�̎����
		float speed = 500.0f;				//
	};
	/// <summary>
	/// �A�j���[�V�����p��enum�B
	/// </summary>
	enum animation {
		ded,
		idle,		//��~�A�j���[�V����
		run,
		hit,
		attack,
		defens,
		walk,
		animnum		//�A�j���[�V�������
	};
	enum State {
		State_Attack,		//�U����
		State_Move,			//
		State_Guard,		//
		State_Hit,
		State_did
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
	/// 
	/// </summary>
	void Hit();
	/// <summary>
	/// 2D�i���A���j�ł̌��݂̃|�W�V�����B
	/// </summary>
	/// <remarks>
	/// 3D�����ŕԂ��֐�������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <returns>
	/// 2D�ł̃|�W�V�����B�iCVector3�j
	/// </returns>
	CVector3 Get2Dposition() const
	{
		auto position = m_position;
		position.y = 0.0f;
		return position;
	} 
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Animation">
	/// 
	/// </param>
	void ChangeAnimation(animation Animation,float taim=0.2f)
	{
		m_animation.Play(Animation, taim);
	}
	void UpdateFront()
	{
		m_mRot.MakeRotationFromQuaternion(m_rotation);
		m_Front.x = m_mRot.m[2][0];
		m_Front.y = m_mRot.m[2][1];
		m_Front.z = m_mRot.m[2][2];
		m_Front.Normalize();
	}
	bool GetanimationPlaying()
	{
		return m_animation.IsPlaying();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Animation">
	/// 
	/// </param>
	//bool AnimationPlaying()
	//{
	//	return m_animation.IsPlaying();
	//}
	/// <summary>
	/// 3D�i���A���A���j�ł̌��݂̃|�W�V�����B
	/// </summary>
	/// <remarks>
	/// 2D�����ŕԂ��֐���������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <returns>
	/// 3D�ł̃|�W�V�����B�iCVector3�j
	/// </returns>
	CVector3 Get3Dposition() const
	{
		return m_position;
	}
	void Setspeed(float speed)
	{
		m_speed = speed;
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
	CVector3 Getangle() const
	{
		return m_amount;
	}
	/// <summary>
	/// ���f���̑O�����B
	/// </summary>
	/// <returns>
	/// �����x�N�g���B�iCVector3�j
	/// </returns>
	CVector3 GetFront() const
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
	/// 
	/// </summary>
	/// <returns></returns>
	Gamecamera* Getcamera()
	{
		return m_camera;
	}
	//�J�����̃|�C���^
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
		
		auto wariai = (damage - m_plyerStatus.defense) / m_plyerStatus.Max_HP;
		/*HP�̍ő�l*/

		//�����łO�`1�̌`�ɕϊ�
		m_ui->SetDamage(wariai);
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
	/// 
	/// </summary>
	void InitAnimation();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="rotation"></param>
	void Setrotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="m_state"></param>
	void TransitionState(State m_state);
private:
	UI* m_ui = nullptr;
	CharacterController m_collider;						//�L�����N�^�[�R���g���[���[
	SkinModel m_model;									//���f���f�[�^
	AnimationClip m_animationclip[animnum];						//�A�j���[�V�����N���b�v
	Animation m_animation;										//�A�j���[�V�����̃C���X�^���X
	CVector3 m_movespeed = CVector3::Zero();			//�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�N�I�[�^�j�I��
	CMatrix m_mRot=CMatrix::Identity();					//��]�s��
	Gamecamera* m_camera = nullptr;						//�J�����̃|�C���^
	CVector3 m_playerUp = CVector3::AxisY();					//�����
	CVector3 m_Front = CVector3::Zero();				//�O����
	CVector3 m_position = { 0.0f,150.0f,-30.0f };		//���݈ʒu
	CVector3 m_amount = { 0.0f,0.0f,0.0f };				//�X�e�B�b�N�̈ړ���
	float m_angle = 0.0f;								//��]�p�x�i���W�A���j
	VectorDraw* m_debugVector =nullptr;					//�f�o�b�N�p�̃x�N�g���\��
	PlyerStatus m_plyerStatus;
	Player_State* m_State = nullptr;
	bool m_ded=false;
	float m_speed = 0.0f;

	//CVector3 m_angle = CVector3::Zero();				
	//wchar_t bonename[50];								//���O
	//int bonenum = 0;									
	//int boneNo = 0;
};

