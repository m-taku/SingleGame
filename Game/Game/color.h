#pragma once
/// <summary>
/// �J���[�N���X
/// </summary>
class Color:public Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Color();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Color();
	/// <summary>
	/// HSV��RGB�ɕϊ�����
	/// </summary>
	/// <param name="hsv">HSV�̃J���[���B</param>
	/// <returns>HSV��RGB�ɕϊ���������</returns>
	static CVector3 HSVtoRGB(const CVector3& hsv);
	/// <summary>
	/// �����o�ϐ���HSV�̒l��RGB�ɕϊ����ĕԂ��B
	/// </summary>
	/// <returns>RGB�ɕϊ����ꂽ�l</returns>
	CVector4 HSVtoRGB();
	void SetHSV(float color)
	{
		m_HSV.x = color;
	}
private:
	CVector3  m_HSV = { 0.0f,1.0f,1.0f};		//�ۑ����Ă���J���[���
};

