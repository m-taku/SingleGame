#include "stdafx.h"
#include "Navimake.h"


Navimake::Navimake()
{
	m_model.Init(L"Assets/modelData/jimennabi2.cmo");
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	
	//���b�V���R���C�_�[���璸�_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̏���Get����
	auto vertex= m_meshCollider.Getvertex(0);
	auto index = m_meshCollider.GetIndex(0);
	int No = 0;
	for (int i = 0; i < index.size();) {
		//�P�̃|���S���i�Z���j�ɕ�����
		SData* data = new SData;
		data->position[0] = vertex[index[i++]];
		data->position[1] = vertex[index[i++]];
		data->position[2] = vertex[index[i++]];
		//�o�����Z�����璆�S�����߂�B
		data->centerposition = Searchcenter(data->position);
		data->linkNoList[0] = -1;
		data->linkNoList[1] = -1;
		data->linkNoList[2] = -1;
		data->cost[0] = -1;
		data->cost[1] = -1;
		data->cost[2] = -1;
		data->No = No++;
		//�ł����|���S���i�Z���j����push_back����
		seru.push_back(data);
		//��������ContactTest�ɂ��p�X���O����
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
			m_collider->Init(Circle.Length() / 2, 100.0f, data->centerposition);
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
	}
	//�������烊���N���̐���
	
	for (auto Major = seru.begin(); Major != seru.end(); Major++)
	{
		//�܂��匳�ɂȂ�P�̃|���S���i�Z���j�����肷��
		SData& MajorData = *(*Major);
		for (auto Former = seru.begin(); Former != seru.end(); Former++)
		{
			const SData& ComparisonData = **Former;
			//�匳�ȊO�̃|���S���i�Z���j����������
			if (MajorData.No != ComparisonData.No)
			{
				int Commonvertex = 0;
				int vertexNo[2] = { 0 };
				for (int i=0;i<3&&Commonvertex<2;i++)
				{
					//�匳�̃|���S���i�Z���j�P�̒��_�ɑ΂���
					CVector3 Majorposition = MajorData.position[i];
					for (int j=0;j<3;j++)
					{
						CVector3 Comparisonposition = ComparisonData.position[j];
						CVector3 distance;
						distance = Comparisonposition - Majorposition;
						//�����̂��������|���S���i�Z���j���ׂĂ̒��_�Ƌ����𑪂�
						if (distance.Length() <= 0.1f)
						{
							//�v�Z��������������Ȃ��߂��ꍇ��
							//�匳�̒��_�ԍ���ۑ�����
							vertexNo[Commonvertex] = i;
							Commonvertex++;
							//�匳�̒��_�ԍ��̕ۑ����Q�i�����j�ɂȂ�����
							if (Commonvertex == 2)
							{
								//�����N���Ƃ��ĕۑ�����
								if ((vertexNo[0] == 0 && vertexNo[1] == 1)
									|| (vertexNo[1] == 0 && vertexNo[0] == 1)
									) {
									//���_�ԍ�0-1�ɗאڂ��Ă����
									MajorData.linkNoList[0] = ComparisonData.No;
									MajorData.cost[0] = (MajorData.centerposition- ComparisonData.centerposition).Length();
								}
								else if ((vertexNo[0] == 1 && vertexNo[1] == 2)
									|| (vertexNo[1] == 1 && vertexNo[0] == 2)
									) {
									//���_�ԍ�1-2�ɗאڂ��Ă����
									MajorData.linkNoList[1] = ComparisonData.No; 
									MajorData.cost[1] = (MajorData.centerposition - ComparisonData.centerposition).Length();
								}
								else if ((vertexNo[0] == 0 && vertexNo[1] == 2)
									|| (vertexNo[1] == 0 && vertexNo[0] == 2)
									) {
									//���_�ԍ�0-2�ɗאڂ��Ă����
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
	vector.push_back(new VectorDraw(seru[0]->centerposition, seru.size()));
	for (int i = 0; i < seru.size(); i++)
	{
		centerposition.push_back(seru[i]->centerposition);
	}
	vector[vector.size()-1]->Update(centerposition);
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
	//vector.push_back(new VectorDraw(seru[0]->centerposition, centerposition.size()));
	//vector[vector.size()-1]->Update(centerposition.begin(), Vectorlist.begin(), Vectorpore.begin());
	//���̂��쐬�A
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //���̂Ɍ`��(�R���C�_�[)��ݒ肷��B
	rbInfo.mass = 0.0f;
	rbInfo.pos = {0.0f,0.0f,0.0f};
	rbInfo.rot = CQuaternion::Identity();
	m_rigidBody.Create(rbInfo);
	//���̂𕨗����[���h�ɒǉ�����B
	g_physics.AddRigidBody(m_rigidBody);
}


Navimake::~Navimake()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}
void Navimake::Up()
{
	for (int i = 0; i < vector.size(); i++) {
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
const std::vector<Path::PasDate*> Navimake::FindLinc(Path::PasDate& date, int endNo,float cost)const
{
	std::vector<Path::PasDate*> ks;
	ks.resize(3);
	for (int i = 0; i < 3; i++) {
		Path::PasDate* pasDate = new Path::PasDate;
		if (seru[date.No]->linkNoList[i] != -1) {
			pasDate->ParentDate = &date;
			pasDate->No = seru[date.No]->linkNoList[i];
			pasDate->LincNo[0]=  seru[pasDate->No]->linkNoList[0];
			pasDate->LincNo[1] = seru[pasDate->No]->linkNoList[1];
			pasDate->LincNo[2] = seru[pasDate->No]->linkNoList[2];
			pasDate->MoveCost = seru[date.No]->cost[i]+ cost;
			pasDate->to_DrstinCost= (seru[endNo]->centerposition - seru[pasDate->No]->centerposition).Length();
		}
		else
		{
			pasDate->ParentDate = &date;
		}
		ks[i] = pasDate;
	}
	return ks;
}
void Navimake::DebugVector(std::vector<int>* a)
{
	std::vector<CVector3> Vectorlist;
	std::vector<CVector3> centerposition;
	std::vector<float> Vectorpore;
	for (int i = 0; i < a->size() - 1; i++)
	{
		CVector3 c_position;
		c_position = seru[(*a)[i]]->centerposition;
		CVector3 Vector = CVector3::Zero();
		Vector = seru[(*a)[i + 1]]->centerposition - c_position;
		centerposition.push_back(c_position);
		Vectorlist.push_back(Vector);
		Vectorpore.push_back(Vector.Length() / 3.0f);
	}
	vector.push_back(new VectorDraw(seru[0]->centerposition, centerposition.size()));
	vector[vector.size() - 1]->Update(centerposition.begin(), Vectorlist.begin(), Vectorpore.begin());
}
//�X���[�W���O�p�̃R�[���o�b�N�N���X
struct Collision : public btCollisionWorld::ConvexResultCallback
{
	bool NextNo = false; //���̔ԍ�

														//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//�Փ˓_�̖@�������������Ă���B
		//CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
		//������Ɩ@���̂Ȃ��p�x�����߂�B
		//float angle = hitNormalTmp.Dot(CVector3::Up());
		//	angle = fabsf(acosf(angle));
		//	if (angle < CMath::PI * 0.3f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
		//		|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground //�������̓R���W�����������n�ʂƎw�肳��Ă���B
		//		) {
		//		//�Փ˂��Ă���B
		//		isHit = true;
		//		CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
		//		//�Փ˓_�̋��������߂�B�B
		//		CVector3 vDist;
		//		vDist.Subtract(hitPosTmp, startPos);
		//		float distTmp = vDist.Length();
		//		if (dist > distTmp) {
		//			//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
		//			hitPos = hitPosTmp;
		//			hitNormal = *(CVector3*)&convexResult.m_hitNormalLocal;
		//			dist = distTmp;
		//		}
		//	}
		//	return 0.0f;
		//}
		NextNo = true;
		return 0.0f;
	}
};
bool Navimake::CollisionTest(int sturtNo, int nextNo)
{
	//�X���[�Y����ۂ̉��̓����蔻��i�Œ�l�Ȃ񂾂�Ȃ��A�A�A�A�A�j
	m_collide.Create(high, ballsize);
	CVector3 nextPosition = seru[nextNo]->centerposition;
	//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
	CVector3 addPos;
	addPos.Subtract(seru[sturtNo]->centerposition, seru[nextNo]->centerposition);
	CVector3 addPosXZ = addPos;
	addPosXZ.y = 0.0f;
	//���̓����蔻��̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
	CVector3 posTmp = seru[sturtNo]->centerposition;
	posTmp.y += high + ballsize + high * 0.1f;
	//���C���쐬�B
	btTransform start, end;
	start.setIdentity();
	end.setIdentity();
	//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
	start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
	//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
	end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

	Collision callback;
	//�Փˌ��o�B
	g_physics.ConvexSweepTest((const btConvexShape*)m_collide.GetBody(), start, end, callback);
	//�Փ˂������ǂ���
	return callback.NextNo;
}
