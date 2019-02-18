#pragma once
/// <summary>
/// �^�C�}�[�N���X
/// </summary>
class Timer
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Timer();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Timer();
	/// <summary>
	/// �^�C�}�[�̃X�^�[�g
	/// �i������Ă񂾏u�Ԃ���v���j
	/// </summary>
	void TimerStart();
	/// <summary>
	/// �^�C�}�[�����X�^�[�g���܂��B
	/// �i�������Ԃ�ێ������܂܂�����x�X�^�[�g���܂��j
	/// </summary>
	void TimerRestart();
	/// <summary>
	/// �X�g�b�v�֐�
	/// �i�X�g�b�v�E�H�b�`�̃��b�v�̂悤�Ȋ֐��j
	/// </summary>
	void TimerStop();
	/// <summary>
	/// ���b�v�X�^�[�g����̕b��Ԃ�
	/// </summary>
	/// <returns>
	/// �o�ߕb�ifloat�j
	/// </returns>
	float GetSeconds()
	{
		return (float)m_elapsed;
	}
	/// <summary>
	/// ���b�v�X�^�[�g����̕��i���ԁj��Ԃ�
	/// </summary>
	/// <returns>
	/// �o�߁@���i���ԁj�ifloat�j
	/// </returns>
	float GetMinute()
	{
		return m_elapsed / 60.0f;
	}
	/// <summary>
	/// �X�^�[�g����̕b��Ԃ�
	/// �i���b�v�֌W�Ȃ��̂��ׂĂ̍��v�j
	/// </summary>
	/// <returns>
	/// ���v�o�ߕb�ifloat�j
	/// </returns>
	float GetAllSeconds()
	{
		return (float)m_Allelapsed;
	}

	/// <summary>	
	/// �X�^�[�g����̕���Ԃ�
	/// �i���b�v�֌W�Ȃ��̂��ׂĂ̍��v�j
	/// </summary>
	/// <returns>
	/// ���v�o�߁@���i���ԁj(float)
	/// </returns>
	float GetAllMinute()
	{
		return (float)m_Allelapsed / 60.0f;
	}
private:
	LONGLONG m_start = 0;
	LONGLONG m_stop = 0;
	LONGLONG m_fleam = 0;
	double m_elapsed = 0;				//�o�ߎ���(�P�ʁF�b)
	double m_Allelapsed = 0.0;			//���ׂĂ̌o�ߎ���(�P�ʁF�b)
};
