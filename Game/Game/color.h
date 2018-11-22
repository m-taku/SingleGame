#pragma once
/// <summary>
/// �J���[�N���X
/// </summary>
class Color:public Noncopyable
{
public:
	Color();
	~Color();
	/// <summary>
	/// HSV��RGB�ɕϊ�����
	/// </summary>
	/// <param name="hsv">HSV�̃J���[���B</param>
	/// <returns>HSV��RGB�ɕϊ���������</returns>
	CVector3 HSVtoRGB(const CVector3& hsv);
	/// <summary>
	/// �����o�ϐ���HSV�̒l��RGB�ɕϊ����ĕԂ��B
	/// </summary>
	/// <returns>RGB�ɕϊ����ꂽ�l</returns>
	CVector4 HSVtoRGB();
private:
	CVector3  m_HSV = { 0.0f,1.0f,0.3f};
};

