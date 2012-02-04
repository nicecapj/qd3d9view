/*******************************************************************************
created:	2012/02/04
created:	2012:4:2   15:45
filename: 	QD3D9View.h		
author:		DRAGONKING(nicecapj@naver.com)

purpose:	directx 9.0 control for QT
*******************************************************************************/
#include "QD3D9View.h"
#include <Windows.h>

QD3DWiew::QD3DWiew(QWidget *parent, Qt::WFlags flags)
:pD3D_(0), pDevice_(0)
,pVB_(0), pIB_(0), pVertexShader_(0), pConstantTable_(0), pVertexDeclaration_(0)
,pPixelShader_(0)
{
	//서피스나 버퍼를 프레임버퍼에 바로 쓰게된다. 속도 향상은 있으나, 깜빡임이 있을수 있다.
	//알파블렌딩에 문제가 있을수 있다고 하는데 일단 써보자.
	setAttribute(Qt::WA_PaintOnScreen);	
	setAttribute(Qt::WA_NoSystemBackground);
	//부모 위젯이 다시 그려질때 자식도 그려지는데, 이것을 안하도록 하는 플래그
	setAttribute(Qt::WA_OpaquePaintEvent); 


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

	//하드웨어로 우선 생성해본후, 실패시 소프트웨어로 생성한다.
	hr = pD3D_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		winId(),//qt의 winId()함수가 윈도우핸들 리턴
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

//디바이스 소실시 처리한다.
HRESULT	QD3DWiew::RestoreDeviceObjects()
{
	if(!pDevice_)
		return E_FAIL;

	return S_OK;
}

//소실된 장치가 복구될 수 있다면, 모든 비디오메모리 자원/스왑체인을 파괴한다.
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