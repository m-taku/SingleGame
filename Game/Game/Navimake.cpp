#include "stdafx.h"
#include "Navimake.h"


Navimake::Navimake()
{
	m_model.Init(L"Assets/modelData/jimennabi2.cmo");
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	
	//メッシュコライダーから頂点バッファとインデックスバッファの情報をGetする
	auto vertex= m_meshCollider.Getvertex(0);
	auto index = m_meshCollider.GetIndex(0);
	int No = 0;
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
		seru.push_back(data);
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
		m_collider->Init(Circle.Length()/2,100.0f,data->centerposition);
		g_physics.ContactTest(*m_collider, [&](const btCollisionObject& contactObject)
		{
			frag = true;
		});
		if (frag)
		{
			seru.erase(
				std::remove(seru.begin(), seru.end(), data),
				seru.end());
			No--;
		}
		delete m_collider;		
	}
	//ここからリンク情報の制作
	
	for (auto Major = seru.begin(); Major != seru.end(); Major++)
	{
		//まず大元になる１つのポリゴン（セル）を決定する
		SData& MajorData = *(*Major);
		for (auto Former = seru.begin(); Former != seru.end(); Former++)
		{
			const SData& ComparisonData = **Former;
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
									MajorData.cost[0] = (MajorData.centerposition- ComparisonData.centerposition).Length();
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
	std::vector<CVector3> centerposition;				
	vector = new VectorDraw(seru[0]->centerposition, seru.size());
	for (int i = 0; i < seru.size(); i++)
	{
		centerposition.push_back(seru[i]->centerposition);
	}
	vector->Update(centerposition);
	centerposition.clear();
	std::vector<CVector3> Vectorlist;
	std::vector<float> Vectorpore;
	for (int i = 0; i < seru.size(); i++)
	{
		CVector3 c_position;
		c_position = seru[i]->centerposition;
		for (int j = 0; j < 3; j++) {
			if (seru[i]->linkNoList[j] != -1)
			{
				CVector3 Vector = CVector3::Zero();
				Vector = seru[seru[i]->linkNoList[j]]->centerposition - c_position;
			    centerposition.push_back(c_position);
				Vectorlist.push_back(Vector);
				Vectorpore.push_back(Vector.Length() / 3.0f);
			}
		}
	}
	vector2=new VectorDraw(seru[0]->centerposition, centerposition.size());
	vector2->Update(centerposition.begin(), Vectorlist.begin(), Vectorpore.begin());
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = {0.0f,0.0f,0.0f};
	rbInfo.rot = CQuaternion::Identity();
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	g_physics.AddRigidBody(m_rigidBody);
}


Navimake::~Navimake()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
void Navimake::Up()
{
	vector2->Draw();
	vector->Draw();
}
CVector3 Navimake::Searchcenter(const CVector3 (&pos)[3])
{
	CVector3 centerpos=CVector3::Zero();
	centerpos.x = (pos[0].x + pos[1].x + pos[2].x) / 3;
	centerpos.y = (pos[0].y + pos[1].y + pos[2].y) / 3;
	centerpos.z = (pos[0].z + pos[1].z + pos[2].z) / 3;
	return centerpos;
}
void Navimake::FindnearestNo_No(Path::PasDate& no, int end,float costtttttttt)
{
	float endcost = (seru[end]->centerposition - seru[no.No]->centerposition).Length();
	float Estimatecost = FLT_MAX;
	int l=0;
	for (int i = 0; i < 3; i++) {
		if (seru[no.No]->linkNoList[i] != -1) {
			float costn = seru[no.No]->cost[no.No] + costtttttttt + endcost;
			if (costn <= Estimatecost)
			{
				Estimatecost = costn;

			}
		}
	}
}
