#pragma once
#include"physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include"character/CharacterController.h"
#include"Path.h"
class Navimake:public Gameobject
{
public:
	Navimake();
	~Navimake();
	void Draw();
	/*
	*@brief	ポジションを使ったバス番号検索
	*@param[in] CVector3(ポジション)
	*@return int（パス番号）
	*/
	int Findpos_No(CVector3 position)
	{
		CVector3 closepos;
		closepos.x = FLT_MAX;
		closepos.y = FLT_MAX;
		closepos.z = FLT_MAX;
		int No = 0;
		for (int i = 0; i < seru.size(); i++)
		{
			CVector3 pos = position - seru[i]->centerposition;
			if (closepos.Length() >= pos.Length())
			{
				No = seru[i]->No;
				closepos = pos;
			}
		}
		return No;
	}
	/*
	*@brief	番号がわかっているときの中心座標検索
	*@param[in]  std::vector<int>
	*@return CVector3
	*/
	CVector3 FindNo_pos(int No)
	{
		return seru[No]->centerposition;
	}
	/*
	*@brief	パスの入った配列を使ったデバック表示用関数
	*@param[in]  std::vector<int>
	*/
	void DebugVector(std::vector<int>* a);
	/*
	*@brief	親のPasDateとコストと目的地を使ってリンクを検索する
	*@return std::vector<Path::PasDate*>[3]（リンク先のPasDate*3）
	*/
	const std::vector<Path::PasDate*> FindLinc(Path::PasDate& date, int endNo,float cost) const;
	/*
	*@brief	スムーズ処理の時の地形との当たり判定
	*@return bool（trueでヒット）
	*/
	bool CollisionTest(int sturtNo, int nextNo);
private:	
	static const int high = 100;
	static const int ballsize = 5;
	struct SData {
		//CVector3				normal;				//!<法線
		CVector3				position[3];		//!<三角形1個の座標
		CVector3				centerposition;		//!<中心座標
		int	                    linkNoList[3];		//!<リンクのリスト
		int                     No;					//!<自分の番号
		float                   cost[3];			//!<リンク先に行く際のコスト
	};
	CVector3 Searchcenter(const CVector3 (&pos)[3]);	//中点を求める関数
	MeshCollider m_meshCollider;						//メッシュ情報
	CharacterController *m_collider = nullptr;			//キャラクターコントローラー
	SkinModel m_model;									//モデルデータ
	std::vector<SData*> seru;							//三角形１つのデータ
	RigidBody m_rigidBody;			                 	//剛体。
	std::vector<VectorDraw*> vector;					//中点描画用のデータ
};

