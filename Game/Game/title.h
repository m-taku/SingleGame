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
	ShaderResourceView texturea;
	sprite title_haikei;
	sprite title_moji;
	sprite feid;
	float toumei = 0.0f;
};

