/********************************************************************
	created:	2012/02/16
	created:	2012:16:2   2:06
	filename: 	cLightDlg.cpp
	author:		DRAGONKING(gmail.com)

	purpose:	빛 설정용 다이얼로그
*********************************************************************/
#include "cLightDlg.h"
#include <qmessagebox.h>
#include <qtextcodec.h>
#include <qslider.h>
//#include "define.h"
#include "cQD3D9View.h"

cLightDlg::cLightDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
{	
	ui.setupUi(this);	
	pMainView_ = (cQD3DView*)parent;

	Initialize();
}

cLightDlg::~cLightDlg()
{
	Finalize();
}

void cLightDlg::Initialize()
{	
	QObject::connect(ui.editDR, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeDR(const QString&)));
	QObject::connect(ui.editDG, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeDG(const QString&)));
	QObject::connect(ui.editDB, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeDB(const QString&)));

	QObject::connect(ui.editAR, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeAR(const QString&)));
	QObject::connect(ui.editAG, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeAG(const QString&)));
	QObject::connect(ui.editAB, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeAB(const QString&)));

	QObject::connect(ui.editSR, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeSR(const QString&)));
	QObject::connect(ui.editSG, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeSG(const QString&)));
	QObject::connect(ui.editSB, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeSB(const QString&)));
	QObject::connect(ui.editPow, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeSP(const QString&)));


	QObject::connect(ui.sliderDR, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderDR()));
	QObject::connect(ui.sliderDG, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderDG()));
	QObject::connect(ui.sliderDB, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderDB()));

	QObject::connect(ui.sliderAR, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderAR()));
	QObject::connect(ui.sliderAG, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderAG()));
	QObject::connect(ui.sliderAB, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderAB()));

	QObject::connect(ui.sliderSR, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderSR()));
	QObject::connect(ui.sliderSG, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderSG()));
	QObject::connect(ui.sliderSB, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderSB()));
	QObject::connect(ui.sliderPow, SIGNAL(valueChanged(int)), this, SLOT(OnChangeSliderSP()));

	
	QObject::connect(ui.spinPosX, SIGNAL(valueChanged(double)), this, SLOT(OnChangePosX()));
	QObject::connect(ui.spinPosY, SIGNAL(valueChanged(double)), this, SLOT(OnChangePosY()));
	QObject::connect(ui.spinPosZ, SIGNAL(valueChanged(double)), this, SLOT(OnChangePosZ()));

	QObject::connect(ui.spinDirX, SIGNAL(valueChanged(double)), this, SLOT(OnChangeDirX()));
	QObject::connect(ui.spinDirY, SIGNAL(valueChanged(double)), this, SLOT(OnChangeDirY()));
	QObject::connect(ui.spinDirZ, SIGNAL(valueChanged(double)), this, SLOT(OnChangeDirZ()));

		
	//D3DXCOLOR color(0.9f, 0.9f, 0.9f, 1.0f);
	::ZeroMemory(&light_, sizeof(light_));
	//light_.Type      = D3DLIGHT_DIRECTIONAL;
	//light_.Ambient   = color * 0.33f;
	//light_.Diffuse   = color;
	//light_.Specular  = color * 0.6f;
	//light_.Direction = D3DXVECTOR3(0.f,0.f,0.f);
	//light_.Direction = D3DXVECTOR3(1.f,-1.f,0.f);

	UpdateLightValue();
}

void cLightDlg::Finalize()
{

}

//------------------------------------------------------------------------------
void cLightDlg::OnTextChangeDR(const QString& text )
{
	int value = text.toUInt();
	ui.sliderDR->setValue(value);
	ui.editDR->setText(text);
}

void cLightDlg::OnTextChangeDG(const QString& text )
{
	int value = text.toUInt();
	ui.sliderDG->setValue(value);
	ui.editDG->setText(text);
}

void cLightDlg::OnTextChangeDB(const QString& text )
{
	int value = text.toUInt();
	ui.sliderDB->setValue(value);
	ui.editDB->setText(text);
}

void cLightDlg::OnChangeSliderDR()
{		
	QString valueStr = QString("%1").arg(ui.sliderDR->value());
	ui.editDR->setText(valueStr);

	light_.Diffuse.r = (float)ui.sliderDR->value()/255.f;
	ApplyLight();
}

void cLightDlg::OnChangeSliderDG()
{
	QString valueStr = QString("%1").arg(ui.sliderDG->value());
	ui.editDG->setText(valueStr);

	light_.Diffuse.g = (float)ui.sliderDG->value()/255.f;
	ApplyLight();
}

void cLightDlg::OnChangeSliderDB()
{
	QString valueStr = QString("%1").arg(ui.sliderDB->value());
	ui.editDB->setText(valueStr);

	light_.Diffuse.b = (float)ui.sliderDB->value()/255.f;
	ApplyLight();
}
//------------------------------------------------------------------------------
void cLightDlg::OnTextChangeAR(const QString& text )
{
	int value = text.toUInt();
	ui.sliderAR->setValue(value);
	ui.editAR->setText(text);
}

void cLightDlg::OnTextChangeAG(const QString& text )
{
	int value = text.toUInt();
	ui.sliderAG->setValue(value);
	ui.editAG->setText(text);
}

void cLightDlg::OnTextChangeAB(const QString& text )
{
	int value = text.toUInt();
	ui.sliderAB->setValue(value);
	ui.editAB->setText(text);
}

void cLightDlg::OnChangeSliderAR()
{
	QString valueStr = QString("%1").arg(ui.sliderAR->value());
	ui.editAR->setText(valueStr);

	light_.Ambient.r = (float)ui.sliderAR->value()/255;
	ApplyLight();
}

void cLightDlg::OnChangeSliderAG()
{
	QString valueStr = QString("%1").arg(ui.sliderAG->value());
	ui.editAG->setText(valueStr);

	light_.Ambient.g = (float)ui.sliderAG->value()/255.f;
	ApplyLight();
}

void cLightDlg::OnChangeSliderAB()
{
	QString valueStr = QString("%1").arg(ui.sliderAB->value());
	ui.editAB->setText(valueStr);

	light_.Ambient.b = (float)ui.sliderAB->value()/255.f;
	ApplyLight();
}
//------------------------------------------------------------------------------
void cLightDlg::OnTextChangeSR(const QString& text )
{
	int value = text.toUInt();
	ui.sliderSR->setValue(value);
	ui.editSR->setText(text);
}

void cLightDlg::OnTextChangeSG(const QString& text )
{
	int value = text.toUInt();
	ui.sliderSG->setValue(value);
	ui.editSG->setText(text);
}

void cLightDlg::OnTextChangeSB(const QString& text )
{
	int value = text.toUInt();
	ui.sliderSB->setValue(value);
	ui.editSB->setText(text);
}

void cLightDlg::OnTextChangeSP(const QString& text )
{
	int value = text.toUInt();
	ui.sliderPow->setValue(value);
	ui.editPow->setText(text);
}

void cLightDlg::OnChangeSliderSR()
{
	QString valueStr = QString("%1").arg(ui.sliderSR->value());
	ui.editSR->setText(valueStr);

	light_.Specular.r = (float)ui.sliderSR->value()/255.f;
	ApplyLight();
}

void cLightDlg::OnChangeSliderSG()
{
	QString valueStr = QString("%1").arg(ui.sliderSG->value());
	ui.editSG->setText(valueStr);

	light_.Specular.g = (float)ui.sliderSG->value()/255.f;
	ApplyLight();
}

void cLightDlg::OnChangeSliderSB()
{
	QString valueStr = QString("%1").arg(ui.sliderSB->value());
	ui.editSB->setText(valueStr);

	light_.Specular.b = (float)ui.sliderSB->value()/255.f;
	ApplyLight();
}

void cLightDlg::OnChangeSliderSP()
{
	QString valueStr = QString("%1").arg(ui.sliderPow->value());
	ui.editPow->setText(valueStr);

	//light_.Specular.b = ui.sliderSB->value();		세이더로 바꿀때 처리
	ApplyLight();
}
//------------------------------------------------------------------------------
void cLightDlg::OnChangePosX()
{
	light_.Position.x = ui.spinPosX->value();
	ApplyLight();
}

void cLightDlg::OnChangePosY()
{
	light_.Position.x = ui.spinPosY->value();
	ApplyLight();
}

void cLightDlg::OnChangePosZ()
{
	light_.Position.x = ui.spinPosZ->value();
	ApplyLight();
}
//------------------------------------------------------------------------------
void cLightDlg::OnChangeDirX()
{
	light_.Direction.x = ui.spinDirX->value();
	ApplyLight();
}

void cLightDlg::OnChangeDirY()
{
	light_.Direction.y = ui.spinDirY->value();
	ApplyLight();
}

void cLightDlg::OnChangeDirZ()
{
	light_.Direction.z = ui.spinDirZ->value();
	ApplyLight();
}
//------------------------------------------------------------------------------
void cLightDlg::UpdateLightValue()
{	
	ui.sliderDR->setValue((int)(255.f * light_.Diffuse.r));
	ui.sliderDG->setValue((int)(255.f * light_.Diffuse.g));
	ui.sliderDB->setValue((int)(255.f * light_.Diffuse.b));

	ui.sliderAR->setValue((int)(255.f * light_.Ambient.r));
	ui.sliderAG->setValue((int)(255.f * light_.Ambient.g));
	ui.sliderAB->setValue((int)(255.f * light_.Ambient.b));

	ui.sliderSR->setValue((int)(255.f * light_.Specular.r));
	ui.sliderSG->setValue((int)(255.f * light_.Specular.g));
	ui.sliderSB->setValue((int)(255.f * light_.Specular.b));

	ui.spinDirX->setValue(light_.Direction.x);
	ui.spinDirY->setValue(light_.Direction.y);
	ui.spinDirZ->setValue(light_.Direction.z);

	ui.spinPosX->setValue(light_.Position.x);
	ui.spinPosY->setValue(light_.Position.y);
	ui.spinPosZ->setValue(light_.Position.z);
}
//------------------------------------------------------------------------------
void cLightDlg::SetLight(D3DLIGHT9 light)
{
	light_ = light;
	UpdateLightValue();
}
//------------------------------------------------------------------------------
void cLightDlg::ApplyLight()
{
	if(pMainView_)
	{
		pMainView_->SetupLight(light_);
	}	
}