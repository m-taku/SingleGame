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
	virtual void postDraw() {};
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
	bool GetLodefrag()
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
private:
	int m_priority = 0;					//�D��x
	bool m_Loadfrag = false;			//���[�h����������
};

