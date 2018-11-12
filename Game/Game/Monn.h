#pragma once
#include"physics/PhysicsStaticObject.h"
/// <summary>
/// �X�e�[�W�̖吧��N���X�B
/// </summary>
class Monn : public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Monn();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Monn();
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
	/// ��]�p�x�̃Z�b�g
	/// </summary>
	/// <param name="rot">
	/// ��]�p�x�iCQuuaternion�j
	/// </param>
	void Setrotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��̊J�������̐���֐�
	/// </summary>
	void Setkaku()
	{
		if (m_kaihei) {
			m_rod *= -1;
			m_kaihei = false;
		}
		else
		{
			m_kaihei = true;
		}
	}
private:
	//PhysicsStaticObject m_monn;			
	SkinModel m_model;											//�X�L�����f���f�[�^
	MeshCollider m_meshCollider;								//���b�V���R���C�_�[�B
	RigidBody m_rigidBody;										//���́B
	CVector3 m_position = CVector3::Zero();						//��̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();			//��̊p�x
	bool m_kaihei = false;										//�J���Ă��邩�ǂ���
	float m_rod = 0.0f;											//�񂷊p�x
	float m_kaku = 0.0f;										//���̊p�x
};

