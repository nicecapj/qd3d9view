/********************************************************************
	created:	2012/02/05
	created:	2012:5:2   0:47
	filename: 	QD3D9View_MsgHandler.cpp		
	author:		DRAGONKING(nicecapj@gmail.com)
	
	purpose:	process windows message
*********************************************************************/
#include "QD3D9View.h"
#include <qevent.h>

bool QD3DWiew::winEvent(MSG *message, long *result)
{
	if(SUCCEEDED(DefWindowProc(message->hwnd, message->message, message->wParam, message->lParam)))
		*result = 1;
	else 
		*result = 0;

	switch(message->message)
	{
	case WM_ACTIVATEAPP:
		{
			//Update(0);
			//PreRender();
			//Render();
			//PostRender();
		}
		break;
	case WM_PAINT:
		{			
		}
		break;
	case WM_SHOWWINDOW:
		{
		}
		break;

	case WM_CLOSE:
		{
		}
		break;
	default:
		{
			return false;
		}
	}

	return true;

}

void QD3DWiew::mousePressEvent(QMouseEvent *)
{

}

void QD3DWiew::mouseReleaseEvent(QMouseEvent *)
{

}

void QD3DWiew::mouseDoubleClickEvent(QMouseEvent *)
{

}

void QD3DWiew::mouseMoveEvent(QMouseEvent *)
{

}

void QD3DWiew::wheelEvent(QWheelEvent *)
{

}

void QD3DWiew::closeEvent(QCloseEvent *)
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