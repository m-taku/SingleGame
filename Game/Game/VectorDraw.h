#pragma once
class VectorDraw
{
public:
	VectorDraw(CVector3 position,int counnt=1)
	{
		m_vector.Init(L"Assets/modelData/vectormodel.cmo", counnt);
		m_position = position;
		m_count = counnt;
	}
	~VectorDraw();
	void Update(CVector3 posotion, CVector3& Vector,float power);
	void Update();	
	void Update(std::vector<CVector3>::iterator posotion, std::vector<CVector3>::iterator& Vector, std::vector<float>::iterator power);
	void Update(std::vector<CVector3>& posotion);
	void Draw();
private:
	CVector3 vector = CVector3::Zero();			//表示したいベクトルの向き（ノーマライズ）
	CVector3 m_position;		                //表示したいベクトルの原点（ノーマライズ）
	SkinModel m_vector;
	int m_count = 1;
	float Power = 0.0f;							//表示したいベクトルの大きさ（float）

};

