#pragma once
#include"UI.h"
/// <summary>
/// �X�R�A�W�v�N���X
/// </summary>
class Score : public Gameobject
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Score();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Score();
	/// <summary>
	/// Gemeobject����p������Loat�֐��B
	/// </summary>
	/// <returns>
	/// ������true�A���s��false�B
	/// </returns>
	bool Load() override;
	/// <summary>
	/// �X�R�A�̉��Z
	/// </summary>
	void AddScore()
	{
		m_Allscore++;
	}
	/// <summary>
	/// ���݂̃X�R�A�̍��v
	/// </summary>
	/// <returns>
	/// �X�R�A�iint�j
	/// </returns>
	const int GetNum()
	{
		return m_Allscore;
	}

	void Gettime(int& minit, int& second)
	{
		minit = m_minute;
		second = m_seconds;
	}
	/// <summary>
	/// Gameobject����p������Draw�֐�
	/// </summary>
	void PostDraw() override;
private:
	int m_Allscore = 0;
	int m_minute = 0;
	int m_seconds = 0;
	Font m_font;											//�����\���̃C���X�^���X
	Timer m_timer;											//�^�C�}�[�N���X�̃C���X�^���X
};
