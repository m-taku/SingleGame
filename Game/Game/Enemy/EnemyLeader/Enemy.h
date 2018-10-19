#pragma once
#include "character/CharacterController.h"
#include"../../Player/Player.h"
#include"Enemyleader.h"
class EnemyState;
class Enemy
{
public:
	Enemy();
	~Enemy();
	bool Load();
	void Update();
	void Draw();
	void postDraw();
	void Setposition(CVector3 position)
	{
		m_position = position;
	} 
	enum State {
		State_Tracking,		//�ǔ���	
		State_Move,			//���s��
		State_Attack		//�U����
	};	
	/*
	*@brief	2�c���W�n�ł̈ʒu
	*@return CVector3
	*/
	CVector3 Get2Dposition()const
	{
		auto position = m_position;
		position.y = 0.0f;
		return position;
	}	
	/*
	*@brief	3�c���W�n�ł̈ʒu
	*@return CVector3
	*/
	CVector3 Get3Dposition()const
	{
		return m_position;
	}
	/*
	*@brief	�ړ��x�N�g��
	*@return CVector3
	*/
	CVector3 Getmove()
	{
		return m_moveVector;
	}
	/*
	*@brief	�ړ��x�N�g��
	*@ CVector3
	*/
	void Setmove(CVector3 speed)
	{
		m_moveVector = speed;
	}
	/*
	*@brief	��]�ʑ�������
	*@ CQuaternion
	*/
	void AddAngle(CQuaternion angle)
	{
		m_angle.Multiply(angle, m_angle);
	
	}
	/*
	*@brief	��]�p�x
	*@return CQuaternion
	*/
	void Setangle(CQuaternion angle)
	{
		m_angle = angle;
	}
	/*
	*@brief	��]�p�x
	*@ CQuaternion
	*/
	CQuaternion Getangle()
	{
		return m_angle;
	}
	/*
	*@brief	�O�����̃x�N�g��
	*@
	*/
	CVector3 Get2DFront()
	{
		m_Front.y = 0;
		m_Front.Normalize();
		return m_Front;
	}
	CVector3 Get3DFront()
	{
		m_Front.Normalize();
		return m_Front;
	}
	/*
	*@brief	�X�e�[�g�̑J��
	*/
	void transitionState(State state);
	/*
	*@brief Enemyleader�̃Z�b�g
	*/
	void SetLeader(Enemyleader* leader)
	{
		Leader = leader;
	}
	/*
	*@brief Player�̃Z�b�g
	*/
	void Setplayer(Player* pla)
	{
		player = pla;
	}
	/*
	*@brief Player�̃Z�b�g
	*/
	void DDraw();
	void Findangle(CVector3 Front);
private:
	void Vectordraw();                              
	EnemyState* m_enemystate=nullptr;						//�G�l�~�[�̃X�e�[�g
	CMatrix mRot;
	State state = State_Tracking;							//�X�e�[�g�̏��
	Enemyleader* Leader = nullptr;							//Leader�̃|�C���^
	Player* player = nullptr;								//Player�̃|�C���^
	CharacterController m_collider;					       //�L�����N�^�[�R���g���[���[
	CVector3 m_position = { 0.0f,150.0f,-30.0f };			//���݈ʒu
	CVector3 m_moveVector =CVector3::Zero();
	CQuaternion m_angle = CQuaternion::Identity();			//��]�p�x
	CQuaternion m_Sprite_angle = CQuaternion::Identity();	//�e�N�X�`���̉�]�p�x
	CVector3 m_Front = CVector3::Zero();					//�G�l�~�[�̑O����
	static const int m_speed = 500;								//�ړ����x
	CVector3 m_Sprite_Front = CVector3::AxisZ()*-1;	        //�e�N�X�`���̑O����
	sprite Sprite_hp;										//�̗͗p��2�c(���g)
	sprite Sprite_fram;										//�̗͗p��2�c(�g)
	float m_HP = 1.0f;										//�g�o�̊���
	ShaderResourceView texture_hp;							//�̗͗p��2�c�f�[�^(���g)
	ShaderResourceView texture_fram;						//�̗͗p��2�c�f�[�^(�g)
	VectorDraw* kasa = nullptr;								//�f�o�b�N�p�̃x�N�g���\��

	static const int kaku = 20;
	float m_margin = CMath::DegToRad(kaku);
}; 

