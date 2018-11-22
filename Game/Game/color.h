#pragma once
/// <summary>
/// カラークラス
/// </summary>
class Color:public Noncopyable
{
public:
	Color();
	~Color();
	/// <summary>
	/// HSVをRGBに変換する
	/// </summary>
	/// <param name="hsv">HSVのカラー情報。</param>
	/// <returns>HSVをRGBに変換したもの</returns>
	CVector3 HSVtoRGB(const CVector3& hsv);
	/// <summary>
	/// メンバ変数のHSVの値をRGBに変換して返す。
	/// </summary>
	/// <returns>RGBに変換された値</returns>
	CVector4 HSVtoRGB();
private:
	CVector3  m_HSV = { 0.0f,1.0f,0.3f};
};

