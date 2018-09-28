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
	CVector3 HP_waku_position = {-640.0f,-240.0f,0.0f};
	CVector3 HP_position = { -637.0f,-242.0f,0.0f };
	float HP=1.0f;

};

