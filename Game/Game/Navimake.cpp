#include "stdafx.h"
#include "Navimake.h"
#include "Physics/CollisionAttr.h"


Navimake::Navimake()
{
	m_model.Init(L"Assets/modelData/jimennabi1.cmo");
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	//メッシュコライダーから頂点バッファとインデックスバッファの情報をGetする
	int No = 0;
	for (int i = 0; i < /*m_meshCollider.Getok()*/1; i++) {
		auto vertex = m_meshCollider.Getvertex(i);
		auto index = m_meshCollider.GetIndex(i);
		
		for (int i = 0; i < index.size();) {
			//１つのポリゴン（セル）に分ける
			SData* data = new SData;
			data->position[0] = vertex[index[i++]];
			data->position[1] = vertex[index[i++]];
			data->position[2] = vertex[index[i++]];
			//出来たセルから中心を求める。
			data->centerposition = Searchcenter(data->position);
			data->linkNoList[0] = -1;
			data->linkNoList[1] = -1;
			data->linkNoList[2] = -1;
			data->cost[0] = -1;
			data->cost[1] = -1;
			data->cost[2] = -1;
			data->No = No++;
			//できたポリゴン（セル）情報をpush_backする
			m_seru.push_back(data);
			//ここからContactTestによるパス除外処理
			{
				m_collider = new CharacterController;
				bool frag = false;
				CVector3 Circle;
				Circle = data->position[0] - data->centerposition;
				for (int i = 1; i < 2; i++) {
					if ((data->position[i] - data->centerposition).Length() >= Circle.Length())
					{
						Circle = data->position[i] - data->centerposition;
					}
				}
				//ポリゴン（セル）情報を使ってポリゴンを内包するコリジョン生成
				m_collider->Init(Circle.Length() / 2, 100.0f, data->centerposition);
				g_physics.ContactTest(*m_collider, [&](const btCollisionObject& contactObject)
				{
					frag = true;
				});
				if (frag)
				{
					m_seru.erase(
						std::remove(m_seru.begin(), m_seru.end(), data),
						m_seru.end());
					delete data;
					No--;
				}
				delete m_collider;
			}
			//delete data;
		}
	}
	//ここからリンク情報の制作

	for (auto Major = m_seru.begin(); Major != m_seru.end(); Major++)
	{
		//まず大元になる１つのポリゴン（セル）を決定する
		SData& MajorData = *(*Major);
		for (auto Former = m_seru.begin(); Former != m_seru.end(); Former++)
		{
			const SData& ComparisonData = **Former;
			//大元以外のポリゴン（セル）を検索する
			if (MajorData.No != ComparisonData.No)
			{
				int Commonvertex = 0;
				int vertexNo[2] = { 0 };
				for (int i = 0; i < 3 && Commonvertex < 2; i++)
				{
					//大元のポリゴン（セル）１つの頂点に対して
					CVector3 Majorposition = MajorData.position[i];
					for (int j = 0; j < 3; j++)
					{
						//CVector3 Comparisonposition = ComparisonData.position[j];
						CVector3 distance;
						distance = ComparisonData.position[j] - Majorposition;
						//検索のかかったポリゴン（セル）すべての頂点と距離を測る
						if (distance.Length() <= 0.1f)
						{
							//計算した距離が限りなく近い場合は
							//大元の頂点番号を保存する
							vertexNo[Commonvertex] = i;
							Commonvertex++;
							//大元の頂点番号の保存が２つ（線分）になったら
							if (Commonvertex == 2)
							{
								//リンク情報として保存する
								if ((vertexNo[0] == 0 && vertexNo[1] == 1)
									|| (vertexNo[1] == 0 && vertexNo[0] == 1)
									) {
									//頂点番号0-1に隣接している面
									MajorData.linkNoList[0] = ComparisonData.No;
									MajorData.cost[0] = (MajorData.centerposition - ComparisonData.centerposition).Length();
								}
								else if ((vertexNo[0] == 1 && vertexNo[1] == 2)
									|| (vertexNo[1] == 1 && vertexNo[0] == 2)
									) {
									//頂点番号1-2に隣接している面
									MajorData.linkNoList[1] = ComparisonData.No;
									MajorData.cost[1] = (MajorData.centerposition - ComparisonData.centerposition).Length();
								}
								else if ((vertexNo[0] == 0 && vertexNo[1] == 2)
									|| (vertexNo[1] == 0 && vertexNo[0] == 2)
									) {
									//頂点番号0-2に隣接している面
									MajorData.linkNoList[2] = ComparisonData.No;
									MajorData.cost[2] = (MajorData.centerposition - ComparisonData.centerposition).Length();
								}
								break;
							}
						}
					}
				}
			}
		}
	}
	//ここからデバック用の中点表示
	{
		std::vector<CVector3> centerposition;
		vector.push_back(new VectorDraw(m_seru[0]->centerposition,m_seru.size()));
		for (int i = 0; i < m_seru.size(); i++)
		{
			centerposition.push_back(m_seru[i]->centerposition);
		}
		vector[vector.size() - 1]->Update(centerposition);
	}
	//ここからデバック用のリンク表示
	//{
	//	std::vector<CVector3> centerposition1;
	//	std::vector<CVector3> Vectorlist;
	//	std::vector<float> Vectorpore;
	//	for (int i = 0; i < seru.size(); i++)
	//	{
	//		CVector3 c_position;
	//		c_position = seru[i]->centerposition;
	//		for (int j = 0; j < 3; j++) {
	//			if (seru[i]->linkNoList[j] != -1)
	//			{
	//				CVector3 Vector = CVector3::Zero();
	//				Vector = seru[seru[i]->linkNoList[j]]->centerposition - c_position;
	//				centerposition1.push_back(c_position);
	//				Vectorlist.push_back(Vector);
	//				Vectorpore.push_back(Vector.Length() / 3.0f);
	//			}
	//		}
	//	}
	//	vector.push_back(new VectorDraw(seru[0]->centerposition, centerposition1.size()));
	//	vector[vector.size()-1]->Update(centerposition1.begin(), Vectorlist.begin(), Vectorpore.begin());
	//}
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = { 0.0f,0.0f,0.0f };
	rbInfo.rot = CQuaternion::Identity();
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	g_physics.AddRigidBody(m_rigidBody);

	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}


Navimake::~Navimake()
{
	g_physics.RemoveRigidBody(m_rigidBody);
	for (int i = 0; i < vector.size(); i++)
	{
		delete vector[i];
	}
	for (int i = 0; i < m_seru.size(); i++)
	{
		delete m_seru[i];
	}
	m_seru.clear();

}
void Navimake::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	for (int i = 0; i < vector.size(); i++) {
		vector[i]->Draw();
	}
}
CVector3 Navimake::Searchcenter(const CVector3 (&pos)[3])
{
	//中点計算を行う
	CVector3 centerpos=CVector3::Zero();
	centerpos.x = (pos[0].x + pos[1].x + pos[2].x) / 3;
	centerpos.y = (pos[0].y + pos[1].y + pos[2].y) / 3;
	centerpos.z = (pos[0].z + pos[1].z + pos[2].z) / 3;
	return centerpos;
}
std::vector<Path::PasDate*> Navimake::FindLinc(Path::PasDate& date, int endNo,float cost)const
{
	std::vector<Path::PasDate*> dete;
	dete.resize(3);
	for (int i = 0; i < 3; i++) {
		Path::PasDate* pasDate = new Path::PasDate;
		if (m_seru[date.No]->linkNoList[i] != -1) {
			pasDate->ParentDate = &date;
			pasDate->No = m_seru[date.No]->linkNoList[i];
			pasDate->LincNo[0]= m_seru[pasDate->No]->linkNoList[0];
			pasDate->LincNo[1] = m_seru[pasDate->No]->linkNoList[1];
			pasDate->LincNo[2] = m_seru[pasDate->No]->linkNoList[2];
			pasDate->MoveCost = m_seru[date.No]->cost[i]+ cost;
			pasDate->to_DrstinCost= (m_seru[endNo]->centerposition - m_seru[pasDate->No]->centerposition).Length();
		}
		else
		{
			pasDate->ParentDate = &date;
		}
		dete[i] = pasDate;
		//delete pasDate;
	}
	return dete;
}
void Navimake::DebugVector(const std::vector<int>& posudate)
{
	std::vector<CVector3> Vectorlist;
	std::vector<CVector3> centerposition;
	std::vector<float> Vectorpore;
	for (int i = 0; i < posudate.size() - 1; i++)
	{
		CVector3 c_position;
		c_position = m_seru[posudate[i]]->centerposition;
		CVector3 Vector = CVector3::Zero();
		Vector = m_seru[posudate[i + 1]]->centerposition - c_position;
		centerposition.push_back(c_position);
		Vectorlist.push_back(Vector);
		Vectorpore.push_back(Vector.Length() / 3.0f);
	}
	vector.push_back(new VectorDraw(m_seru[0]->centerposition, centerposition.size()));
	if (centerposition.size() != 1) {
		vector[vector.size() - 1]->Update(centerposition.begin(), Vectorlist.begin(), Vectorpore.begin());
	}
	else
	{
		vector[vector.size() - 1]->Update(centerposition[0], Vectorlist[0], Vectorpore[0]);
	}
}
//スムージング用のコールバッククラス
struct Collision : public btCollisionWorld::ConvexResultCallback
{
	bool NextNo = false; //次の番号

														//衝突したときに呼ばれるコールバック関数。
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) {
			return 0.0f;
		}
		NextNo = true;
		return 0.0f;
	}
};
bool Navimake::CollisionTest(int sturtNo, int nextNo)
{
	//スムーズする際の仮の当たり判定（固定値なんだよなぁ、、、、、）
	
	CapsuleCollider m_collide;						//コライダー。
	m_collide.Create(high, ballsize);
	CVector3 nextPosition = m_seru[nextNo]->centerposition;
	//現在の座標から次の移動先へ向かうベクトルを求める。
	CVector3 addPos;
	addPos.Subtract(m_seru[sturtNo]->centerposition, m_seru[nextNo]->centerposition);
	CVector3 addPosXZ = addPos;
	addPosXZ.y = 0.0f;
	//仮の当たり判定の中心座標 + 高さ*0.1の座標をposTmpに求める。
	CVector3 posTmp = m_seru[sturtNo]->centerposition;
	posTmp.y += high + ballsize + high * 0.1f;
	//レイを作成。
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//始点はカプセルコライダーの中心座標 + 0.2の座標をposTmpに求める。
	start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
	//終点は次の移動先。XZ平面での衝突を調べるので、yはposTmp.yを設定する。
	end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

	Collision callback;
	//衝突検出。
	g_physics.ConvexSweepTest((const btConvexShape*)m_collide.GetBody(), start, end, callback);

	//衝突したかどうか
	return callback.NextNo;
}
