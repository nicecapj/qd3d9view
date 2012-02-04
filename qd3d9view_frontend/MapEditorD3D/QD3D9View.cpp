/*******************************************************************************
created:	2012/02/04
created:	2012:4:2   15:45
filename: 	QD3D9View.h		
author:		DRAGONKING(gmail.com)

purpose:	directx 9.0 control for QT
*******************************************************************************/
#include "QD3D9View.h"
#include <Windows.h>
#include "define.h"
#include "defineForTest.h"

QD3DWiew::QD3DWiew(QWidget *parent, Qt::WFlags flags)
:pD3D_(0), pDevice_(0)
,pVB_(0), pIB_(0), pVertexShader_(0), pConstantTable_(0), pVertexDeclaration_(0)
,pPixelShader_(0), isWireMode_(false)
{	
	setAttribute(Qt::WA_PaintOnScreen);		//speed up! so... can make flicking....
	setAttribute(Qt::WA_NoSystemBackground);		
	setAttribute(Qt::WA_OpaquePaintEvent);	//don`t redraw by parent.
}

QD3DWiew::~QD3DWiew()
{
	Finalize();
}

void QD3DWiew::PreRender()
{
}

void QD3DWiew::Render()
{	
	HRESULT hr = S_OK;

	ClearScene( D3DXCOLOR( 0.0f, 0.f, 0.f, 0.f ), 1.0f, 0 );

	if( SUCCEEDED(BeginScene()) )
	{
		if(isWireMode_)
			pDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			pDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				
		SetupGeometryForTest();
		RenderGeometryForTest();

		EndScene();
	}

	hr = Present();
}

void QD3DWiew::PostRender()
{
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

	HRESULT hr =  pDevice_->Present(0,0,0,0);
	if(hr == D3DERR_DEVICELOST)
	{
		Sleep(100);

		if( FAILED( hr = pDevice_->TestCooperativeLevel() ) )
		{
			// The device has been lost but cannot be reset at this time. 
			// Therefore, rendering is not possible and we'll have to return 
			// and try again at a later time.
			if( hr == D3DERR_DEVICELOST )
				return hr;

			// The device has been lost but it can be reset at this time. 
			if( hr == D3DERR_DEVICENOTRESET )
			{
				//
				// If the device can be restored, the application prepares the 
				// device by destroying all video-memory resources and any 
				// swap chains. 
				//

				InvalidateDeviceObjects();

				//
				// Then, the application calls the Reset method.
				//
				// Reset is the only method that has an effect when a device 
				// is lost, and is the only method by which an application can 
				// change the device from a lost to an operational state. 
				// Reset will fail unless the application releases all 
				// resources that are allocated in D3DPOOL_DEFAULT, including 
				// those created by the IDirect3DDevice9::CreateRenderTarget 
				// and IDirect3DDevice9::CreateDepthStencilSurface methods.
				//

				hr = pDevice_->Reset( &d3dParam_ );

				if( FAILED( hr ) )
					return hr;

				//
				// Finally, a lost device must re-create resources (including  
				// video memory resources) after it has been reset.
				//

				RestoreDeviceObjects();
			}
		}
	}
	
	return hr;
}

HRESULT QD3DWiew::Initialize()
{
	HRESULT hr = S_OK;
	
	pD3D_ = Direct3DCreate9(D3D_SDK_VERSION);
	if(!pD3D_)
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

	
	InitGeometryForTest();

	return S_OK;
}

void QD3DWiew::Finalize()
{
	InvalidateDeviceObjects();

	SAFE_RELEASE(pVB_);
	SAFE_RELEASE(pIB_);
	SAFE_RELEASE(pDevice_);
	SAFE_RELEASE(pD3D_);	
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
	if(!pDevice_)
		return;

	pDevice_->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, (DWORD)ClearColor, Z, Stencil );
}

void QD3DWiew::ClearRenderTarget(D3DXCOLOR ClearColor)
{
	pDevice_->Clear( 0, 0, D3DCLEAR_TARGET,(DWORD)ClearColor, 1.0f, 0 );
}

void QD3DWiew::ClearDepthStencil(float Z, DWORD Stencil)
{

}

void QD3DWiew::Update(float time)
{

}

void QD3DWiew::SetupGeometryForTest()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationX( &matWorld, 1 );

	D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-80.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 80.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	pDevice_->SetTransform( D3DTS_VIEW, &matView );
	
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	pDevice_->SetTransform( D3DTS_PROJECTION, &matProj );
}

HRESULT QD3DWiew::InitGeometryForTest()
{
	CUSTOMVERTEX vertices[] = 
	{
		CUSTOMVERTEX(150.f,50.f,0.5f,0xffff0000),
		CUSTOMVERTEX(250.f,250.f,0.5f,0xffff0000),
		CUSTOMVERTEX(50.f,250.f,0.5f,0xffff0000),
	};
		    
	if(FAILED(pDevice_->CreateVertexBuffer(3 * sizeof(vertices), 0, D3DFVF_P3F_D, D3DPOOL_DEFAULT, &pVB_, NULL)))
	{
		return E_FAIL;
	}

	void* pVertices;
	if(FAILED(pVB_->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	pVB_->Unlock();


	return S_OK;
}

void QD3DWiew::RenderGeometryForTest()
{
	pDevice_->SetStreamSource(0, pVB_, 0, sizeof(CUSTOMVERTEX));
	pDevice_->SetFVF(D3DFVF_P3F_D);
	pDevice_->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}