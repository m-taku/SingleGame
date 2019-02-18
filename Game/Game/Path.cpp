#include "stdafx.h"
#include "Path.h"
#include"Navimake.h"

Path::Path()
{
	m_pathdata = g_objectManager->FindGO<Navimake>("Navimake");
}


Path::~Path()
{

}
void Path::Course(CVector3 sturt, CVector3 end)
{
	m_nowNo = 0;
	m_coursepasu.clear();

	int startNo = m_pathdata->FindPos_No(sturt);
	int endNo = m_pathdata->FindPos_No(end);

	PasDate* Date = new PasDate;
	Date->No = startNo;
	std::vector<PasDate*> open;
	std::vector<PasDate*> close;
	open.push_back(Date);
	auto p = open[0];
	if (startNo == endNo) {
		m_coursepasu.push_back(p->No);
		delete Date;
		return;
	}
	float CurrentCost = 0.0f;

	while (p->No != endNo)
	{
		 auto ka5 = m_pathdata->FindLinc(*p, endNo, CurrentCost);
		//auto ka1= ka5.begin();
		//float costng = FLT_MAX;
		//int MinNo = 0;
		open.erase(
			std::remove(open.begin(), open.end(), p),
			open.end());
		close.push_back(p);
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
				for (int k = 0; k < close.size(); k++) {
					if (close[k]->No == ka5[j]->No) {
						if (close[k]->to_DrstinCost <= ka5[j]->to_DrstinCost) {
							delete  ka5[j];
							open.erase(
								std::remove(open.begin(), open.end(), ka5[j]),
								open.end());
							break;
						}
						else {
							delete close[k];
							close.erase(
								std::remove(close.begin(), close.end(), close[k]),
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
		for (auto i : open)
		{
			if ((i->MoveCost + i->to_DrstinCost) <= costnV2) {
				costnV2 = i->MoveCost + i->to_DrstinCost;
				p = i;
			}
		}
		CurrentCost = p->MoveCost;
	}

	if (open.size() <= 0)
	{
		m_coursepasu.push_back(startNo);
	}
	else
	{
		while (p->No != startNo) {
			m_coursepasu.push_back(p->No);
			p = (PasDate*)p->ParentDate;
		}
		m_coursepasu.push_back(p->No);
		std::reverse(m_coursepasu.begin(), m_coursepasu.end());
		if (m_coursepasu.size() > 2)
		{
			Smoothing(&m_coursepasu);
		}
		//m_pathdata->DebugVector(m_coursepasu);
	}
	for (auto ereas : open) {
		delete ereas;
	}
	for (auto ereas : close) {
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
		if (m_pathdata->CollisionTest(start, Next))
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
	if (m_coursepasu.size()-1 > m_nowNo) {
		return m_pathdata->FindNo_Pos(m_coursepasu[m_nowNo++]);
	}
	else
	{
		return m_pathdata->FindNo_Pos(m_coursepasu[m_nowNo]);
	}
}