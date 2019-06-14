#include "stdafx.h"
#include "color.h"


Color::Color()
{
}


Color::~Color()
{
}
CVector3 Color::HSVtoRGB(const CVector3& hsv)
{
	const float h = hsv.x - floor(hsv.x);
	const float s = hsv.y;
	const float v = hsv.z;
	const float hueF = h * 6.0f;
	const int hueI = static_cast<int>(hueF);
	const float fr = hueF - hueI;
	const float m = v * (1.0f - s);;
	const float n = v * (1.0f - s * fr);
	const float p = v * (1.0f - s * (1.0f - fr));

	CVector3 rgb;

	switch (hueI)
	{
	case 0: rgb.x = v; rgb.y = p; rgb.z = m; break;
	case 1: rgb.x = n; rgb.y = v; rgb.z = m; break;
	case 2: rgb.x = m; rgb.y = v; rgb.z = p; break;
	case 3: rgb.x = m; rgb.y = n; rgb.z = v; break;
	case 4: rgb.x = p; rgb.y = m; rgb.z = v; break;
	default: rgb.x = v; rgb.y = m; rgb.z = n; break;
	}

	return rgb;
}
CVector4 Color::HSVtoRGB()
{
	m_HSV.x += 10.0f / 360.0f;
	const float h = m_HSV.x-floor(m_HSV.x);
	const float s = m_HSV.y;
	const float v = m_HSV.z;
	const float hueF = h * 6.0f;
	const int hueI = static_cast<int>(hueF);
	const float fr = hueF - hueI;
	const float m = v * (1.0f - s);
	const float n = v * (1.0f - s * fr);
	const float p = v * (1.0f - s * (1.0f - fr));

	CVector3 rgb;

	switch (hueI)
	{
	case 0: rgb.x = v; rgb.y = p; rgb.z = m; break;
	case 1: rgb.x = n; rgb.y = v; rgb.z = m; break;
	case 2: rgb.x = m; rgb.y = v; rgb.z = p; break;
	case 3: rgb.x = m; rgb.y = n; rgb.z = v; break;
	case 4: rgb.x = p; rgb.y = m; rgb.z = v; break;
	default: rgb.x = v; rgb.y = m; rgb.z = n; break;
	}
	CVector4 Color = { rgb.x,rgb.y,rgb.z,1.0f };
	return Color;
}