#ifndef __DEFINE_FOR_TEST_H__
#define __DEFINE_FOR_TEST_H__

struct CUSTOMVERTEX
{
	FLOAT x, y, z;      // The untransformed, 3D position for the vertex
	DWORD color;        // The vertex color
	CUSTOMVERTEX()
	{
		x = 0;
		y = 0;
		z = 0;
		color = 0xffff00;
	}

	CUSTOMVERTEX(float fx, float fy, float fz, DWORD c)
	{
		x = fx;
		y = fy;
		z = fz;
		color = c;
	}
};

#define  D3DFVF_P3F_D (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#endif /*__DEFINE_FOR_TEST_H__*/