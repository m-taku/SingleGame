#pragma once
/// <summary>
/// Gemeobjectの基底クラス。
/// </summary>
class Gameobject : Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Gameobject();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~Gameobject();
	/// <summary>
	/// 発生した後、データの読み込み、初期化を行う関数。
	/// </summary>
	/// <returns>
	/// trueで終了、falseでロード中。
	/// </returns>
	virtual bool Load() { return true; };
	/// <summary>
	/// Loadが終わった後、毎フレーム呼ばれる関数。
	/// </summary>
	virtual void Update() {};
	/// <summary>
	/// Loadが終わった後、毎フレーム呼ばれる表示関数。
	/// </summary>
	virtual void Draw() {};
	/// <summary>
	/// Drawの後に、毎フレーム呼ばれる表示関数。
	/// </summary>
	virtual void PostDraw() {};
	/// <summary>
	/// オブジェクトの優先度取得。
	/// </summary>
	/// <returns>
	/// オブジェクトの優先度。（int）
	/// </returns>
	int GetPriority()
	{
		return m_priority;
	}
	/// <summary>
	/// オブジェクトの優先度のセット。
	/// </summary>
	/// <param name="No">
	/// オブジェクトの優先度。（int）
	/// </param>
	void SetPriority(int No)
	{
		m_priority = No;
	}
	/// <summary>
	/// Loadが成功しているかどうか。
	/// </summary>
	/// <returns>
	/// Load成功でtrue、失敗またはLoat中はfalse。
	/// </returns>
	bool GetLodefrag() const
	{
		return m_Loadfrag;
	}
	/// <summary>
	/// Loadが成功したかをセット。
	/// </summary>
	/// <param name="frag">
    /// Load成功でtrue、失敗またはLoat中はfalse。
    /// </param>
	void SetLoadfrag(bool frag)
	{
		m_Loadfrag = frag;
	}
	const std::string& GetName()const
	{
		return m_Name;
	}
	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}
private:
	std::string m_Name = "NULL";     	//インスタンスの名前
	int m_priority = 0;					//優先度
	bool m_Loadfrag = false;			//ロード完了したか
};

