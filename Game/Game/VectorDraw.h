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
	CVector3 vector = CVector3::Zero();			//表示したいベクトルの向き（ノーマライズ）
	CVector3 m_position;		//表示したいベクトルの原点（ノーマライズ）
	SkinModel m_vector;
	float Power = 0.0f;							//表示したいベクトルの大きさ（float）

};

