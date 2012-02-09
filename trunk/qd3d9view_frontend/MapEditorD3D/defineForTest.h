/********************************************************************
created:	2012/02/05
created:	2012:5:2   2:38
filename: 	define.h		
author:		DRAGONKING(gmail.com)

purpose:	define for test
*********************************************************************/
#ifndef __DEFINE_FOR_TEST_H__
#define __DEFINE_FOR_TEST_H__

struct CUSTOMVERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;			  // The vertex color	

	CUSTOMVERTEX(float fx, float fy, float fz, DWORD c)
	{
		x = fx;
		y = fy;
		z = fz;	
		color = c;
	}
};

struct TerrainVertex
{	
	D3DXVECTOR3 pos;
	D3DXVECTOR3 n;
	DWORD color;
//	D3DXVECTOR2 tex;

	TerrainVertex()
	{
		pos = D3DXVECTOR3(0.f, 0.f, 0.f);
		n = D3DXVECTOR3(0.f, 0.f, 0.f);
		color = 0;
		//tex = D3DXVECTOR2(0.f, 0.f);
	}
};

#define  D3DFVF_P3F_D (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define  D3DFVF_P3RHWF_D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#define  D3DFVF_TERRAIN (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)
#define  D3DFVF_TERRAIN_Tex (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX0)


//map
const float CELL_SIZE = 10.f;
const float CELL_HEIGHT = 2.f;

const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );

#endif /*__DEFINE_FOR_TEST_H__*/