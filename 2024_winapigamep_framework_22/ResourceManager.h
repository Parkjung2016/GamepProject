#pragma once
#pragma comment(lib, "fmod_vc")
class Texture;
class ResourceManager
{
public:
	void Init();
	const wchar_t* GetResPath() const { return m_resourcePath; }
public:
	Texture* TextureLoad(const wstring& _key, const wstring& _path);
	Texture* CreateTexture(const wstring& _key, UINT _iWidth, UINT _iHeight);
	Texture* TextureFind(const wstring& _key);
	void Release();
private:
	wchar_t m_resourcePath[255] = {};
	map<wstring, Texture*> m_mapTextures;
	DECLARE_SINGLE(ResourceManager)
};

