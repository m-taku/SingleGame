#pragma once
class Navimake;
class Path:Noncopyable
{
public:
	Path();
	~Path();
	/*
	*@brief �p�X�f�[�^�̃C���X�^���X�Z�b�g
	*@�@Navimake*
	*/
	void Setpathdete(Navimake* navimake)
	{
		pathdete = navimake;
	}
	/*
	*@brief �o�H�T��+�X���[�W���O�����i��肷�����ӁI�I�j
	*@�@CVctor3�@sturt,end
	*/
	void course(CVector3 sturt, CVector3 end);
	/*
	*@brief ���ɓ����ڕW�ʒu(�����Ȃ�)
	*@return CVctor3
	*/
	CVector3 Pathpos();
	//�p�X�̃f�[�^�`��
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
		PasDate* ParentDate;		//�e�̃p�X�e�[�^�̃|�C���^
	};
	/*
	*@brief �p�X�f�[�^�ɂ��X���[�W���O�����icoursepasu��ύX�j
	*@�@std::vector<int>* pasu�i���ǂ��ς��̏W���j
	*/
	void Smoothing(std::vector<int>* pasu);
private:
	std::vector<int> coursepasu;
	Navimake* pathdete = nullptr;
	int m_nuwNo = 0;
};

