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
	Score()
	{

	}
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Score()
	{

	}
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
private:
	int m_Allscore = 0;
};

