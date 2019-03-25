#pragma once
#include"Score.h"
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
	bool Load() override;
	/// <summary>
	/// Gameobject����p������Update�֐��B
	/// </summary>
	void Update() override;
	/// <summary>
	/// Gameobject����p������Draw�֐��B
	/// </summary>
	void Draw() override;
	/// <summary>
	/// Gameobject����p������postDraw�֐��B
	/// </summary>
	void PostDraw() override;
	/// <summary>
	/// �v���C���[�ɑ΂���_���[�W�ɂ��Q�[�W�̌�������
	/// </summary>
	/// <param name="damage">
	/// �_���[�W�ʁi1.0���Ŏ��S�j�ifloat�j
	/// </param>
	void SetDamage(float damage)
	{
		m_Damage = damage;
	}
	/// <summary>
	/// �c��̗̑͂��擾�i0.0���`1.0���j
	/// </summary>
	/// <returns>
	/// �c��̗̑́ifloat�j
	/// </returns>
	const float GetHP() const
	{
		return m_HP- m_Damage;
	}
	/// <summary>
	/// �X�R�A�v�Z�N���X�̃C���X�^���X�Z�b�g
	/// </summary>
	/// <param name="score">
	/// �Z�b�g�������C���X�^���X�iScore*�j
	/// </param>
	void SetScore(Score* score)
	{
		m_Score = score;
	}
private:
	ShaderResourceView m_Texture_bar_waku;					//HP�o�[�̘g�̃��\�[�X
	sprite m_HP_bar_waku;									//HP�o�[�̘g�̕\���p�C���X�^���X
	CVector3 m_HP_waku_position = {-660.0f,-240.0f,0.0f};	//HP�o�[�̘g�̉�ʏ�̈ʒu
	ShaderResourceView m_Texture_bar;						//HP�o�[�̒��g�̃��\�[�X
	sprite m_HP_bar;										//HP�o�[�̒��g�̕\���p�C���X�^���X
	CVector3 m_HP_position = { -657.0f,-242.0f,0.0f };		//HP�o�[�̒��g�̉�ʏ�̈ʒu
	Score* m_Score = nullptr;								//�X�R�A�v�Z�̃N���X�̃C���X�^���X
	Timer m_timer;											//�^�C�}�[�N���X�̃C���X�^���X
	float m_Damage = 0.0f;									//�_���[�W��
	Font m_font;											//�����\���̃C���X�^���X
	float m_HP=1.0f;										//�c��HP�i1�ōő�j			
};

