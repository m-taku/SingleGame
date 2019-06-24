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
	/// delete処理直後に呼ばれる関数
	/// </summary>
	virtual void OnDestroy() {};
	/// <summary>
	/// アップデートを休止しドローコールのみ動かす際の初期化処理
	/// </summary>
	virtual void Stop() {};
	/// <summary>
	/// アップデートを休止しドローコールのみ動かす際の初期化処理
	/// </summary>
	virtual void StopUpdate() {};
	/// <summary>
	/// アップデートを再開し通常運転に戻る際の初期化処理
	/// </summary>
	virtual void Comeback() {};
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
	/// <summary>
	/// 名前の取得
	/// </summary>
	/// <returns>
	/// 名前（string）
	/// </returns>
	const std::string& GetName()const
	{
		return m_Name;
	}
	/// <summary>
	/// 名前のセット
	/// </summary>
	/// <param name="Name">
	/// 名前（string）
	/// </param>
	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}
	/// <summary>
	/// deleteするときにエンジンで呼ばれる関数
	/// (エンジン側の処理のため外で呼ばないで！！)
	/// </summary>
	void deleteobjiect()
	{
		m_islife = false;			
		OnDestroy();
	}
	/// <summary>
	/// 関数にストップをかける又は解除する関数
	/// （呼ぶとストップ状態が反転します）
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
	/// 現在のストップの状態
	/// </summary>
	/// <returns>
	/// trueで起動中
	/// </returns>
	bool GetStop()
	{
		return m_stop;
	}
	/// <summary>
	/// 今の生存状態
	/// （delete用のためゲーム側では使用を控えてください）
	/// </summary>
	/// <returns>
	/// trueで生存
	/// </returns>
	bool GetIslife()
	{
		return m_islife;
	}
private:
	std::string m_Name = "NULL";     	//インスタンスの名前
	int m_priority = 0;					//優先度
	bool m_Loadfrag = false;			//ロード完了したか
	bool m_stop = true;					//アップデートをストップさせる
	bool m_islife = true;				//生存フラグ
};