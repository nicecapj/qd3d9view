/********************************************************************
	created:	2012/02/05
	created:	2012:5:2   0:47
	filename: 	QD3D9View_MsgHandler.cpp		
	author:		DRAGONKING(nicecapj@gmail.com)
	
	purpose:	process windows message
*********************************************************************/
#include "QD3D9View.h"
#include <qevent.h>

#define DXUT_AUTOLIB
#include "DXUT.h"
#include "DXUTcamera.h"

bool QD3DWiew::winEvent(MSG *message, long *result)
{
	if(SUCCEEDED(DefWindowProc(message->hwnd, message->message, message->wParam, message->lParam)))
		*result = 1;
	else 
		*result = 0;

	if(pModelviewCam_)
		pModelviewCam_->HandleMessages(message->hwnd, message->message, message->wParam, message->lParam);

	return true;

}

void QD3DWiew::mousePressEvent(QMouseEvent * event)
{
	//if(event->button() & Qt::RightButton)
	//{		
	//	startMousePos_.setX(event->x());
	//	startMousePos_.setY(event->y());
	//}
}

void QD3DWiew::mouseReleaseEvent(QMouseEvent * event)
{

}

void QD3DWiew::mouseDoubleClickEvent(QMouseEvent * event)
{

}

void QD3DWiew::mouseMoveEvent(QMouseEvent * event)
{		
	////if(event->button() & Qt::RightButton)	//moveevnet에서는 button값이 비정상임
	//
	//if(event->buttons() == Qt::RightButton)
	//{		
	//	QPoint endPT(event->x(), event->y());
	//	QPoint moveFactor(endPT.x() - startMousePos_.x(), endPT.y() - startMousePos_.y());

	//	D3DXMATRIXA16 matRotX;
	//	D3DXMATRIXA16 matRotY;

	//	//if(moveFactor.x() > 0)						
	//	//{
	//	//	D3DXMatrixRotationX(&matRotX, 10.f);
	//	//	matWorld *= matRotX;
	//	//}
	//	//else
	//	//{
	//	//	D3DXMatrixRotationX(&matRotX, -10.f);
	//	//	matWorld *= matRotX;
	//	//}

	//	if(moveFactor.y() > 0)
	//	{
	//		D3DXMatrixRotationY(&matRotY, 10.f);
	//		matWorld *= matRotY;
	//	}
	//	else
	//	{
	//		D3DXMatrixRotationY(&matRotY, -10.f);
	//		matWorld *= matRotY;
	//	}
	//}	
}

void QD3DWiew::wheelEvent(QWheelEvent * event)
{	
	float delte = event->delta();
	if(delte > 0.f)
	{
		eyePos_.z += 10.f;
	}
	else
	{
		eyePos_.z -= 10.f;
	}

	InitializeCamera();
}

void QD3DWiew::closeEvent(QCloseEvent * event)
{

}

void QD3DWiew::paintEvent(QPaintEvent *paintE)
{
	Q_UNUSED(paintE);
	
	//Update();
	PreRender();
	Render();
	PostRender();
}

//리사이즈하게 되면, 디바이스등등 소실된다.
void QD3DWiew::resizeEvent(QResizeEvent *p_event)
{
	QSize newSize = size();
	if(p_event)
	{
		newSize = p_event->size();
		// if( width()==newSize.width() && height()==newSize.height() ) return;
		QWidget::resizeEvent( p_event );
	}

	UINT nWidth = newSize.width();
	UINT nHeight = newSize.height();

	HRESULT hr = S_OK;

	if(!pDevice_) 
		return;

	viewPort_.Height = nHeight;
	viewPort_.Width = nWidth;
	viewPort_.MaxZ = nHeight;
	viewPort_.MinZ = nHeight;
	viewPort_.X = 0.f;
	viewPort_.Y = 0.f;

	d3dParam_.BackBufferWidth = newSize.width();
	d3dParam_.BackBufferHeight = newSize.height();

	InvalidateDeviceObjects();

	hr = pDevice_->Reset(&d3dParam_);

	RestoreDeviceObjects();

}