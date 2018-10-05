#include "stdafx.h"
#include "Path.h"
#include"Navimake.h"


Path::Path()
{
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
	ka.Estimatecost = 0.0f;
	ka.parentNo = 0;
	std::vector<PasDate> open;
	std::vector<PasDate> cloas;
	open.push_back(ka);
	while (true)
	{
		pathdete->FindnearestNo_No(open[0], endNo, cost);
	}
}
