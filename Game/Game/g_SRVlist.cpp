#include "stdafx.h"
#include "g_SRVlist.h"

g_SRVlist g_srvlist;
g_SRVlist::g_SRVlist()
{
}


g_SRVlist::~g_SRVlist()
{
	for (const auto& list : m_list) {
		list.second->Release();
	}
	m_list.clear();
}
ID3D11ShaderResourceView* g_SRVlist::Create(const wchar_t* fileName)
{
	ID3D11ShaderResourceView* m_srv;
	auto it = m_list.find(fileName);
	if (it == m_list.end()) {
		HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
			g_graphicsEngine->GetD3DDevice(), fileName, 0,
			D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
			false, nullptr, &m_srv);
		if (FAILED(hr)) {
			//TK_WARNING_MESSAGE_BOX("Failed create texture");  //ƒGƒ‰[o—Í
			throw;
			return nullptr;
		}
		m_list.insert(std::make_pair(fileName,m_srv));
	}
	else
	{
		m_srv = it->second;
	}

	return m_srv;
}
