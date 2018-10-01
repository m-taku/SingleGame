#include "stdafx.h"
#include "Navimake.h"


Navimake::Navimake()
{
	m_model.Init(L"Assets/modelData/jimennabi2.cmo");
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = {0.0f,0.0f,0.0f};
	rbInfo.rot = CQuaternion::Identity();
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	g_physics.AddRigidBody(m_rigidBody);
	//メッシュコライダーから頂点バッファとインデックスバッファの情報をGetする
	auto vertex= m_meshCollider.Getvertex(0);
	auto index = m_meshCollider.GetIndex(0);
	for (int i = 0; i <index.size();) {
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
		data->No = (i / 3)-1;
		//できたポリゴン（セル）情報をpush_backする
		seru.push_back(*data);
	}
	//ここからリンク情報の制作
	for (auto Major = seru.begin(); Major != seru.end(); Major++)
	{
		//まず大元になる１つのポリゴン（セル）を決定する
		SData& MajorData = *Major;
		for (auto Former = seru.begin(); Former != seru.end(); Former++)
		{
			const SData& ComparisonData = *Former;
			//大元以外のポリゴン（セル）を検索する
			if (MajorData.No != ComparisonData.No)
			{
				int Commonvertex = 0;
				int vertexNo[2] = { 0 };
				for (int i=0;i<3&&Commonvertex<2;i++)
				{
					//大元のポリゴン（セル）１つの頂点に対して
					CVector3 Majorposition = MajorData.position[i];
					for (int j=0;j<3;j++)
					{
						CVector3 Comparisonposition = ComparisonData.position[j];
						CVector3 distance;
						distance = Comparisonposition - Majorposition;
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
								}
								else if ((vertexNo[0] == 1 && vertexNo[1] == 2)
									|| (vertexNo[1] == 1 && vertexNo[0] == 2)
									) {
									//頂点番号1-2に隣接している面
									MajorData.linkNoList[1] = ComparisonData.No;
								}
								else if ((vertexNo[0] == 0 && vertexNo[1] == 2)
									|| (vertexNo[1] == 0 && vertexNo[0] == 2)
									) {
									//頂点番号0-2に隣接している面
									MajorData.linkNoList[2] = ComparisonData.No;
								}
								break;
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < seru.size(); i++)
	{
		vector.push_back(new VectorDraw(seru[i].position[0]));
		vector.push_back(new VectorDraw(seru[i].position[1]));
		vector.push_back(new VectorDraw(seru[i].position[2]));
		vector.push_back(new VectorDraw(seru[i].centerposition));
	}
	for (int i = 0; i < vector.size(); i++)
	{
		vector[i]->Update();
	}
}


Navimake::~Navimake()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
void Navimake::Up()
{
	for (int i = 0; i < vector.size(); i++)
	{
		vector[i]->Draw();
	}

}
CVector3 Navimake::Searchcenter(const CVector3 (&pos)[3])
{
	CVector3 centerpos=CVector3::Zero();
	centerpos.x = (pos[0].x + pos[1].x + pos[2].x) / 3;

	centerpos.y = (pos[0].y + pos[1].y + pos[2].y) / 3;

	centerpos.z = (pos[0].z + pos[1].z + pos[2].z) / 3;
	return centerpos;
}
