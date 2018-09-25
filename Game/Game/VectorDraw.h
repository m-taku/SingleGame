#pragma once
class VectorDraw
{
public:
	VectorDraw(CVector3 position)
	{
		m_vector.Init(L"Assets/modelData/vectormodel.cmo");
		m_position = position;
	}
	~VectorDraw();
	void Update(CVector3 posotion, CVector3 Vector,float power);
	void Draw();
private:
	CVector3 vector = CVector3::Zero();			//�\���������x�N�g���̌����i�m�[�}���C�Y�j
	CVector3 m_position;		//�\���������x�N�g���̌��_�i�m�[�}���C�Y�j
	SkinModel m_vector;
	float Power = 0.0f;							//�\���������x�N�g���̑傫���ifloat�j

};

