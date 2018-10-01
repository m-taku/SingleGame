#pragma once
#include"physics/MeshCollider.h"
#include "physics/RigidBody.h"
class Navimake
{
public:
	Navimake();
	~Navimake();
	void Up();
	struct SData {
		SData(){
		}
		CVector3				position[3];		//!<三角形1個の座標
		//CVector3				normal;				//!<法線
		CVector3                Halfposition;		//!<辺の半分の長さ
		CVector3				centerposition;		//!<中心座標
		int	                    linkNoList[3];		//!<リンクのリスト
		int                     No;					//!<自分の番号
	};
	CVector3 Searchcenter(const CVector3 (&pos)[3]);
	MeshCollider m_meshCollider;
	SkinModel m_model;									//モデルデータ
	std::vector<SData> seru;							//三角形１つのデータ
	RigidBody m_rigidBody;				//!<剛体。
	std::vector<VectorDraw*> vector;
};

