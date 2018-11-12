#pragma once
class Navimake;
/// <summary>
/// パスデータを使った経路探査クラス。
/// </summary>
class Path:Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	Path();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~Path();
	/// <summary>
	/// パスデータのインスタンスセット。
	/// </summary>
	/// <param name="navimake">
	/// パスデータのインスタンス。（Navimake*）
	/// </param>
	void Setpathdete(Navimake* navimake)
	{
		pathdete = navimake;
	}
	/// <summary>
	/// 経路探査+スムージング処理。（やりすぎ注意！！）
	/// </summary>
	/// <param name="sturt">
	/// 初期ポジション。（CVector3）
	/// </param>
	/// <param name="end">
	/// 　目標ポジション。（CVector3）
	/// </param>
	void Course(CVector3 sturt, CVector3 end);
	/// <summary>
	/// メンバ変数を使って次に動く目標位置を取得。(引数なし)
	/// </summary>
	/// <returns>
	/// 目標位置。（CVector3）
	/// </returns>
	CVector3 PathPos();
	//パスのデータ形式
	struct PasDate
	{
		PasDate() {
			LincNo[0] = -1;
			LincNo[1] = -1;
			LincNo[2] = -1;
			MoveCost = 0.0f;
			ParentDate = nullptr;
			to_DrstinCost=0.0f;
			No = -1;
		}
		~PasDate()
		{
			//delete ParentDate;
		}
		int No;						//自身の番号
		int LincNo[3];				//自身からのリンク先番号
		float MoveCost;				//自身の場所まで行くコスト
		float to_DrstinCost;		//自身の場所から目的地までのコスト
		PasDate* ParentDate;	//親のパステータのポインタ
	};
	/// <summary>
	/// パスデータによるスムージング処理。（coursepasuを変更）
	/// </summary>
	/// <param name="pasu">
	/// 移動パスの集合 。(std::vector(int)*)
	/// </param>
	void Smoothing(std::vector<int>* pasu);
private:
	std::vector<int> coursepasu;							//経路探査の結果（スムージング処理済み）
	Navimake* pathdete = nullptr;							//セル（ポリゴン）のデータ
	int m_nuwNo = 0;										//今何番目のポイントに向かっているか
};

