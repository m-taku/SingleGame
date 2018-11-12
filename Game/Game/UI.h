#pragma once
/// <summary>
/// ���[�U�[�C���^�[�t�F�[�X�N���X�B
/// </summary>
class UI :public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	UI();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~UI();
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load();
	/// <summary>
	/// Gameobject����p������Update�֐��B
	/// </summary>
	void Update();
	/// <summary>
	/// Gameobject����p������Draw�֐��B
	/// </summary>
	void Draw();
	/// <summary>
	/// Gameobject����p������postDraw�֐��B
	/// </summary>
	void postDraw();
	/// <summary>
	/// �v���C���[�ɑ΂���_���[�W�ɂ��Q�[�W�̌�������
	/// </summary>
	/// <param name="damage">
	/// �_���[�W�ʁi1.0���Ŏ��S�j�ifloat�j
	/// </param>
	void SetDamage(float damage)
	{
		m_Damage += damage;
	}
	/// <summary>
	/// �c��̗̑͂��擾�i0.0���`1.0���j
	/// </summary>
	/// <returns>
	/// �c��̗̑́ifloat�j
	/// </returns>
	float GetHP()
	{
		return m_HP;
	}
private:
	ShaderResourceView texture;												//HP�o�[�̘g�̃��\�[�X
	sprite HP_bar_waku;														//HP�o�[�̘g�̕\���p�C���X�^���X
	CVector3 m_HP_waku_position = {-640.0f,-240.0f,0.0f};					//HP�o�[�̘g�̉�ʏ�̈ʒu
	ShaderResourceView Texture;												//HP�o�[�̒��g�̃��\�[�X
	sprite HP_bar;															//HP�o�[�̒��g�̕\���p�C���X�^���X
	CVector3 m_HP_position = { -637.0f,-242.0f,0.0f };						//HP�o�[�̒��g�̉�ʏ�̈ʒu
	float m_Damage = 0.0f;													//�_���[�W��
	float m_HP=1.0f;														//�c��HP			

};

