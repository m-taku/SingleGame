#pragma once
/// <summary>
/// カラークラス
/// </summary>
class Color:public Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Color();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Color();
	/// <summary>
	/// HSVをRGBに変換する
	/// </summary>
	/// <param name="hsv">HSVのカラー情報。</param>
	/// <returns>HSVをRGBに変換したもの</returns>
	static CVector3 HSVtoRGB(const CVector3& hsv);
	/// <summary>
	/// メンバ変数のHSVの値をRGBに変換して返す。
	/// </summary>
	/// <returns>RGBに変換された値</returns>
	CVector4 HSVtoRGB();
	void SetHSV(float color)
	{
		m_HSV.x = color;
	}
private:
	CVector3  m_HSV = { 0.0f,1.0f,1.0f};		//保存しているカラー情報
};

