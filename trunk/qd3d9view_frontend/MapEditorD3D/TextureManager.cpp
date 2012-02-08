/********************************************************************
created:	2012/02/09
created:	2012:9:2   4:34
filename: 	TextureManager.h		
author:		DRAGONKING(gmail.com)

purpose:	symple texture manager
*********************************************************************/
#include "TextureManager.h"

#define DXUT_AUTOLIB
#include "DXUT.h"
#include "DXUTcamera.h"

TextureManager::TextureManager(IDirect3DDevice9* device):pDevice_(device)
{

}


TextureManager::~TextureManager()
{
	SafeReleaseMap(textures_);
}


LPDIRECT3DTEXTURE9 TextureManager::LoadTextureFromFile(const std::string& filename)
{
	if(!pDevice_)
		return 0;

	textures::iterator it = textures_.find(filename);
	if(it != textures_.end())
		return it->second;

	LPDIRECT3DTEXTURE9 pTexture = 0;
	D3DXCreateTextureFromFileExA(pDevice_, filename.c_str(),
		D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0,
		D3DFMT_X8B8G8R8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &pTexture);
	if(!pTexture)
		return 0;

	textures_.insert(textures::value_type(filename, pTexture));

	return pTexture;
}