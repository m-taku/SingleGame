#include "stdafx.h"
#include "Navimake.h"


Navimake::Navimake()
{
	m_model.Init(L"Assets/modelData/jimennabi2.cmo");
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	//���̂��쐬�A
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //���̂Ɍ`��(�R���C�_�[)��ݒ肷��B
	rbInfo.mass = 0.0f;
	rbInfo.pos = {0.0f,0.0f,0.0f};
	rbInfo.rot = CQuaternion::Identity();
	m_rigidBody.Create(rbInfo);
	//���̂𕨗����[���h�ɒǉ�����B
	g_physics.AddRigidBody(m_rigidBody);
	//���b�V���R���C�_�[���璸�_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̏���Get����
	auto vertex= m_meshCollider.Getvertex(0);
	auto index = m_meshCollider.GetIndex(0);
	for (int i = 0; i <index.size();) {
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
		data->No = (i / 3)-1;
		//�ł����|���S���i�Z���j����push_back����
		seru.push_back(*data);
	}
	//�������烊���N���̐���
	for (auto Major = seru.begin(); Major != seru.end(); Major++)
	{
		//�܂��匳�ɂȂ�P�̃|���S���i�Z���j�����肷��
		SData& MajorData = *Major;
		for (auto Former = seru.begin(); Former != seru.end(); Former++)
		{
			const SData& ComparisonData = *Former;
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
								}
								else if ((vertexNo[0] == 1 && vertexNo[1] == 2)
									|| (vertexNo[1] == 1 && vertexNo[0] == 2)
									) {
									//���_�ԍ�1-2�ɗאڂ��Ă����
									MajorData.linkNoList[1] = ComparisonData.No;
								}
								else if ((vertexNo[0] == 0 && vertexNo[1] == 2)
									|| (vertexNo[1] == 0 && vertexNo[0] == 2)
									) {
									//���_�ԍ�0-2�ɗאڂ��Ă����
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
