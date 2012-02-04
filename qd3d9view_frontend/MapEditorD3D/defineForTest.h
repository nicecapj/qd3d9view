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
	FLOAT rhw;
	DWORD color;        // The vertex color
	CUSTOMVERTEX()
	{
		x = 0;
		y = 0;
		z = 0;
		color = 0xffff00;
	}

	CUSTOMVERTEX(float fx, float fy, float fz, float frhw, DWORD c)
	{
		x = fx;
		y = fy;
		z = fz;
		rhw =  frhw;
		color = c;
	}
};

#define  D3DFVF_P3RHWF_D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

#endif /*__DEFINE_FOR_TEST_H__*/