#pragma once
class Navimake;
class Path:Noncopyable
{
public:
	Path();
	~Path();
	void Setpathdete(Navimake* navimake)
	{
		pathdete = navimake;
	}
	void course(CVector3 sturt, CVector3 end);
	/*
	*@brief ���ɓ����ڕW�ʒu(�����Ȃ�)
	*@return CVctor3
	*/
	CVector3 Pathpos();
	struct PasDate
	{
		PasDate() {
			LincNo[0] = -1;
			LincNo[1] = -1;
			LincNo[2] = -1;
			MoveCost = 0.0f;
			ParentDate = nullptr;
			to_DrstinCost=0.0f;
			No = -1;
		}
		int No;						//���g�̔ԍ�
		int LincNo[3];				//���g����̃����N��ԍ�
		float MoveCost;				//���g�̏ꏊ�܂ōs���R�X�g
		float to_DrstinCost;		//���g�̏ꏊ����ړI�n�܂ł̃R�X�g
		PasDate* ParentDate;
	};
	void Smoothing(std::vector<int>* pasu);
private:
	std::vector<int> coursepasu;
	Navimake* pathdete = nullptr;
	int m_nuwNo = 0;
};

