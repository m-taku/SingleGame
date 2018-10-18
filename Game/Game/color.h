#pragma once
class color
{
public:
	color();
	~color();
	CVector3 HSVtoRGB(const CVector3& hsv);
	CVector4 HSVtoRGB();
private:
	CVector3  HSV = { 0.0f,1.0f,0.3f};
};

