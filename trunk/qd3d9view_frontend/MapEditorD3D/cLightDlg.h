/********************************************************************
	created:	2012/02/16
	created:	2012:16:2   2:06
	filename: 	cLightDlg.h		
	author:		DRAGONKING(gmail.com)
	
	purpose:	빛 설정용 다이얼로그
*********************************************************************/
#ifndef __LIGHT_DLG_H__
#define __LIGHT_DLG_H__

#include <QtGui/qdialog.h>
#include "ui_cLightDlg.h"
#include <d3d9.h>
#include <d3dx9.h>

class cQD3DView;
class cLightDlg : public QDialog
{
	Q_OBJECT

public:
	cLightDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~cLightDlg();
	
	void UpdateLightValue();
	void SetLight(D3DLIGHT9 light);
	void ApplyLight();


public slots:
	void OnTextChangeDR(const QString& text );
	void OnTextChangeDG(const QString& text );
	void OnTextChangeDB(const QString& text );

	void OnTextChangeAR(const QString& text );
	void OnTextChangeAG(const QString& text );
	void OnTextChangeAB(const QString& text );

	void OnTextChangeSR(const QString& text );
	void OnTextChangeSG(const QString& text );
	void OnTextChangeSB(const QString& text );
	void OnTextChangeSP(const QString& text );	

	void OnChangeSliderDR();
	void OnChangeSliderDG();
	void OnChangeSliderDB();

	void OnChangeSliderAR();
	void OnChangeSliderAG();
	void OnChangeSliderAB();

	void OnChangeSliderSR();
	void OnChangeSliderSG();
	void OnChangeSliderSB();
	void OnChangeSliderSP();

	void OnChangePosX();
	void OnChangePosY();
	void OnChangePosZ();

	void OnChangeDirX();
	void OnChangeDirY();
	void OnChangeDirZ();

protected:	

private:
	void Initialize();
	void Finalize();

	Ui::LightDialog ui;

	D3DLIGHT9 light_;
	cQD3DView* pMainView_;
};

#endif /*__LIGHT_DLG_H__*/