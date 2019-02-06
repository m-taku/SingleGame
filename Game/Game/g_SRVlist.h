#pragma once
class g_SRVlist:public Noncopyable
{
public:
	g_SRVlist();
	~g_SRVlist();
	ID3D11ShaderResourceView* Create(const wchar_t* fileName);
private:
	std::map<std::wstring,ID3D11ShaderResourceView*> m_list;
};
extern g_SRVlist g_srvlist;
