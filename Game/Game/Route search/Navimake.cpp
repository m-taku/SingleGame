#include "stdafx.h"
#include "Navimake.h"
#include "Physics/CollisionAttr.h"
#include "title.h"


Navimake::Navimake()
{

	auto mode = g_objectManager->FindGO<title>("title");
	wchar_t moveFilePath[256];
	switch (mode->GetMode())
	{
	case title::sturt:
		swprintf_s(moveFilePath, L"Assets/modelData/AAAAAAAAAAAAAA.cmo");
		break;
	case title::test:
		swprintf_s(moveFilePath, L"Assets/modelData/jimennabi%d.cmo", 10);
		break;
	default:
		break;
	}	
	m_model.Init(moveFilePath);
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	//メッシュコライダーから頂点バッファとインデックスバッファの情報をGetする
	int No = 0;
	for (int i = 0; i < m_meshCollider.Getok(); i++) {
		auto vertex = m_meshCollider.Getvertex(i);
		auto index = m_meshCollider.GetIndex(i);
		for (int i = 0; i < index.size();) {
			//１つのポリゴン（セル）に分ける
			SData* data = new SData;
			data->position[0] = vertex[index[i++]];
			data->position[1] = vertex[index[i++]];
			data->position[2] = vertex[index[i++]];
			auto vector1 = data->position[1] - data->position[0];
			auto vector2 = data->position[2] - data->position[0];
			CVector3 jiku;
			vector1.Normalize();
			vector2.Normalize();
			jiku.Cross(vector2, vector1);
			jiku.Normalize();
			float j = acos(jiku.Dot(CVector3::AxisY()));
			if (CMath::DegToRad(45.0f)<=j)
			{
				delete data;
				continue;
			}
			//データの初期化
			data->linkNoList[0] = -1;
			data->linkNoList[1] = -1;
			data->linkNoList[2] = -1;
			data->cost[0] = -1;
			data->cost[1] = -1;
			data->cost[2] = -1;
			data->No = No++;
			//出来たセルから中心を求める。
			data->centerposition = Searchcenter(data->position);
			//できたポリゴン（セル）情報をpush_backする
			m_seru.push_back(data);
			//ここからContactTestによるパス除外処理
			{
				bool frag = false;
				CVector3 Circle;
				Circle = data->position[0] - data->centerposition;
				//できたポリゴンを内包する円の大きさを計算
				for (int i = 1; i < 2; i++) {
					if ((data->position[i] - data->centerposition).Length() >= Circle.Length())
					{
						Circle = data->position[i] - data->centerposition;
					}
				}
				//ポリゴンを内包するコリジョン生成
				CreateRigidBody(Circle.Length() / 2, 10.0f, data->centerposition);
				g_physics.ContactTest(m_rigidBody, [&](const btCollisionObject& contactObject)
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
				g_physics.RemoveRigidBody(m_rigidBody);
				m_collider.Release();
			}
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
		std::vector<CVector3> centerposition;		//中点の入れる配列
		m_vector.push_back(new VectorDraw(m_seru[0]->centerposition,m_seru.size()));
		for (int i = 0; i < m_seru.size(); i++)
		{
			centerposition.push_back(m_seru[i]->centerposition);
		}
		m_vector[m_vector.size() - 1]->Update(centerposition);
	}

	//ここからデバック用のリンク表示
	{
		std::vector<CVector3> centerposition_rinc;		//中点の配列
		std::vector<CVector3> Vectorlist_rinc;			//中点と中点をつなぐベクトルの配列
		std::vector<float> Vectorpore_rinc;				//ベクトルの長さ
		for (int i = 0; i < m_seru.size(); i++)
		{
			CVector3 c_position;
			c_position = m_seru[i]->centerposition;
			for (int j = 0; j < 3; j++) {
				if (m_seru[i]->linkNoList[j] != -1)
				{
					CVector3 Vector = CVector3::Zero();
					Vector = m_seru[m_seru[i]->linkNoList[j]]->centerposition - c_position;
					centerposition_rinc.push_back(c_position);
					Vectorlist_rinc.push_back(Vector);
					Vectorpore_rinc.push_back(Vector.Length() / 3.0f);
				}
			}
		}
		m_vector.push_back(new VectorDraw(m_seru[0]->centerposition, centerposition_rinc.size()));
		m_vector[m_vector.size()-1]->Update(centerposition_rinc.begin(), Vectorlist_rinc.begin(), Vectorpore_rinc.begin());
	}
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = { 0.0f,0.0f,0.0f };
	rbInfo.rot = CQuaternion::Identity();
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	g_physics.AddRigidBody(m_rigidBody);
	m_model.SetShadowReciever(true);
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}


Navimake::~Navimake()
{
	//剛体を物理ワールドから解放する。
	g_physics.RemoveRigidBody(m_rigidBody);
	for (int i = 0; i < m_vector.size(); i++)
	{
		//デバック用のベクトルを使っていればDeleteする
		delete m_vector[i];
	}
	for (int i = 0; i < m_seru.size(); i++)
	{
		//パスデータをすべて削除する
		delete m_seru[i];
	}
	m_seru.clear();
}
void Navimake::Draw()
{
	m_model.SetShadowReciever(true);
	//モデルのDraw
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	for (int i = 0; i < m_vector.size(); i++) {
		//デバック用ベクトルがあれば表示
		m_vector[i]->Draw();
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
const std::vector<Path::PasDate*> Navimake::FindLinc(Path::PasDate& date, int endNo,float cost)const
{
	std::vector<Path::PasDate*> dete;
	dete.resize(3);
	for (int i = 0; i < 3; i++) {
		Path::PasDate* pasDate = new Path::PasDate;
		if (m_seru[date.No]->linkNoList[i] != -1) 
		{
			//リンク情報があればデータのを追加する
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
			//リンク情報がなければ親のみ
			pasDate->ParentDate = &date;
		}
		//データを積む
		dete[i] = pasDate;
	}
	//できたデータを返す
	return dete;
}
void Navimake::DebugVector(const std::vector<int>& posudate)
{
	//経路データ（パス番号データ）をデバック用のデータ作成
	std::vector<CVector3> Vectorlist;			//ベクトルの配列
	std::vector<CVector3> centerposition;		//中点の配列
	std::vector<float> Vectorpore;				//ベクトルの長さ
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
	//できたデータをVectorDrawに挿入
	if (centerposition.size() >= 1) {
		m_vector.push_back(new VectorDraw(m_seru[0]->centerposition, centerposition.size()));
		if (centerposition.size() != 1) {
			m_vector[m_vector.size() - 1]->Update(centerposition.begin(), Vectorlist.begin(), Vectorpore.begin());
		}
		else
		{
			m_vector[m_vector.size() - 1]->Update(centerposition[0], Vectorlist[0], Vectorpore[0]);
		}
	}
}
//スムージング用のコールバッククラス
struct Collision : public btCollisionWorld::ConvexResultCallback
{
	bool NextNo = false; //次の番号

														//衝突したときに呼ばれるコールバック関数。
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//キャラクターは障害物ではない
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
	m_collide.Create(hight, ballsize);
	CVector3 nextPosition = m_seru[nextNo]->centerposition;
	//仮の当たり判定の中心座標 + 高さ*0.1の座標をposTmpに求める。
	CVector3 posTmp = m_seru[sturtNo]->centerposition;
	posTmp.y += hight + ballsize + hight * 0.1f;
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
void Navimake::CreateRigidBody(float radius, float height, const CVector3& position) {
	auto m_position = position;
	//コリジョン作成。
	auto m_radius = radius;
	auto m_height = height;
	m_collider.Create(radius, height);
	//剛体を初期化。
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	g_physics.AddRigidBody(m_rigidBody);
}	