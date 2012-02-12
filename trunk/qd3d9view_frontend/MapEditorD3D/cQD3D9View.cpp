/*******************************************************************************
created:	2012/02/04
created:	2012:4:2   15:45
filename: 	QD3D9View.h		
author:		DRAGONKING(gmail.com)

purpose:	directx 9.0 control for QT
*******************************************************************************/
#include "cQD3D9View.h"
#include <Windows.h>
#include <qstring.h>
#include "define.h"
#include "defineForTest.h"
#include "cTextureManager.h"
#include "cTestRoutine.h"

#define DXUT_AUTOLIB
#include "../DXUtil/DXUT.h"
#include "../DXUtil/DXUTcamera.h"

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


cQD3DView::cQD3DView(QWidget *parent, Qt::WFlags flags)
:QWidget( parent, flags )
,pD3D_(0), pDevice_(0)
,pVB_(0), pIB_(0), pVertexShader_(0), pConstantTable_(0), pVertexDeclaration_(0)
,pPixelShader_(0), isWireMode_(false), appTime_(0.f), pFont_(0), fps_(0.f)
,pModelviewCam_(0), pcTextureManager(0), pTestRoutine_(0)
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

cQD3DView::~cQD3DView()
{
	Finalize();
}

void cQD3DView::PreRender()
{
}

void cQD3DView::Render()
{		
	HRESULT hr = S_OK;

	ClearScene( D3DXCOLOR( 0.0f, 0.f, 0.f, 0.f ), 1.0f, 0 );

	if( SUCCEEDED(hr = BeginScene()) )
	{
		if(isWireMode_)
			pDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			pDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				
		//SetupGeometryForTest();
		SetupCamera();

		//SetupLight();

		if(mapCellNum_ == 0)
		{
			//RenderGeometryForTest();
			RenderSLODTileForTest();
		}
		else
		{
			RenderHeightMap();
		}
		DrawFps();

		EndScene();						
	}
	else
	{
		qDebug("Failed BeginScene : %d", hr);		
	}		

	hr = Present();
}

void cQD3DView::PostRender()
{
}

HRESULT	cQD3DView::BeginScene()
{
	if(!pDevice_)
		return E_FAIL;	

	return pDevice_->BeginScene();
}

HRESULT	cQD3DView::EndScene()
{
	if(!pDevice_)
		return E_FAIL;
	
	return pDevice_->EndScene();
}

HRESULT	cQD3DView::Present()
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

HRESULT cQD3DView::Initialize()
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

	pTestRoutine_ = new cTestRoutine(this);
	pcTextureManager = new cTextureManager(pDevice_);

	//★ abnormal using, pre alloc for test routine;
	pDevice_->CreateVertexBuffer(128 * 128 * 28, 0, D3DFVF_TERRAIN, D3DPOOL_DEFAULT, &pVB_, NULL);

	RestoreDeviceObjects();
	


	timer_.start();

	return S_OK;
}

void cQD3DView::Finalize()
{	
	InvalidateDeviceObjects();		

	SAFE_DELETE(pcTextureManager);
	SAFE_DELETE(pModelviewCam_);
	SAFE_RELEASE(pDevice_);
	SAFE_RELEASE(pD3D_);	
}

//복구 처리
HRESULT	cQD3DView::RestoreDeviceObjects()
{
	if(!pDevice_)
		return E_FAIL;		

	InitializeValue();
	InitializeFont();
	InitializeCamera();
	//pTestRoutine_->InitGeometryForTest();		
	
	if(!loadedHeightmapfilename_.isEmpty())
	{
		ImportHeightmap(loadedHeightmapfilename_);
	}
	else
	{
		InitVBIBforTLODTest();
	}	

	pDevice_->SetRenderState( D3DRS_LIGHTING, FALSE);
	pDevice_->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	//pDevice_->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );

	timer_.start();

	return S_OK;
}

//무효화 처리
HRESULT cQD3DView::InvalidateDeviceObjects()
{
	if(!pDevice_)
		return E_FAIL;

	timer_.stop();

	SAFE_RELEASE(pFont_);

	SAFE_RELEASE(pVB_);
	SAFE_RELEASE(pIB_);	

	return S_OK;
}

void cQD3DView::ClearScene(D3DXCOLOR ClearColor, float Z, DWORD Stencil)
{
	if(!pDevice_)
		return;

	pDevice_->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, (DWORD)ClearColor, Z, Stencil );
}

void cQD3DView::ClearRenderTarget(D3DXCOLOR ClearColor)
{
	pDevice_->Clear( 0, 0, D3DCLEAR_TARGET,(DWORD)ClearColor, 1.0f, 0 );
}

void cQD3DView::ClearDepthStencil(float Z, DWORD Stencil)
{

}

void cQD3DView::Update(float timeMS)
{
	pModelviewCam_->FrameMove(timeMS);
}

void cQD3DView::Idle()
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

void cQD3DView::InitializeFont()
{
	hFont_ = (HFONT)GetStockObject(SYSTEM_FONT);
	D3DXCreateFont(pDevice_, 20, 10, 1, TRUE, 1, 1, 5, 1,  NULL,L"Courier", &pFont_);	
}

void cQD3DView::DrawFps()
{
	RECT TextRect = {0.f, 0.f, 200.f, 100.f};
	char buff[16];
	sprintf(buff, "FPS : %5.2f", fps_);
	
	if(pFont_)
		pFont_->DrawTextA(NULL, buff, -1, &TextRect, DT_WORDBREAK |DT_VCENTER | DT_CENTER, D3DCOLOR_XRGB(255,0,255));
}

void cQD3DView::InitializeValue()
{
	addTime_ = 0;
	callCnt = 0;

	eyePos_ = D3DXVECTOR3(0, 0.f, -80.f);
	D3DXMatrixIdentity(&matWorld);	 
	
	startMousePos_ = QPoint(0,0);

	windowSize_ = size();

	mapCellNum_ = 0;
}

void cQD3DView::InitializeCamera()
{
	if(!pModelviewCam_)
		pModelviewCam_ = new CModelViewerCamera();

	if(!pModelviewCam_)
		return;	

	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 80.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	//DX 카메라
	pModelviewCam_->SetViewParams(&eyePos_, &vLookatPt);
	pModelviewCam_->SetProjParams(D3DX_PI / 4, 1.0f, 1.0f, 10000.f);	
	GetModelViewCamera()->SetWindow(windowSize_.width(), windowSize_.height());

	//스크린 공간으로 투영(글짜 출력용)
	D3DXVec3Project(&screenFontPos_,&objectFontPos_,&viewPort_,
		GetModelViewCamera()->GetProjMatrix(),
		GetModelViewCamera()->GetViewMatrix(),
		GetModelViewCamera()->GetWorldMatrix());
}

CModelViewerCamera* cQD3DView::GetModelViewCamera()
{
	return (CModelViewerCamera*)pModelviewCam_;
}

void cQD3DView::SetupCamera()
{
	if(pModelviewCam_)
	{
		pDevice_->SetTransform( D3DTS_WORLD, GetModelViewCamera()->GetWorldMatrix());	
		pDevice_->SetTransform( D3DTS_VIEW, GetModelViewCamera()->GetViewMatrix() );	
		pDevice_->SetTransform( D3DTS_PROJECTION, GetModelViewCamera()->GetProjMatrix());
	}
}

void cQD3DView::SetRenderMode(renderMode mode)
{
	if(mode == rdSolid)
		isWireMode_ = false;
	else
		isWireMode_ = true;
}

bool cQD3DView::ImportHeightmap(QString filename)
{	
	if(!pcTextureManager)
		return false;

	LPDIRECT3DTEXTURE9 pTexture = pcTextureManager->LoadTextureFromFile(filename.toStdString());
	if(!pTexture)
		return false;

	loadedHeightmapfilename_ = filename;

	D3DSURFACE_DESC desc;
	pTexture->GetLevelDesc(0, &desc);
	UINT width = desc.Width;
	UINT height = desc.Height;
	mapCellNum_	= width;

	if(!InitVBforHeightmap(pTexture))
		return false;

	if(!InitIBforHeightmap(pTexture))
		return false;

	return true;
}

bool cQD3DView::InitVBforHeightmap(LPDIRECT3DTEXTURE9 pTexture)
{
	if(pVB_)
		SAFE_RELEASE(pVB_);
		
	
	if(FAILED( pDevice_->CreateVertexBuffer(mapCellNum_ * mapCellNum_ * sizeof(TerrainVertex), 0, D3DFVF_TERRAIN, D3DPOOL_DEFAULT, &pVB_, NULL)) )
	{
		return false;
	}

	//텍츠쳐 메모리 락
	D3DLOCKED_RECT textureRect;
	pTexture->LockRect(0, &textureRect, 0, D3DLOCK_READONLY);
	
	void* pVertices = 0;	
	if(FAILED(pVB_->Lock(0, mapCellNum_ * mapCellNum_ * sizeof(TerrainVertex), (void**)&pVertices, 0)))
		return false;

	//디버깅시만 메모리 소거
	ZeroMemory(pVertices, mapCellNum_ * mapCellNum_ * sizeof(TerrainVertex));

	TerrainVertex v;
	TerrainVertex* pV = (TerrainVertex*)pVertices;

	for(DWORD z = 0 ; z < mapCellNum_; ++z)
	{
		for(DWORD x = 0 ; x < mapCellNum_ ; ++x)
		{
			v.pos.x = x * CELL_SIZE / 2.0f;		//원점 정렬
			v.pos.z = -(z * CELL_SIZE / 2.0f);	//z좌표가 반대임으로 -
			v.pos.y = (float)(*((LPDWORD)textureRect.pBits + x + z * (textureRect.Pitch/4)) & 0x000000ff) * CELL_HEIGHT;
			v.n.x = 0.f;//v.pos.x;
			v.n.y = v.pos.y;
			v.n.z = 0.f;//v.pos.z;
			
			v.color = D3DXCOLOR(255.f, 0.f, 0.f, 1.0f);

			D3DXVec3Normalize(&v.n, &v.n);
//			qDebug("vb  :%f %f %f", v.pos.x, v.pos.y, v.pos.z);

			*pV++ = v;
		}
	}


	pVB_->Unlock();
	
	pTexture->UnlockRect(0);
	

	return true;
}

bool cQD3DView::InitIBforHeightmap(LPDIRECT3DTEXTURE9 pTexture)
{
	if(pIB_)
		SAFE_RELEASE(pIB_);

	//사각형당 2개의 폴리곤 x 3개의 인덱스
	if(FAILED(pDevice_->CreateIndexBuffer((mapCellNum_ - 1) * (mapCellNum_ - 1)* 2 * sizeof(WORD) * 3,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIB_,
		NULL)))
		return false;


	WORD* pIndicies = NULL;
	int index = 0;
	if(FAILED(pIB_->Lock(0, (mapCellNum_ - 1) * (mapCellNum_ - 1) * 2 * sizeof(WORD) * 3, (VOID**)&pIndicies, 0)))
		return false;

	for(int z = 0 ; z < mapCellNum_ - 1 ; ++z)
	{
		for(int x = 0 ; x < mapCellNum_ - 1 ; ++x)
		{                        
			pIndicies[0 + index] = z * mapCellNum_ + x;
			pIndicies[1 + index] = (z + 1) * mapCellNum_ + x;            
			pIndicies[2 + index] = z * mapCellNum_ + (x + 1);            
			pIndicies[3 + index] = z * mapCellNum_ + (x + 1);
			pIndicies[4 + index] = (z + 1) * mapCellNum_ + x;
			pIndicies[5 + index] = (z + 1) * mapCellNum_ + (x + 1);            

			//qDebug("IB : %d %d %d -> %d %d %d",pIndicies[0+index], pIndicies[1+index], pIndicies[2+index],
			//	pIndicies[3+index], pIndicies[4+index], pIndicies[5+index]);

			index += 6;
		}
	}
	pIB_->Unlock();

	return true;
}

D3DMATERIAL9 cQD3DView::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient  = a;
	mtrl.Diffuse  = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power    = p;
	return mtrl;
}

D3DLIGHT9 cQD3DView::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_DIRECTIONAL;
	light.Ambient   = *color * 0.4f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

void cQD3DView::RenderHeightMap()
{	
	if(mapCellNum_ == 0)
		return;

	pDevice_->SetStreamSource(0, pVB_, 0, sizeof(TerrainVertex));
	pDevice_->SetIndices(pIB_);	
	pDevice_->SetFVF(D3DFVF_TERRAIN);	
	pDevice_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0,
		0,
		mapCellNum_ * mapCellNum_,
		0,
		(mapCellNum_ - 1) * (mapCellNum_ - 1) * 2);
}

void cQD3DView::SetupLight()
{
	D3DXVECTOR3 dir(-2.0f, 0.0f, 0.507f);
	D3DXCOLOR col(0.9f, 0.9f, 1.0f, 1.0f);
	D3DLIGHT9 light = InitDirectionalLight(&dir, &col);

	D3DMATERIAL9 mtrl  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	pDevice_->SetMaterial(&mtrl);

	pDevice_->SetLight(0, &light);
	pDevice_->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	pDevice_->SetRenderState(D3DRS_SPECULARENABLE, true);

	pDevice_->LightEnable(0, true);
}