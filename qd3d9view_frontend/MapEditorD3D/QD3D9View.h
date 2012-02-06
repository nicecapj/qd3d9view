/*******************************************************************************
	created:	2012/02/04
	created:	2012:4:2   15:45
	filename: 	QD3D9View.h		
	author:		DRAGONKING(gmail.com)
	
	purpose:	directx 9.0 control for QT
*******************************************************************************/

#ifndef __QT_DIRECTX_WIEW_H__
#define __QT_DIRECTX_WIEW_H__

#include <QtGui/QWidget>
#include <qevent.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <QTimer.h>

#include <DxErr.h>
#pragma comment(lib,"DxErr.lib")
//------------------------------------------------------------------------------
class CBaseCamera;
class CModelViewerCamera;
class QD3DWiew : public QWidget
{
	Q_OBJECT

public:		

	QD3DWiew(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QD3DWiew();

	HRESULT Initialize();
	void	Finalize();

	void Update(float timeMS);

	void PreRender();
	void Render();
	void PostRender();

	const IDirect3D9*	GetD3D() { return pD3D_; }
	const IDirect3DDevice9* GetD3DDevice() { return pDevice_; }	

public slots:
		void Idle();

protected:
	// Event handlers
	//bool event(QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);

#ifndef QT_NO_WHEELEVENT
	virtual void wheelEvent(QWheelEvent *);
#endif

//	virtual void keyPressEvent(QKeyEvent *);
//	virtual void keyReleaseEvent(QKeyEvent *);
//	virtual void focusInEvent(QFocusEvent *);
//	virtual void focusOutEvent(QFocusEvent *);
//	virtual void enterEvent(QEvent *);
//	virtual void leaveEvent(QEvent *);
	virtual void paintEvent(QPaintEvent *);
//	virtual void moveEvent(QMoveEvent *);
	virtual void resizeEvent(QResizeEvent *p_event);
	virtual void closeEvent(QCloseEvent *);

//#ifndef QT_NO_CONTEXTMENU
//	virtual void contextMenuEvent(QContextMenuEvent *);
//#endif
//
//#ifndef QT_NO_ACTION
//	virtual void actionEvent(QActionEvent *);
//#endif
//
//#ifndef QT_NO_DRAGANDDROP
//	virtual void dragEnterEvent(QDragEnterEvent *);
//	virtual void dragMoveEvent(QDragMoveEvent *);
//	virtual void dragLeaveEvent(QDragLeaveEvent *);
//	virtual void dropEvent(QDropEvent *);
//#endif

	//virtual void showEvent(QShowEvent *);
	//virtual void hideEvent(QHideEvent *);

	virtual bool winEvent(MSG *message, long *result);

	// Misc. protected functions
	//virtual void changeEvent(QEvent *);
	//int metric(PaintDeviceMetric) const;
	//virtual void inputMethodEvent(QInputMethodEvent *);

private:
	HRESULT	BeginScene();
	HRESULT	EndScene();
	HRESULT	Present();	

	HRESULT	RestoreDeviceObjects();
	HRESULT InvalidateDeviceObjects();

	void	ClearScene( D3DXCOLOR ClearColor, float Z=1.0f, DWORD Stencil=0 );
	void	ClearRenderTarget( D3DXCOLOR ClearColor );
	void	ClearDepthStencil( float Z=1.0f, DWORD Stencil=0 );

	
	void InitializeFont();
	void DrawFps();

	void InitializeValue();

	CBaseCamera* pModelviewCam_;
	void InitializeCamera();
	CModelViewerCamera* GetModelViewCamera();
	void SetupCamera();

	//test
	void	SetupGeometryForTest();
	HRESULT InitGeometryForTest();
	void    FinalzeGeometryForTest();
	void	RenderGeometryForTest();


	LPDIRECT3DVERTEXBUFFER9         pVB_;
	LPDIRECT3DINDEXBUFFER9          pIB_;

	LPDIRECT3DVERTEXSHADER9         pVertexShader_;
	LPD3DXCONSTANTTABLE             pConstantTable_;
	LPDIRECT3DVERTEXDECLARATION9    pVertexDeclaration_;
	
	LPDIRECT3DPIXELSHADER9			pPixelShader_;
	
	IDirect3D9*						pD3D_;
	IDirect3DDevice9*				pDevice_;

	D3DPRESENT_PARAMETERS			d3dParam_;		
		
	float appTime_;

	//font
	HFONT							hFont_;
	LPD3DXFONT						pFont_;
	D3DXVECTOR3						screenFontPos_;
	D3DXVECTOR3						objectFontPos_;
	D3DVIEWPORT9					viewPort_;

	//for tool
	bool isWireMode_;		
	QTimer timer_;
	
	float fps_;
	float addTime_;
	int   callCnt;	
	

	QPoint startMousePos_;
	D3DXVECTOR3 eyePos_;	
	D3DXMATRIXA16 matWorld;

	QSize windowSize_;
};

#endif  __QT_DIRECTX_WIEW_H__