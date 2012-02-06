/********************************************************************
	created:	2012/02/07
	created:	2012:7:2   8:14
	filename: 	QD3D9View_Test.cpp		
	author:		DRAGONKING(gmail.com)
	
	purpose:	test routine
*********************************************************************/
#include "QD3D9View.h"
#include "defineForTest.h"

HRESULT QD3DWiew::InitGeometryForTest()
{		
	CUSTOMVERTEX vertices[] = 
	{
		CUSTOMVERTEX(-1.f , 0.f , 0.f , 0xffff0000),
		CUSTOMVERTEX(0.f , 1.f , 0.f , 0xff00ff00),
		CUSTOMVERTEX(1.f , 0.f , 0.f , 0xff0000ff),
	};

	if(FAILED(pDevice_->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX), 0, D3DFVF_P3F_D, D3DPOOL_DEFAULT, &pVB_, NULL)))
	{
		return E_FAIL;
	}

	void* pVertices;
	if(FAILED(pVB_->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	pVB_->Unlock();

	objectFontPos_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	SetupGeometryForTest();

	return S_OK;
}


void QD3DWiew::SetupGeometryForTest()
{
	//D3DXMATRIXA16 matWorld;	
	pDevice_->SetTransform(D3DTS_WORLD, &matWorld);

	//D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-80.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 80.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &eyePos_, &vLookatPt, &vUpVec );
	pDevice_->SetTransform( D3DTS_VIEW, &matView );	
	
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	pDevice_->SetTransform( D3DTS_PROJECTION, &matProj );

	//스크린 공간으로 투영(글짜 출력용)
	D3DXVec3Project(&screenFontPos_,&objectFontPos_,&viewPort_,&matProj,&matView,&matWorld);	
}


void QD3DWiew::RenderGeometryForTest()
{
	pDevice_->SetStreamSource(0, pVB_, 0, sizeof(CUSTOMVERTEX));
	pDevice_->SetFVF(D3DFVF_P3F_D);
	pDevice_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 1);
}