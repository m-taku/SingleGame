#pragma once
class UI :public Gameobject
{
public:
	UI();
	~UI();
	bool Load();
	void Update();
	void postDraw();
	void Draw();
private:
	ShaderResourceView texture;
	ShaderResourceView Texture;
	sprite HP_bar_waku;
	sprite HP_bar;
	float m_Damage = 0.0f;											//É_ÉÅÅ[ÉWó 
	CVector3 m_HP_waku_position = {-640.0f,-240.0f,0.0f};
	CVector3 m_HP_position = { -637.0f,-242.0f,0.0f };
	float m_HP=1.0f;

};

