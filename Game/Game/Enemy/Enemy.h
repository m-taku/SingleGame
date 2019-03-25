#pragma once
#include "character/CharacterController.h"
#include"Player.h"
#include"Path.h"
#include"EnemyLeader/EnemyLeader.h"
#include"Status.h"
class EnemyState;
class HitObjict;
class HitReceive;
/// <summary>
/// Enemy1��1�̂̓���N���X�B
/// </summary>
class Enemy : public Noncopyable
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
	/// �|�X�g�h���[
	/// </summary>
	void postDraw();
	/// <summary>
	/// �G�l�~�[�̃X�e�[�g�i��ԁj��enum�B
	/// </summary>
	enum State {
		State_Move,			//���s��
		State_Attack,		//�U����
		State_Gathering,	//�W����
		State_Hit,			//�U�����󂯂Ă���
		State_Dead			//
	};
	/// <summary>
	/// �A�j���[�V�����p��enum�B
	/// </summary>
	enum animation {
		idle,		//��~�A�j���[�V����
		attack,		//�U���A�j���[�V����
		walk,		//�����A�j���[�V����
		hit,		//�q�b�g�A�j���[�V����
		dead,		//���S�A�j���[�V����
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
	/// �ړ����x�̑J�ځB�����œn���Ă��������i�����l�́Bm_Status��m_Speed�j
	/// </summary>
	/// <param name="speed">
	/// �ύX���������x�̊����B(float�j
	/// </param>
	void SetSpeed(const float& speed)
	{
		auto Speeeeed = m_Status->m_Speed*speed;
		m_speed = Speeeeed;
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
	const CVector3& Get3DFront()const 
	{
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
	void SetLeaderPosition(const CVector3& position)
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
	const CVector3& GetLeaderPosition()const
	{
		return m_Leader->GetPosition();
	}
	/// <summary>
	/// �f�o�b�N�p�̓_�\���֐�
	/// </summary>
	/// <param name="pos">
	/// �\���������_
	/// </param>
	void SetDebugPos(const CVector3& pos)
	{
		m_debugVecor->Update(pos);
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
	void FindAngle(const CVector3& Vector);
	/// <summary>
	/// �|�W�V�����̃Z�b�g�B
	/// </summary>
	/// <param name="position">
	/// �Z�b�g�������|�W�V�����B�iCVector3�j
	/// </param>
	void SetPosition(const CVector3& position)
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
		return m_bolnNo;
	}
	/// <summary>
	///�@�A�j���[�V�����̕ύX
	/// </summary>
	/// <param name="Animation">
	/// �ύX��̃A�j���[�V�����iEnemy::animation�j
	/// </param>
	void ChangeAnimation(animation Animation)
	{
		m_animation.Play(Animation,0.1f);
	}
	/// <summary>
	/// �A�j���[�V�������Đ������ǂ���
	/// </summary>
	/// <returns>
	/// true�ōĐ���
	/// </returns>
	bool GetanimationPlaying()
	{
		return m_animation.IsPlaying();
	}
	/// <summary>
	/// �A�j���[�V�������C�x���g�����ǂ���
	/// </summary>
	/// <returns>
	/// true�ŃC�x���g��
	/// </returns>
	bool GetIsEvent()
	{
		return m_animation.IsEvent();
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
		m_collider.SetPosition(m_position);
	}
	/// <summary>
	/// HitObjict����Ă΂�铖���������̏���
	/// </summary>
	/// <param name="damage">
	/// HitObjict������炦��f�[�^
	/// </param>
	void Hit(float damage);
	/// <summary>
	/// �G�l�~�[�������Ă��邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetLife()
	{
		return m_life;
	}
	/// <summary>
	/// �G�l�~�[�̘r�̍s�������
	/// </summary>
	void FindArm();
	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	void InitAnim();
	/// <summary>
	/// �e�N�X�`���f�[�^�̏�����
	/// </summary>
	void InitTex();
	/// <summary>
	/// �X�e�[�^�X�̃Z�b�g
	/// </summary>
	/// <param name="Status">
	/// �X�e�[�^�X�iAbility*�j
	/// </param>
	void SetStatus(Ability* Status)
	{
		m_Status = Status;
		m_HP = m_Status->m_HP;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const Ability* GetStatus()
	{
		return m_Status;
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
	/// <summary>
	/// HitObjict��delete����
	/// </summary>
	void DeleteHitobj();
	/// <summary>
	/// ���g�����S���鏈��
	/// �i���[�_�[����������̂Ńt���O�̂݁j
	/// </summary>
	void DeleteEnemy()
	{
		m_life = false;
		m_Score->AddScore();
	}
private:
	/// <summary>
	/// �f�o�b�N�p�̃x�N�g���\���B
	/// </summary>
	void DrawDebugVector();
	SkinModel m_model;										//�C���X�^���V���O�����̂P�l�P�l�̃C���X�^���X
	ShaderResourceView m_texture_hp;						//HP�̒��̃e�N�X�`���f�[�^
	ShaderResourceView m_texture_fram;						//HP�̘g�̃e�N�X�`���f�[�^
	CSoundSource m_bgmA;									//BGM�̃C���X�^���X
	State m_state = State_Move;							//�X�e�[�g�̏��
	sprite m_Sprite_hp;										//�̗͗p��2�c(���g)
	sprite m_Sprite_fram;									//�̗͗p��2�c(�g)
	CharacterController m_collider;							//�L�����N�^�[�R���g���[���[
	AnimationClip m_animationclip[animnum];					//�A�j���[�V�����N���b�v
	Animation m_animation;									//�A�j���[�V�����̃C���X�^���X	
	Score* m_Score = nullptr;								//�X�R�A�̃C���X�^���X
	Ability* m_Status = nullptr;							//�X�e�[�^�X�̃C���X�^���X
	Enemyleader* m_Leader = nullptr;						//m_Leader�̃|�C���^
	Player* m_player = nullptr;								//Player�̃|�C���^
	VectorDraw* m_debugVecor = nullptr;						//�f�o�b�N�p�̃x�N�g���\��
	Path m_path;											//�o�H�T���̃C���X�^���X
	EnemyState* m_enemystate = nullptr;						//�G�l�~�[�̃X�e�[�g
	const HitReceive* m_obj;								//�q�b�g�I�u�W�F�N�g�̃C���X�^���X
	CMatrix m_Rot;											//�p�x�Ɋւ���s��
	CVector3 m_Front = CVector3::Zero();					//�G�l�~�[�̑O����
	CVector3 m_position = { 0.0f,150.0f,-30.0f };			//���݈ʒu
	CVector3 m_moveVector = CVector3::Zero();				//�ړ�������x�N�g��
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	        //�e�N�X�`���̑O����
	CVector3 m_nextpos = CVector3::Zero();					//�o�H�T���ŏo�����̃|�W�V����
	CQuaternion m_angle = CQuaternion::Identity();			//��]�p�x
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//�e�N�X�`���̉�]�p�x
	const float m_kaku = 10.0f;								//1�t���[���ŉ�]������ő�p�x(degree)
	const float m_margin = CMath::DegToRad(m_kaku);			//1�t���[���ŉ�]������ő�p�x(radian)
	int m_bolnNo = 0;										//��̃{�[���̔ԍ�
	float m_HP = 1.0f;										//�g�o�̊���
	float m_speed = 0.0f;             				    	//�ړ����x
	int m_mutekitaim = 0;									//���G����									
	bool m_life = true;										//�����t���O
};