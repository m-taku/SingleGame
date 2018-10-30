#pragma once
class Navimake;
class Path:Noncopyable
{
public:
	Path();
	~Path();
	/*
	*@brief パスデータのインスタンスセット
	*@　Navimake*
	*/
	void Setpathdete(Navimake* navimake)
	{
		pathdete = navimake;
	}
	/*
	*@brief 経路探査+スムージング処理（やりすぎ注意！！）
	*@　CVctor3　sturt,end
	*/
	void course(CVector3 sturt, CVector3 end);
	/*
	*@brief 次に動く目標位置(引数なし)
	*@return CVctor3
	*/
	CVector3 Pathpos();
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
		int No;						//自身の番号
		int LincNo[3];				//自身からのリンク先番号
		float MoveCost;				//自身の場所まで行くコスト
		float to_DrstinCost;		//自身の場所から目的地までのコスト
		PasDate* ParentDate;		//親のパステータのポインタ
	};
	/*
	*@brief パスデータによるスムージング処理（coursepasuを変更）
	*@　std::vector<int>* pasu（いどうぱすの集合）
	*/
	void Smoothing(std::vector<int>* pasu);
private:
	std::vector<int> coursepasu;
	Navimake* pathdete = nullptr;
	int m_nuwNo = 0;
};

