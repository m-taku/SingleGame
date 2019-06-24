#pragma once
#include"Fade.h"
class Score;
class Gameover :public Gameobject
{
public:
	enum ScoreDoaw
	{
		start,
		toubatu,
		nokorijikann,
		stop
	};
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Gameover();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Gameover();
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// Gameobject����p������Update�֐�
	/// </summary>
	void Update() override;
	/// <summary>
	/// 
	/// </summary>
	void Stop()override;
	/// <summary>
	/// �N���A����̃Z�b�g
	/// </summary>
	/// <param name="flag">
	/// �N���A��false
	/// </param>
	void Setfra(bool flag)
	{
		m_flag = flag;
	}
	/// <summary>
	/// Gameobject����p������Draw�֐�
	/// </summary>
	void PostDraw() override;
	void clear();
private:
	ShaderResourceView m_texture_font;							//�Q�[�����[�΂̕����̃��\�[�X
	sprite m_over_font;											//�Q�[�����[�΂̕����̃C���X�^���X
	CVector3 m_pos = { 0.0f,1000.0f,0.0f };						//�Q�[�����[�΂̕����̈ʒu
	Fade m_fade;												//�t�F�[�h�N���X�̃C���X�^���X
	bool m_flag;													//�N���A����
	//��������N���A���̂ݎg�p
	Font* m_font=nullptr;											//�����\���̃C���X�^���X
	Score* m_score = nullptr;
	std::list<wchar_t*> m_scoa;
	ScoreDoaw m_scorenum = start;
	float m_count = 0;
};

