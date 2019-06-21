#pragma once
#include"Score.h"
#include"status_sani.h"
class Player;
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
	/// �v���C���[��Mp�𑝂₷����
	/// </summary>
	/// <param name="damage">
	/// MP�ʁi1.0����Max�j�ifloat�j
	/// </param>
	void AddMp(float Mp)
	{
		m_MP = Mp;
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
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	void SetStetus(Status_bairitu na,float toumei)
	{
		m_status[na].SetclearColor(toumei);
	}
private:
	ShaderResourceView m_Texture_bar_waku;					//HP�o�[�̘g�̃��\�[�X
	sprite m_HP_bar_waku;									//HP�o�[�̘g�̕\���p�C���X�^���X
	const CVector3 m_HP_waku_position = {-660.0f,-230.0f,0.0f};	//HP�o�[�̘g�̉�ʏ�̈ʒu
	ShaderResourceView m_Texture_bar;						//HP�o�[�̒��g�̃��\�[�X
	sprite m_HP_bar;										//HP�o�[�̒��g�̕\���p�C���X�^���X
	const CVector3 m_HP_position = { -657.0f,-232.0f,0.0f };	//HP�o�[�̒��g�̉�ʏ�̈ʒu
	ShaderResourceView m_texture_status_bar;						//HP�o�[�̒��g�̃��\�[�X
	sprite m_status_bar;										//HP�o�[�̒��g�̕\���p�C���X�^���X
	const CVector3 m_status_bar_position = { -620.0f,-220.0f,0.0f };	//HP�o�[�̒��g�̉�ʏ�̈ʒu
	ShaderResourceView m_Texture_bar_waku_MP;						//MP�o�[�̒��g�̃��\�[�X
	sprite m_MP_bar_waku;										//MP�o�[�̒��g�̕\���p�C���X�^���X
	const CVector3 m_MP_waku_position = { -645.0f,-300.0f,0.0f };	//HP�o�[�̘g�̉�ʏ�̈ʒu
	ShaderResourceView m_Texture_bar_MP;						//MP�o�[�̒��g�̃��\�[�X
	sprite m_MP_bar;										//MP�o�[�̒��g�̕\���p�C���X�^���X
	const CVector3 m_MP_position = { -637.0f,-302.0f,0.0f };	//HP�o�[�̒��g�̉�ʏ�̈ʒu
	ShaderResourceView m_texture_status[num];					//�X�e�[�^�X�J�ڕ\���p�e�N�X�`���̃��\�[�X
	sprite m_status[num];										//�X�e�[�^�X�J�ڕ\���p�e�N�X�`���̃C���X�^���X
	const CVector3 m_status_position[num] = {
		{-620.0f,-210.0f,0.0f},
	{m_status_position[0].x+30.0f,m_status_position[0].y,m_status_position[0].z },
	{ m_status_position[1].x + 30.0f,m_status_position[1].y,m_status_position[1].z} 
	};														//�X�e�[�^�X�J�ڕ\���p�e�N�X�`���̉�ʏ�̈ʒu
	Score* m_Score = nullptr;								//�X�R�A�v�Z�̃N���X�̃C���X�^���X
	Color m_Color_Mp;
	float m_Damage = 0.0f;									//�_���[�W��
	CSoundSource m_bgmA;									//BGM�p�̃C���X�^���X
	bool m_bool = true;
	float m_MP = 0.0f;
	float m_HP=1.0f;										//�c��HP�i1�ōő�j	
	Font m_font;											//�����\���̃C���X�^���X
	Player* m_player = nullptr;
};
