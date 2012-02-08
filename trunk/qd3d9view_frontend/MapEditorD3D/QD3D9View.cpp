/*******************************************************************************
created:	2012/02/04
created:	2012:4:2   15:45
filename: 	QD3D9View.h		
author:		DRAGONKING(gmail.com)

purpose:	directx 9.0 control for QT
*******************************************************************************/
#include "QD3D9View.h"
#include <Windows.h>
#include <qstring.h>
#include "define.h"
#include "defineForTest.h"
#include "TextureManager.h"

#define DXUT_AUTOLIB
#include "DXUT.h"
#include "DXUTcamera.h"

#pragma comment(lib,"d3d9.lib")
#if (defined(_DEBUG) || defined(DEBUG))
	#pragma comment(lib,"d3dx9d.lib")
	#pragma comment(lib,"d3dx9d.lib")
	#pragma comment(lib,"lib/DXUT_d.lib")
	#pragma comment(lib,"lib/DXUTOpt_d.lib")
#else
	#pragma comment(lib,"d3dx9.lib")
	#pragma comment(lib,"lib/DXUT.lib")
	#pragma comment(lib,"lib/DXUTOpt.lib")
	#pragma comment(lib,"d3dx9.lib")
#endif


QD3DWiew::QD3DWiew(QWidget *parent, Qt::WFlags flags)
:QWidget( parent, flags )
,pD3D_(0), pDevice_(0)
,pVB_(0), pIB_(0), pVertexShader_(0), pConstantTable_(0), pVertexDeclaration_(0)
,pPixelShader_(0), isWireMode_(false), appTime_(0.f), pFont_(0), fps_(0.f)
,pModelviewCam_(0), pTextureManager(0)
{	
	//버퍼에서 버퍼로 복사후 프레임버퍼로 복사하게 되는데, 버퍼에서 바로 프레임버퍼로 복사하게 한다.
	//성능향상이 있지만 깜빡임이 나타날 수 있다.
	//알파블렌드에 영향을 줄 수 있으나, 다이렉트 엑스에게는 모르겠다.
	setAttribute(Qt::WA_PaintOnScreen);		
	setAttribute(Qt::WA_NoSystemBackground);		
	//부모에서 리드로우가 일어나면, 자식에게도 리드로우가 호출되는데, 그것을 막는다.
	setAttribute(Qt::WA_OpaquePaintEvent);

	timer_.setParent( parent );
	timer_.setInterval(1);	//최대 해상도로 1/1000
	timer_.setSingleShot( false ) ;		//정해진 시간후에 한번 호출하는 방식은 사용하지 않는다.
	QObject::connect( &timer_, SIGNAL( timeout() ), this, SLOT( Idle() ) ) ;

	InitializeValue();
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

	if( SUCCEEDED(hr = BeginScene()) )
	{
		if(isWireMode_)
			pDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			pDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				
		SetupCamera();

		RenderGeometryForTest();
		DrawFps();

		EndScene();						
	}
	else
	{
		qDebug("Failed BeginScene : %d", hr);		
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
	
	QSize wndSize = size();
	d3dParam_.BackBufferWidth =	wndSize.width();
	d3dParam_.BackBufferHeight = wndSize.height();


	for( int m=0; m<=(int)D3DMULTISAMPLE_4_SAMPLES; m+=2 )
	{
		DWORD QualityBackBuffer = 0;

		hr = pD3D_->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			d3dParam_.BackBufferFormat,
			d3dParam_.Windowed,
			(D3DMULTISAMPLE_TYPE)m,
			&QualityBackBuffer );

		if( FAILED(hr) ) 
			break;

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

	pTextureManager = new TextureManager(pDevice_);


	timer_.start();

	return S_OK;
}

void QD3DWiew::Finalize()
{	
	InvalidateDeviceObjects();		

	SAFE_DELETE(pTextureManager);
	SAFE_DELETE(pModelviewCam_);
	SAFE_RELEASE(pDevice_);
	SAFE_RELEASE(pD3D_);	
}

//복구 처리
HRESULT	QD3DWiew::RestoreDeviceObjects()
{
	if(!pDevice_)
		return E_FAIL;		

	InitializeValue();
	InitializeFont();
	InitializeCamera();
	InitGeometryForTest();	

	pDevice_->SetRenderState( D3DRS_LIGHTING, FALSE );
	pDevice_->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	//pDevice_->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );

	timer_.start();

	return S_OK;
}

//무효화 처리
HRESULT QD3DWiew::InvalidateDeviceObjects()
{
	if(!pDevice_)
		return E_FAIL;

	timer_.stop();

	SAFE_RELEASE(pFont_);

	SAFE_RELEASE(pVB_);
	SAFE_RELEASE(pIB_);	

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

void QD3DWiew::Update(float timeMS)
{
	pModelviewCam_->FrameMove(timeMS);
}

void QD3DWiew::Idle()
{
	appTime_ += timer_.interval() * 0.01;

	Update(appTime_); 
	PreRender();
	Render();
	PostRender();


	if(addTime_ >= 1.0f)
	{
		++callCnt;
		fps_ = callCnt/addTime_;
		callCnt = 0;	
		addTime_ = 0;

	}
	else
	{
		addTime_ += timer_.interval() * 0.01;
		++callCnt;
	}
}

void QD3DWiew::InitializeFont()
{
	hFont_ = (HFONT)GetStockObject(SYSTEM_FONT);
	D3DXCreateFont(pDevice_, 20, 10, 1, TRUE, 1, 1, 5, 1,  NULL,L"Courier", &pFont_);	
}

void QD3DWiew::DrawFps()
{
	RECT TextRect = {0.f, 0.f, 200.f, 100.f};
	char buff[16];
	sprintf(buff, "FPS : %5.2f", fps_);
	
	if(pFont_)
		pFont_->DrawTextA(NULL, buff, -1, &TextRect, DT_WORDBREAK |DT_VCENTER | DT_CENTER, D3DCOLOR_XRGB(255,0,255));
}

void QD3DWiew::InitializeValue()
{
	addTime_ = 0;
	callCnt = 0;

	eyePos_ = D3DXVECTOR3(0, 0.f, -80.f);
	D3DXMatrixIdentity(&matWorld);	 
	
	startMousePos_ = QPoint(0,0);

	windowSize_ = size();
}

void QD3DWiew::InitializeCamera()
{
	if(!pModelviewCam_)
		pModelviewCam_ = new CModelViewerCamera();

	if(!pModelviewCam_)
		return;	

	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 80.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	//DX 카메라
	pModelviewCam_->SetViewParams(&eyePos_, &vLookatPt);
	pModelviewCam_->SetProjParams(D3DX_PI / 4, 1.0f, 1.0f, 1000.f);	
	GetModelViewCamera()->SetWindow(windowSize_.width(), windowSize_.height());

	//스크린 공간으로 투영(글짜 출력용)
	D3DXVec3Project(&screenFontPos_,&objectFontPos_,&viewPort_,
		GetModelViewCamera()->GetProjMatrix(),
		GetModelViewCamera()->GetViewMatrix(),
		GetModelViewCamera()->GetWorldMatrix());
}

CModelViewerCamera* QD3DWiew::GetModelViewCamera()
{
	return (CModelViewerCamera*)pModelviewCam_;
}

void QD3DWiew::SetupCamera()
{
	if(pModelviewCam_)
	{
		pDevice_->SetTransform( D3DTS_WORLD, GetModelViewCamera()->GetWorldMatrix());	
		pDevice_->SetTransform( D3DTS_VIEW, GetModelViewCamera()->GetViewMatrix() );	
		pDevice_->SetTransform( D3DTS_PROJECTION, GetModelViewCamera()->GetProjMatrix());
	}
}

void QD3DWiew::SetRenderMode(renderMode mode)
{
	if(mode == rdSolid)
		isWireMode_ = false;
	else
		isWireMode_ = true;
}

bool QD3DWiew::ImportHeightmap(QString filename)
{	
	if(!pTextureManager)
		return false;

	LPDIRECT3DTEXTURE9 pTexture = pTextureManager->LoadTextureFromFile(filename.toStdString());
	if(!pTexture)
		return false;


	return true;
}

bool QD3DWiew::InitVBforHeightmap()
{
	return true;
}

bool QD3DWiew::InitIBforHeightmap()
{
	return true;
}