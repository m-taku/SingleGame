#include "stdafx.h"
#include "HitObjict.h"


HitObjict::HitObjict()
{
}


HitObjict::~HitObjict()
{
	for (auto k : m_objict)
	{
		delete k;
	}
}
const HitReceive* HitObjict::Create(const CVector3* pos, float radius, std::function<void()>  objict, HitReceive::objict_Name name)
{
	auto ka = new HitReceive;
	ka->Create(pos,radius,objict,name);
	m_objict.push_back(ka);
	return ka;
}
bool HitObjict::HitTest(CVector3 pos, HitReceive::objict_Name name)
{
	for (auto k : m_objict)
	{
		if (k->Getobjict_Name() != name) {
			if (k->HitTest(pos))
				return true;
		}
	}
	return false;
}
void HitObjict::Deleteobjict(const HitReceive* objict)
{
	m_objict.erase(std::find(m_objict.begin(), m_objict.end(),objict));
	delete objict;
}