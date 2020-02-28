#pragma once

#include <map>
#include <string>

using namespace std;
class CTexture
{
protected:
	LPDIRECT3DTEXTURE9 m_Texture;
	static map<wstring, LPDIRECT3DTEXTURE9> s_TexturePool;
public:
	CTexture();
	CTexture(LPDIRECT3DDEVICE9 pD3DDevice, const TCHAR* filename);
	virtual ~CTexture();

	bool Create(LPDIRECT3DDEVICE9 pD3DDevice, const TCHAR* filename);
	void Release();

	LPDIRECT3DTEXTURE9 GetTexture() const {
		return m_Texture;
	}
	static void ReleaseAll();
};

