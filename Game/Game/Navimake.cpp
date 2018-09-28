#include "stdafx.h"
#include "Navimake.h"


Navimake::Navimake()
{
	m_model.Init(L"Assets/modelData/jimennabi.cmo");
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_model, nullptr);
	auto vertex= m_meshCollider.Getvertex(0);
	auto index = m_meshCollider.GetIndex(0);
	for (int i = 0; i <index.size();) {
		vertexpos[0] = vertex[index[i++]];
		vertexpos[1] = vertex[index[i++]];
		vertexpos[2] = vertex[index[i++]];
		seru.push_back({0.0f,0.0f,0.0f}, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		//seru.push_back(vertexpos);
	}

	int kalalakidjmocvnwsjijvdniosc = 0;
	kalalakidjmocvnwsjijvdniosc++;

}


Navimake::~Navimake()
{
}
