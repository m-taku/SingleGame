#pragma once
#include "HitReceive.h"
/// <summary>
/// ŠÈˆÕ‚È“–‚½‚è”»’è
/// </summary>
class HitObjict:public Noncopyable
{
public:
	HitObjict();
	~HitObjict();
	const HitReceive* Create(const CVector3* pos, float radius, std::function<void(float damage)> objict, HitReceive::objict_Name name);
	bool HitTest(CVector3 pos, float damage, HitReceive::objict_Name name);
	void Deleteobjict(const HitReceive* objict);
	void Release();
private:
	std::list<HitReceive*> m_objict;
};
extern HitObjict* g_HitObjict;

