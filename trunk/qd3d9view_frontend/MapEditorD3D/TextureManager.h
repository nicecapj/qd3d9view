/********************************************************************
	created:	2012/02/09
	created:	2012:9:2   4:34
	filename: 	TextureManager.h		
	author:		DRAGONKING(gmail.com)
	
purpose:	symple texture manager
*********************************************************************/

#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"

class TextureManager
{
public:
	TextureManager(IDirect3DDevice9* device);
	~TextureManager();
	
	typedef std::map<std::string, LPDIRECT3DTEXTURE9>textures;	
	LPDIRECT3DTEXTURE9 LoadTextureFromFile(const std::string& filename);

protected:

private:
	IDirect3DDevice9* pDevice_;
	textures textures_;
};

#endif __TEXTURE_MANAGER_H__