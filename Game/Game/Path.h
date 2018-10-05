#pragma once
class Navimake;
class Path
{
public:
	Path();
	~Path();
	void Setpathdete(Navimake* navimake)
	{
		pathdete = navimake;
	}
	void course(CVector3 sturt, CVector3 end);	
	struct PasDate
	{
		int No;
		int Estimatecost;
		int parentNo;
	};
private:

	Navimake* pathdete = nullptr;
	float cost = 0.0f;
	CVector3 jki;
};

