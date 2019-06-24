#pragma once
/// <summary>
/// Gemeobject�̊��N���X�B
/// </summary>
class Gameobject : Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	Gameobject();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	virtual ~Gameobject();
	/// <summary>
	/// ����������A�f�[�^�̓ǂݍ��݁A���������s���֐��B
	/// </summary>
	/// <returns>
	/// true�ŏI���Afalse�Ń��[�h���B
	/// </returns>
	virtual bool Load() { return true; };
	/// <summary>
	/// Load���I�������A���t���[���Ă΂��֐��B
	/// </summary>
	virtual void Update() {};
	/// <summary>
	/// Load���I�������A���t���[���Ă΂��\���֐��B
	/// </summary>
	virtual void Draw() {};
	/// <summary>
	/// Draw�̌�ɁA���t���[���Ă΂��\���֐��B
	/// </summary>
	virtual void PostDraw() {};
	/// <summary>
	/// delete��������ɌĂ΂��֐�
	/// </summary>
	virtual void OnDestroy() {};
	/// <summary>
	/// �A�b�v�f�[�g���x�~���h���[�R�[���̂ݓ������ۂ̏���������
	/// </summary>
	virtual void Stop() {};
	/// <summary>
	/// �A�b�v�f�[�g���x�~���h���[�R�[���̂ݓ������ۂ̏���������
	/// </summary>
	virtual void StopUpdate() {};
	/// <summary>
	/// �A�b�v�f�[�g���ĊJ���ʏ�^�]�ɖ߂�ۂ̏���������
	/// </summary>
	virtual void Comeback() {};
	/// <summary>
	/// �I�u�W�F�N�g�̗D��x�擾�B
	/// </summary>
	/// <returns>
	/// �I�u�W�F�N�g�̗D��x�B�iint�j
	/// </returns>
	int GetPriority()
	{
		return m_priority;
	}
	/// <summary>
	/// �I�u�W�F�N�g�̗D��x�̃Z�b�g�B
	/// </summary>
	/// <param name="No">
	/// �I�u�W�F�N�g�̗D��x�B�iint�j
	/// </param>
	void SetPriority(int No)
	{
		m_priority = No;
	}
	/// <summary>
	/// Load���������Ă��邩�ǂ����B
	/// </summary>
	/// <returns>
	/// Load������true�A���s�܂���Loat����false�B
	/// </returns>
	bool GetLodefrag() const
	{
		return m_Loadfrag;
	}
	/// <summary>
	/// Load���������������Z�b�g�B
	/// </summary>
	/// <param name="frag">
    /// Load������true�A���s�܂���Loat����false�B
    /// </param>
	void SetLoadfrag(bool frag)
	{
		m_Loadfrag = frag;
	}
	/// <summary>
	/// ���O�̎擾
	/// </summary>
	/// <returns>
	/// ���O�istring�j
	/// </returns>
	const std::string& GetName()const
	{
		return m_Name;
	}
	/// <summary>
	/// ���O�̃Z�b�g
	/// </summary>
	/// <param name="Name">
	/// ���O�istring�j
	/// </param>
	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}
	/// <summary>
	/// delete����Ƃ��ɃG���W���ŌĂ΂��֐�
	/// (�G���W�����̏����̂��ߊO�ŌĂ΂Ȃ��ŁI�I)
	/// </summary>
	void deleteobjiect()
	{
		m_islife = false;			
		OnDestroy();
	}
	/// <summary>
	/// �֐��ɃX�g�b�v�������閔�͉�������֐�
	/// �i�ĂԂƃX�g�b�v��Ԃ����]���܂��j
	/// </summary>
	void isStop()
	{
		m_stop = !m_stop;
		if (m_stop)
		{
			Comeback();
		}
		else
		{
			Stop();
		}
	}
	/// <summary>
	/// ���݂̃X�g�b�v�̏��
	/// </summary>
	/// <returns>
	/// true�ŋN����
	/// </returns>
	bool GetStop()
	{
		return m_stop;
	}
	/// <summary>
	/// ���̐������
	/// �idelete�p�̂��߃Q�[�����ł͎g�p���T���Ă��������j
	/// </summary>
	/// <returns>
	/// true�Ő���
	/// </returns>
	bool GetIslife()
	{
		return m_islife;
	}
private:
	std::string m_Name = "NULL";     	//�C���X�^���X�̖��O
	int m_priority = 0;					//�D��x
	bool m_Loadfrag = false;			//���[�h����������
	bool m_stop = true;					//�A�b�v�f�[�g���X�g�b�v������
	bool m_islife = true;				//�����t���O
};