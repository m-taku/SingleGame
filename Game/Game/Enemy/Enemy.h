#pragma once
#include "character/CharacterController.h"
#include"../Player/Player.h"
#include"../../Path.h"
#include"EnemyLeader/EnemyLeader.h"
class EnemyState;
/// <summary>
/// Enemy1��1�̓���N���X�B
/// </summary>
class Enemy
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Enemy();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Enemy();
	/// <summary>
	/// �ŏ��ɌĂ΂��֐��B
	/// </summary>
	/// <returns>
	/// Load������true�A���s��false�B
	/// </returns>
	bool Load();
	/// <summary>
	/// ���t���[���Ă΂��֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// �\���p�֐��B
	/// </summary>
	void Draw();
	/// <summary>
	/// �|�X�g�[�[�[�[�[�[�[�[�[�[�[
	/// </summary>
	void postDraw();
	/// <summary>
	/// �G�l�~�[�̃X�e�[�g�i��ԁj��enum�B
	/// </summary>
	enum State {
		State_Tracking,		//�ǔ���	
		State_Move,			//���s��
		State_Attack,		//�U����
		State_Gathering		//�W����
	};
	/// <summary>
	/// �A�j���[�V�����p��enum�B
	/// </summary>
	enum animation {
		idle,		//��~�A�j���[�V����
		attack, 
		walk,
		animnum		//�A�j���[�V�������
	};
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
	/// 3D�i���A���A���j�ł̌��݂̃|�W�V�����B
	/// </summary>
	/// <remarks>
	/// 2D�����ŕԂ��֐���������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <returns>
	/// 3D�ł̃|�W�V�����B�iCVector3�j
	/// </returns>
	CVector3 Get3DPosition()const
	{
		return m_position;
	}
	/// <summary>
	/// �ړ����x�̑J�ځB�i�����l��500.0f�j
	/// </summary>
	/// <param name="speed">
	/// �ύX���������x�B�ifloat�j
	/// </param>
	void SetSpeed(const float& speed)
	{
		m_speed = speed;
	}
	/// <summary>
	/// ���f���̉�]�p�x�ւ̉��Z�B
	/// </summary>
	/// <remarks>
	/// ���ڎw�肷��֐�������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <param name="angle">
	/// ���������p�x�̃N�I�[�^�j�I���B�iCQuaternion�j
	/// </param>
	void AddAngle(CQuaternion angle)
	{
		m_angle.Multiply(angle, m_angle);

	}
	/// <summary>
	/// ���f���̉�]�p�x�𒼐ڎw��B
	/// </summary>	
	/// <remarks>
	/// ��]�p�x�Ɋp�x�����Z����֐�������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <param name="angle">
	/// �񂵂����p�x�̃N�I�[�^�j�I���B�iCQuaternion�j
	/// </param>
	void SetAngle(CQuaternion angle)
	{
		m_angle = angle;
	}
	/// <summary>
	/// �����݂̃��f���̉�]�p�x���擾�B
	/// </summary>
	/// <returns>
	/// ���f���̉�]�p�x�B�iCQuaternion�j
	/// </returns>
	CQuaternion GetAngle() const
	{
		return m_angle;
	}
	/// <summary>
	/// 2D�i���A���j�ł̌��݂̑O�����B
	/// </summary>
	/// <remarks>
	/// 3D�����ŕԂ��֐�������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <returns>
	/// 2D�ł̑O�����B
	/// </returns>
	CVector3 Get2DFront()const
	{
		auto front = m_Front;
		front.y = 0;
		front.Normalize();
		return front;
	}
	/// <summary>
	/// 3D�i���A���A���j�ł̌��݂̑O�����B
	/// </summary>
	/// <remarks>
	/// 2D�����ŕԂ��֐�������̂œK���Ă��邩�m�F�B
	/// </remarks>
	/// <returns>
	/// 3D�ł̑O�����B(CVector3)
	/// </returns>
	CVector3 Get3DFront()const 
	{
		//m_Front.Normalize();
		return m_Front;
	}
	/// <summary>
	/// Enemy�̏�ԑJ�ځB
	/// </summary>	
	/// <remarks>
	/// Delete�ANew�����邽�ߏ����d���B
	/// </remarks>
	/// <param name="m_state">
	/// �J�ڂ������X�e�[�g�B�iEnemy::m_state�j
	/// </param>
	void TransitionState(State m_state);
	/// <summary>
	/// �������Ă��郊�[�_�[�̃Z�b�g�B
	/// </summary>
	/// <param name="m_Leader">
	/// ���[�_�[�̃C���X�^���X�B�iEnemyleader*�j
	/// </param>
	void SetLeader(Enemyleader* Leader)
	{
		m_Leader = Leader;
	}
	/// <summary>
	///  �v���C���[�̃C���X�^���X�̃Z�b�g�B
	/// </summary>
	/// <param name="player">
	/// �Z�b�g�������v���C���[�̃C���X�^���X�B(Player*)
	/// </param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	/// <summary>
	/// �������Ă��郊�[�_�[�̏�ԑJ�ځB
	/// </summary>
	/// <param name="m_Leader">
	/// �ύX��������ԁB(Enemyleader::m_state)
	/// </param>
	void ChangeLeaderState(Enemyleader::State m_state)
	{
		m_Leader->ChangeSteat(m_state);
	}
	/// <summary>
	/// �o�H�T���̃C���X�^���X�̃Q�b�g�B
	/// �iconst�Ȃ��̂��ߒ��ӁI�I�I�j
	/// </summary>
	/// <returns>
	/// �o�H�T���̃C���X�^���X�B�iPath*�j
	/// </returns>
	Path* CopyPath()
	{
		return &m_path;
	}
	/// <summary>
	/// �������Ă��郊�[�_�[�ɑ΂��ă|�W�V�������Z�b�g�B
	/// </summary>
	/// <param name="position">
	/// �Z�b�g�������|�W�V�����B�iCVector3�j
	/// </param>
	void SetLeaderPosition(CVector3 position)
	{
		m_Leader->SetPosition(position);
	}
	/// <summary>
	/// �W������ۂ̔���֐��B
	/// </summary>
	void RollCall()
	{
		m_Leader->RollCall();
	}
	/// <summary>
	/// �������Ă��郊�[�_�[�̃|�W�V�����̃Q�b�g�B
	/// </summary>
	/// <returns>
	/// �������Ă��郊�[�_�[�̃|�W�V�����B�iCVector3�j
	/// </returns>
	CVector3 GetLeaderPosition()const
	{
		return m_Leader->GetPosition();
	}
	/// <summary>
	/// HP�o�[�̌v�Z+�\���B
	/// </summary>
	void HP_Draw();
	/// <summary>
	/// ���̃��f���̌����ɑ΂���
	/// �i�s�����́A���x�p�x�����Ă��邩�B
	/// </summary>
	/// <param name="Vector">
	/// �i�s������\���x�N�g���B�iCVector3�j
	/// </param>
	void FindAngle(CVector3 Vector);
	/// <summary>
	/// �|�W�V�����̃Z�b�g�B
	/// </summary>
	/// <param name="position">
	/// �Z�b�g�������|�W�V�����B�iCVector3�j
	/// </param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}
	/// <summary>
	///�@���f���̃C���X�^���X�̃Q�b�g�B
	/// �iconst�Ȃ��̂��ߒ��ӁI�I�I�j
	/// </summary>
	/// <returns>
	/// ���f���̃C���X�^���X�iSkinModel�j
	/// </returns>
	SkinModel& CopyModel()
	{
		return m_model;
	}
	/// <summary>
	/// �r�̈ʒu�̃{�[���ԍ�
	/// </summary>
	/// <returns>
	/// �{�[���ԍ��iint�j
	/// </returns>
	int GetNo()
	{
		return bolnNo;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="Animation"></param>
	void ChangeAnimation(animation Animation)
	{
		m_animation.Play(Animation,0.1);
		//m_animation.Update(0.01f);
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
		//m_collider.SetPosition(m_position);
	}
private:
	/// <summary>
	/// �f�o�b�N�p�̃x�N�g���\���B
	/// </summary>
	void DrawDebugVector();
	SkinModel m_model;										//�C���X�^���V���O�����̂P�l�P�l�̃C���X�^���X
	ShaderResourceView m_texture_hp;						//�̗͗p��2�c�f�[�^(���g)
	ShaderResourceView m_texture_fram;						//�̗͗p��2�c�f�[�^(�g)
	sprite m_Sprite_hp;										//�̗͗p��2�c(���g)
	sprite m_Sprite_fram;									//�̗͗p��2�c(�g)
	//CharacterController m_collider;					        //�L�����N�^�[�R���g���[���[
	AnimationClip m_animationclip[animnum];					//�A�j���[�V�����N���b�v
	Animation m_animation;									//�A�j���[�V�����̃C���X�^���X
	Enemyleader* m_Leader = nullptr;						//m_Leader�̃|�C���^
	Player* m_player = nullptr;								//Player�̃|�C���^
	VectorDraw* m_debugVecor = nullptr;						//�f�o�b�N�p�̃x�N�g���\��
	Path m_path;											//�o�H�T���̃C���X�^���X
	EnemyState* m_enemystate = nullptr;						//�G�l�~�[�̃X�e�[�g
	State m_state = State_Tracking;							//�X�e�[�g�̏��
	CMatrix m_Rot;											//�p�x�Ɋւ���s��
	CVector3 m_position = { 0.0f,150.0f,-30.0f };			//���݈ʒu
	CVector3 m_moveVector = CVector3::Zero();				//�ړ�������x�N�g��
	CVector3 m_Front = CVector3::Zero();					//�G�l�~�[�̑O����
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	        //�e�N�X�`���̑O����
	CVector3 m_oldposition = CVector3::Zero();				//1�t���[���O�̃|�W�V�����i�ǎC��Ȃǂ̔���ȂǂȂǁj
	CVector3 m_nextpos = CVector3::Zero();					//�o�H�T���ŏo�����̃|�W�V����
	CQuaternion m_angle = CQuaternion::Identity();			//��]�p�x
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//�e�N�X�`���̉�]�p�x
	const float m_kaku = 10.0f;								//1�t���[���ŉ�]������ő�p�x(degree)
	const float m_margin = CMath::DegToRad(m_kaku);			//1�t���[���ŉ�]������ő�p�x(radian)
	int bolnNo = 0;
	float m_HP = 1.0f;										//�g�o�̊���
	float m_speed = 0.0f;             					//�ړ����x

};

