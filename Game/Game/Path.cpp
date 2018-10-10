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
	int sturtNo = pathdete->FindNo_pos(sturt);
	int endNo = pathdete->FindNo_pos(end);
	if (sturtNo == endNo){
		return;
	}
	PasDate ka;
	ka.No = sturtNo;
	std::vector<PasDate*> open;
	std::vector<PasDate*> cloas;
	open.push_back(&ka);
	auto p = open[0];
	float CurrentCost = 0.0f;
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
	Smoothing(&coursepasu);
	pathdete->DebugVector(&coursepasu);
	int ha = 0;
	ha++;
}
void Path::Smoothing(std::vector<int>* pasu)
{
	//スムーズスタート時の番号
	std::vector<int> pa;
	int start = (*pasu)[0];
	pa.push_back(start);
	int Next;
	//1つ飛ばした2番目から検索を開始にする。
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