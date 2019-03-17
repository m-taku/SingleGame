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
	auto NextPas = open[0];
	//m_coursepasu.push_back(startNo);
	//m_coursepasu.push_back(endNo);
	//std::reverse(m_coursepasu.begin(), m_coursepasu.end());
	//if (m_coursepasu.size() > 2)
	//{
	//	Smoothing(&m_coursepasu);
	//}
	//if (startNo == endNo) {
	//	m_coursepasu.push_back(p->No);
	//	delete Date;
	//	return;
	//}

	float CurrentCost = 0.0f;

	while (NextPas->No != endNo)
	{
		 auto LincPas = m_pathdata->FindLinc(*NextPas, endNo, CurrentCost);
		//auto ka1= ka5.begin();
		//float costng = FLT_MAX;
		//int MinNo = 0;
		open.erase(
			std::remove(open.begin(), open.end(), NextPas),
			open.end());
		close.push_back(NextPas);
		for (int j = 0; j < 3; j++)
		{

			if (-1 != LincPas[j]->No)
			{
				open.push_back(LincPas[j]);
				for (int k = 0; k < open.size(); k++) {
					if (open[k] == LincPas[j])
					{
						break;
					}
					if (open[k]->No == LincPas[j]->No) {
						if (open[k]->to_DrstinCost <= LincPas[j]->to_DrstinCost)
						{
							delete LincPas[j];
							open.erase(
								std::remove(open.begin(), open.end(), LincPas[j]),
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
					if (close[k]->No == LincPas[j]->No) {
						if (close[k]->to_DrstinCost <= LincPas[j]->to_DrstinCost) {
							delete  LincPas[j];
							open.erase(
								std::remove(open.begin(), open.end(), LincPas[j]),
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
				delete LincPas[j];
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
				NextPas = i;
			}
		}
		CurrentCost = NextPas->MoveCost;
	}

	if (open.size() <= 0)
	{
		m_coursepasu.push_back(startNo);
	}
	else
	{
		while (NextPas->No != startNo) {
			m_coursepasu.push_back(NextPas->No);
			NextPas = (PasDate*)NextPas->ParentDate;
		}
		m_coursepasu.push_back(NextPas->No);
		std::reverse(m_coursepasu.begin(), m_coursepasu.end());
		if (m_coursepasu.size() > 2)
		{
			Smoothing(&m_coursepasu);
		}
		m_pathdata->DebugVector(m_coursepasu);
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