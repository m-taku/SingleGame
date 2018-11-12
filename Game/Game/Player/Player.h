#pragma once
#include "character/CharacterController.h"
#include"UI.h"
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
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load();
	/// <summary>
	/// Gameobject����p������Update�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobject����p������Draw�֐�
	/// </summary>
	void Draw();
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
	/*
	*@brief	��]�s����擾
	*@return CMatrix
	*/
	const CMatrix& GetMatrix() const
	{
		return mRot;
	}	
	/*
	*@brief	�X�e�B�b�N�̈ړ���
	*@return CVector3�i�x�N�g���j 
	*/
	const CVector3& Getangle() const
	{
		return m_amount;
	}
	/*
	*@brief	�X�e�B�b�N�̈ړ���
	*@return CVector3�i�x�N�g���j
	*/
	const CVector3& GetFront() const
	{
		return m_Front;
	}
	/*
	*@brief	Gamecamera�̃|�C���^���擾
	*/
	void SetCamera(Gamecamera* camera)
	{
		m_camer = camera;
	}
	UI* Ui = nullptr;
private:
	CharacterController m_collider;						//�L�����N�^�[�R���g���[���[
	SkinModel m_model;									//���f���f�[�^
	CVector3 m_movespeed = CVector3::Zero();			//�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity();	//��]�N�I�[�^�j�I��
	CMatrix mRot;										//��]�s��
	Gamecamera* m_camer = nullptr;						//�J�����̃|�C���^
	CVector3 m_Up = CVector3::AxisY();					//�����
	CVector3 m_Front = CVector3::Zero();				//�O����
	CVector3 m_position = { 0.0f,150.0f,-30.0f };		//���݈ʒu
	CVector3 m_amount = { 0.0f,0.0f,0.0f };				//�X�e�B�b�N�̈ړ���
	float m_kaiten = 0.0f;								//��]�p�x�i���W�A���j
	VectorDraw* vector =nullptr; 
	//CVector3 m_angle = CVector3::Zero();				
	//wchar_t bonename[50];								//���O
	//int bonenum = 0;									
	//int boneNo = 0;
};

