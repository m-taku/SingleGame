#pragma once
/// <summary>
/// �A�C�e���N���X
/// </summary>
class Item:public Gameobject
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
	enum item_group {
		ataac,
		ataacM2,
		defense,
		defenseM2,
		life,
		itemnum
	};
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
	bool Load() override;
	/// <summary>
 	/// ���t���[���Ă΂��֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// �\���p�֐��B
	/// </summary>
	void Draw() override;
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
	bool m_hit = true;											//�����������ǂ���
};