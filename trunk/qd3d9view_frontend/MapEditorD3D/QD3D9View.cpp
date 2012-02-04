/*******************************************************************************
created:	2012/02/04
created:	2012:4:2   15:45
filename: 	QD3D9View.h		
author:		DRAGONKING(gmail.com)

purpose:	directx 9.0 control for QT
*******************************************************************************/
#include "QD3D9View.h"
#include <Windows.h>

QD3DWiew::QD3DWiew(QWidget *parent, Qt::WFlags flags)
:pD3D_(0), pDevice_(0)
,pVB_(0), pIB_(0), pVertexShader_(0), pConstantTable_(0), pVertexDeclaration_(0)
,pPixelShader_(0)
{	
	setAttribute(Qt::WA_PaintOnScreen);		//speed up! so... can make flicking....
	setAttribute(Qt::WA_NoSystemBackground);		
	setAttribute(Qt::WA_OpaquePaintEvent);	//don`t redraw by parent.


}

QD3DWiew::~QD3DWiew()
{

}

void QD3DWiew::PreRender()
{
	if(!pDevice_)
		return E_FAIL;

	return S_OK;
}

void QD3DWiew::Render()
{
	if(!pDevice_)
		return E_FAIL;

	return S_OK;
}

void QD3DWiew::PostRender()
{
	if(!pDevice_)
		return E_FAIL;

	return S_OK;
}

HRESULT	QD3DWiew::BeginScene()
{
	if(!pDevice_)
		return E_FAIL;
	
	return pDevice_->BeginScene();
}

HRESULT	QD3DWiew::EndScene()
{
	if(!pDevice_)
		return E_FAIL;

	return pDevice_->EndScene();
}

HRESULT	QD3DWiew::Present()
{
	if(!pDevice_)
		return E_FAIL;

	return pDevice_->Present();
}

HRESULT QD3DWiew::Initialize()
{
	HRESULT hr = S_OK;
	
	pD3D_ = Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D_)
		return S_FALSE;
	
	D3DCAPS9 Caps;
	pD3D_->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps );

	DWORD BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	// If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW 
	// then switch to SWVP.
	if( ( Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) == 0 ||
		Caps.VertexShaderVersion < D3DVS_VERSION( 2, 0 ) )
	{
		BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	ZeroMemory( &d3dParam_, sizeof(d3dParam_) );
	d3dParam_.Windowed = TRUE;
	d3dParam_.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParam_.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dParam_.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dParam_.MultiSampleQuality = 0;
	d3dParam_.EnableAutoDepthStencil = TRUE;
	d3dParam_.AutoDepthStencilFormat = D3DFMT_D24S8; 

	for( int m=0; m<=(int)D3DMULTISAMPLE_4_SAMPLES; m+=2 )
	{
		DWORD QualityBackBuffer = 0;

		hr = pD3D_->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			d3dParam_.BackBufferFormat,
			d3dParam_.Windowed,
			(D3DMULTISAMPLE_TYPE)m,
			&QualityBackBuffer );
		if( FAILED(hr) ) break;

		if( QualityBackBuffer>0 )
		{
			d3dParam_.MultiSampleType = (D3DMULTISAMPLE_TYPE)m;
			d3dParam_.MultiSampleQuality = QualityBackBuffer-1;
		}
	}

	//if can`t create h/w device, create software.
	hr = pD3D_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		winId(),//return windows handle
		BehaviorFlags,
		&d3dParam_,
		&pDevice_ );

	if( FAILED(hr) )
	{
		d3dParam_.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dParam_.MultiSampleQuality = 0;
		// Reference Rasterizer
		hr = pD3D_->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, winId(),	
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dParam_, &pDevice_);
		
		if( FAILED(hr) )
		{
			return S_FALSE;
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = RestoreDeviceObjects();
	}

	return S_OK;
}

void QD3DWiew::Uninitialize()
{

}

HRESULT	QD3DWiew::RestoreDeviceObjects()
{
	if(!pDevice_)
		return E_FAIL;

	return S_OK;
}

HRESULT QD3DWiew::InvalidateDeviceObjects()
{
	if(!pDevice_)
		return E_FAIL;

	return S_OK;
}

void QD3DWiew::ClearScene(D3DXCOLOR ClearColor, float Z, DWORD Stencil)
{
	pDevice_->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, (DWORD)ClearColor, Z, Stencil );
}

void QD3DWiew::ClearRenderTarget(D3DXCOLOR ClearColor)
{
	pDevice_->Clear( 0, 0, D3DCLEAR_TARGET,(DWORD)ClearColor, 1.0f, 0 );
}

void QD3DWiew::ClearDepthStencil(float Z, DWORD Stencil)
{

}