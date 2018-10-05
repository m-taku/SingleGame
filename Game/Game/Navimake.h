#pragma once
#include"physics/MeshCollider.h"
#include "physics/RigidBody.h"
#include"character/CharacterController.h"
#include"Path.h"
class Navimake
{
public:
	Navimake();
	~Navimake();
	void Up();
	/*
	*@brief	ポジションを使ったバス番号検索
	*@return int（パス番号）
	*/
	int FindNo_pos(CVector3 position)
	{
		CVector3 closepos=CVector3::Zero();
		int No = 0;
		for (int i = 0; i < seru.size(); i++)
		{
			CVector3 pos = position - seru[i]->centerposition;
			if (closepos.Length() <= pos.Length())
			{
				No = seru[i]->No;
				closepos = pos;
			}
		}
		return No;
	}
	void FindnearestNo_No(Path::PasDate& no,int end,float costtttttttt);
private:	
	struct SData {
		//CVector3				normal;				//!<法線
		CVector3				position[3];		//!<三角形1個の座標
		CVector3				centerposition;		//!<中心座標
		int	                    linkNoList[3];		//!<リンクのリスト
		int                     No;					//!<自分の番号
		float                   cost[3];			//!<リンク先に行く際のコスト
	};
	CVector3 Searchcenter(const CVector3 (&pos)[3]);	//中点を求める関数
	MeshCollider m_meshCollider;						//
	CharacterController *m_collider = nullptr;			//キャラクターコントローラー
	SkinModel m_model;									//モデルデータ
	std::vector<SData*> seru;							//三角形１つのデータ
	RigidBody m_rigidBody;			                 	//!<剛体。
	VectorDraw* vector;									//中点描画用のデータ
	VectorDraw* vector2;								//リンク情報表示用のデータ
};

