#include "stdafx.h"
#include "Path.h"
#include"Navimake.h"

Path::Path()
{
	char hoge[] = "Navimake";
	pathdete = objectManager->FindGO<Navimake>(hoge);
}


Path::~Path()
{

}
void Path::Course(CVector3 sturt, CVector3 end)
{
	m_nuwNo = 0;
	coursepasu.clear();

	int sturtNo = pathdete->FindPos_No(sturt);
	int endNo = pathdete->FindPos_No(end);

	PasDate* ka = new PasDate;
	ka->No = sturtNo;
	std::vector<PasDate*> open;
	std::vector<PasDate*> cloas;
	open.push_back(ka);
	auto p = open[0];
	if (sturtNo == endNo) {
		coursepasu.push_back(p->No);
		delete ka;
		return;
	}
	float CurrentCost = 0.0f;

	while (p->No != endNo)
	{
		auto ka5 = pathdete->FindLinc(*p, endNo, CurrentCost);
		//auto ka1= ka5.begin();
		//float costng = FLT_MAX;
		//int MinNo = 0;
		open.erase(
			std::remove(open.begin(), open.end(), p),
			open.end());
		cloas.push_back(p);
		for (int j = 0; j < 3; j++)
		{

			if (-1 != ka5[j]->No)
			{
				open.push_back(ka5[j]);
				for (int k = 0; k < open.size(); k++) {
					if (open[k] == ka5[j])
					{
						break;
					}
					if (open[k]->No == ka5[j]->No) {
						if (open[k]->to_DrstinCost <= ka5[j]->to_DrstinCost)
						{
							delete ka5[j];
							open.erase(
								std::remove(open.begin(), open.end(), ka5[j]),
								open.end());
							break;
						}
						else
						{
							delete open[k];
							open.erase(
								std::remove(open.begin(), open.end(), open[k]),
								open.end());
							break;

						}
					}
				}
				for (int k = 0; k < cloas.size(); k++) {
					if (cloas[k]->No == ka5[j]->No) {
						if (cloas[k]->to_DrstinCost <= ka5[j]->to_DrstinCost) {
							delete  ka5[j];
							open.erase(
								std::remove(open.begin(), open.end(), ka5[j]),
								open.end());
							break;
						}
						else {
							delete cloas[k];
							cloas.erase(
								std::remove(cloas.begin(), cloas.end(), cloas[k]),
								open.end());
							break;
						}
					}
				}
			}
			else
			{
				delete ka5[j];
			}
		}

		if (open.size() <= 0)
		{
			break;
		}
		float costnV2 = FLT_MAX;
		for (auto i = open.begin(); i < open.end(); i++)
		{
			if (((*i)->MoveCost + (*i)->to_DrstinCost) <= costnV2) {
				costnV2 = (*i)->MoveCost + (*i)->to_DrstinCost;
				p = *i;
			}
		}
		CurrentCost = p->MoveCost;
	}

	if (open.size() <= 0)
	{
		coursepasu.push_back(sturtNo);
	}
	else
	{
		while (p->No != sturtNo) {
			coursepasu.push_back(p->No);
			p = (PasDate*)p->ParentDate;
		}
		coursepasu.push_back(p->No);
		std::reverse(coursepasu.begin(), coursepasu.end());
		if (coursepasu.size() > 2)
		{
			Smoothing(&coursepasu);
		}
		pathdete->DebugVector(coursepasu);
	}
	for (auto ereas : open) {
		delete ereas;
	}
	for (auto ereas : cloas) {
		delete ereas;
	}
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
CVector3 Path::PathPos()
{
	if (coursepasu.size()-1 > m_nuwNo) {
		return pathdete->FindNo_Pos(coursepasu[m_nuwNo++]);
	}
	else
	{
		return pathdete->FindNo_Pos(coursepasu[m_nuwNo]);
	}
}