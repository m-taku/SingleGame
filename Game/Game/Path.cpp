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
	if (sturtNo == endNo) {
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
			if (((*i)->MoveCost+(*i)->to_DrstinCost) <= costnV2)
			{
				costnV2 = (*i)->MoveCost + (*i)->to_DrstinCost;
				p = *i;
			}
		}
		CurrentCost = p->MoveCost;
		auto ka5 = pathdete->FindLinc(p->No,endNo,CurrentCost);
		auto ka1= ka5.begin();
		//float costng = FLT_MAX;
		//int MinNo = 0;
		cloas.push_back(p);
		for (int j=0;j<3;j++)
		{
			
			if (-1 != (*ka1)->No)
			{
				//if (costng >= p->Estimatecost + ka1[j].Estimatecost)
				//{
				//	costng = p->Estimatecost + ka1[j].Estimatecost;
				//	MinNo = ka1[j].No;
				//}
				open.push_back(*ka1);
				for (int k = 0; k < cloas.size(); k++) {
					for (int j = 0; j < 3; j++) {
						if (cloas[k]->No == (*ka1)->No) {
							open.erase(
								std::remove(open.begin(), open.end(), *ka1),
								open.end());
							break;
						}
					}
				}
			}
			ka1++;
		}
		open.erase(
			std::remove(open.begin(), open.end(), p),
			open.end());

		////ƒNƒ[ƒY‚·‚é‚Æ‚«

		//pathdete->FindnearestNo_No(*p, endNo, cost);
	
	}
	//cloas.push_back(p);
	//while (cloas) {
	//	coursepasu;
	//}
}
