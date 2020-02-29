#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>

#include "CTexture.h"



map<wstring, LPDIRECT3DTEXTURE9> CTexture::s_TexturePool;

CTexture::CTexture()
{
}
CTexture::CTexture(LPDIRECT3DDEVICE9 pD3DDevice, const TCHAR* filename)
{
	Create(pD3DDevice, filename);
}

CTexture::~CTexture()
{
	Release();
}

bool CTexture::Create(LPDIRECT3DDEVICE9 pD3DDevice, const TCHAR* filename)
{
	bool bReturn = false;
	auto iter = s_TexturePool.find(wstring(filename));
	if (iter != s_TexturePool.end()) {
		m_Texture = iter->second;
		bReturn = true;
	}
	else {
		auto hr = D3DXCreateTextureFromFileEx(pD3DDevice, filename, 0, 0, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), NULL, NULL, &m_Texture);
		bReturn = FAILED(hr) ? false : true;

		if (bReturn == true) {
			s_TexturePool[wstring(filename)] = m_Texture;
		}
	}
	return bReturn;
}

void CTexture::Release() {

}
void CTexture::ReleaseAll() {
	for (auto iter = s_TexturePool.begin(); iter != s_TexturePool.end(); ++iter)
	{
		iter->second->Release();
		iter->second = NULL;
	}
	s_TexturePool.clear();
}
