#pragma once
class title : public Gameobject
{
public:
	title();
	~title();
	bool Load();
	void Update();
	void postDraw();
private:
	ShaderResourceView texture;
	ShaderResourceView Texture;
	sprite HP_bar_waku;
	sprite HP_bar;
};

