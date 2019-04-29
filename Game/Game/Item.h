#pragma once
/// <summary>
/// �A�C�e���N���X
/// </summary>
#include"status_sani.h"
enum item_group {
	ataac,
	defense,
	life,
	itemnum
};
class Item:public Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Item();
	/// <summary>
	/// �f�X�g���N�^�B�v
	/// </summary>
	~Item();	
	/// <summary>
	/// �A�C�e���̎�ނ�enum
	/// </summary>

	/// <summary>
	/// �A�C�e���̏o���ʒu�̃Z�b�g
	/// </summary>
	/// <param name="pos">
	/// �A�C�e���̏o���ʒu�iCVector3�j
	/// </param>
	void SetPosition(CVector3 pos)
	{
		m_pos = pos;
	}
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load();
	/// <summary>
 	/// ���t���[���Ă΂��֐��B
	/// </summary>
	bool Update();
	/// <summary>
	/// �\���p�֐��B
	/// </summary>
	void Draw();
	/// <summary>
	/// �A�C�e���̎�ނ̃Z�b�g
	/// �i���Ȃ��Əo�܂���I�I�j
	/// </summary>
	/// <param name="No">
	/// �A�C�e���̎�ނ̃Z�b�g�iItem::item_group�j�Q��
	/// </param>
	void Setitemtype(item_group No)
	{
		m_item = No;
	}
private:	
	SkinModel m_model;											//���f���f�[�^
	Player* m_prayer = nullptr;									//�v���C���[�̃C���X�^���X
	CVector3 m_pos = CVector3::Zero();							//���݈ʒu
	CQuaternion m_rotetion = CQuaternion::Identity();			//���݉�]�p�x
	item_group m_item= itemnum;									//�A�C�e���̎��
	bool m_hit = false;											//�����������ǂ���
	Effekseer::Effect* m_sampleEffect = nullptr;			//�G�t�F�N�g�̎��Ԃ̃|�C���^�i�H�j
	Effekseer::Handle m_playEffectHandle;					//�G�t�F�N�g�̂����n���h��
};