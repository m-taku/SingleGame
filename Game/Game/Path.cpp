#include "stdafx.h"
#include "Path.h"
#include"Navimake.h"


Path::Path()
{
	pathdete = objectManager->FindGO<Navimake>("Navimake");
}


Path::~Path()
{
}
void Path::course(CVector3 sturt, CVector3 end)
{
	m_nuwNo = 0;
	coursepasu.clear();

	int sturtNo = pathdete->Findpos_No(sturt);
	int endNo = pathdete->Findpos_No(end);
	PasDate ka;
	ka.No = sturtNo;
	std::vector<PasDate*> open;
	std::vector<PasDate*> cloas;
	open.push_back(&ka);
	auto p = open[0];
	float CurrentCost = 0.0f;
	if (sturtNo == endNo) {
		coursepasu.push_back(p->No);
		return;
	}
	while (p->No!= endNo)
	{	
		float costnV2 = FLT_MAX;
		for (auto i = open.begin(); i < open.end(); i++)
		{
			if (((*i)->MoveCost+(*i)->to_DrstinCost) <= costnV2){
				costnV2 = (*i)->MoveCost + (*i)->to_DrstinCost;
				p = *i;
			}
		}
		CurrentCost = p->MoveCost;
		auto ka5 = pathdete->FindLinc(*p,endNo,CurrentCost);
		//auto ka1= ka5.begin();
		//float costng = FLT_MAX;
		//int MinNo = 0;
		cloas.push_back(p);
		for (int j=0;j<3;j++)
		{
			
			if (-1 != ka5[j]->No)
			{
				//if (costng >= p->Estimatecost + ka1[j].Estimatecost)
				//{
				//	costng = p->Estimatecost + ka1[j].Estimatecost;
				//	MinNo = ka1[j].No;
				//}
				open.push_back(ka5[j]);
				for (int k = 0; k < cloas.size(); k++) {
					for (int j = 0; j < 3; j++) {
						if (cloas[k]->No == ka5[j]->No) {
							open.erase(
								std::remove(open.begin(), open.end(), ka5[j]),
								open.end());
							break;
						}
					}
				}
			}
		}
		open.erase(
			std::remove(open.begin(), open.end(), p),
			open.end());
	}
	while (p->No!= sturtNo) {
		coursepasu.push_back(p->No);
		p = p->ParentDate;
	}
	coursepasu.push_back(p->No);
	std::reverse(coursepasu.begin(), coursepasu.end());
	if (coursepasu.size() > 2)
	{
		Smoothing(&coursepasu);
	}
	pathdete->DebugVector(&coursepasu);
}
void Path::Smoothing(std::vector<int>* pasu)
{
	//�X���[�Y�X�^�[�g���̔ԍ�
	std::vector<int> pa;
	int start = (*pasu)[0];
	pa.push_back(start);
	int Next;
	//1��΂���2�Ԗڂ��猟�����J�n�ɂ���B
	for (int i = 2; i < pasu->size(); i++) 
	{
		Next = (*pasu)[i];
		if (pathdete->CollisionTest(start, Next))
		{
			start = (*pasu)[i-1];
			pa.push_back(start);
		}
	}
	pa.push_back(Next);
	*pasu = pa;
}
CVector3 Path::Pathpos()
{
	if (coursepasu.size()-1 > m_nuwNo) {
		return pathdete->FindNo_pos(coursepasu[m_nuwNo++]);
	}
	else
	{
		return pathdete->FindNo_pos(coursepasu[m_nuwNo]);
	}
}