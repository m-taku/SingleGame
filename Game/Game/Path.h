#pragma once
class Navimake;
class Path:Noncopyable
{
public:
	Path();
	~Path();
	/*
	*@brief �p�X�f�[�^�̃C���X�^���X�Z�b�g
	*@param[in]�@Navimake*
	*/
	void Setpathdete(Navimake* navimake)
	{
		pathdete = navimake;
	}
	/*
	*@brief �o�H�T��+�X���[�W���O�����i��肷�����ӁI�I�j
	*@param[in]�@CVector3�@sturt  �i�����|�W�V�����j
	*@param[in]�@CVector3�@end�@�@�i�ڕW�|�W�V�����j
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
		~PasDate()
		{
			//delete ParentDate;
		}
		int No;						//���g�̔ԍ�
		int LincNo[3];				//���g����̃����N��ԍ�
		float MoveCost;				//���g�̏ꏊ�܂ōs���R�X�g
		float to_DrstinCost;		//���g�̏ꏊ����ړI�n�܂ł̃R�X�g
		PasDate* ParentDate;		//�e�̃p�X�e�[�^�̃|�C���^
	};
	/*
	*@brief �p�X�f�[�^�ɂ��X���[�W���O�����icoursepasu��ύX�j
	*@param[in]�@std::vector<int>* pasu�i�ړ��p�X�̏W���j
	*/
	void Smoothing(std::vector<int>* pasu);
private:
	std::vector<int> coursepasu;							//�o�H�T���̌��ʁi�X���[�W���O�����ς݁j
	Navimake* pathdete = nullptr;							//�Z���i�|���S���j�̃f�[�^
	int m_nuwNo = 0;										//�����Ԗڂ̃|�C���g�Ɍ������Ă��邩
};

