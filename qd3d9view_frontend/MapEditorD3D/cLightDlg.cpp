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

cLightDlg::cLightDlg(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
{	
	ui.setupUi(this);
	QObject::connect(ui.editDR, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeDR()));
	QObject::connect(ui.editDG, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeDG()));
	QObject::connect(ui.editDB, SIGNAL(textChanged(const QString&)), this, SLOT(OnTextChangeDB()));

	Initialize();
}

cLightDlg::~cLightDlg()
{
	Finalize();
}

void cLightDlg::Initialize()
{	

}

void cLightDlg::Finalize()
{

}


void cLightDlg::OnTextChangeDR(const QString& text )
{
	int value = text.toUInt();
	ui.sliderDR->setPageStep(value);
}

void cLightDlg::OnTextChangeDG(const QString& text )
{
	int value = text.toUInt();
	ui.sliderDG->setPageStep(value);
}

void cLightDlg::OnTextChangeDB(const QString& text )
{
	int value = text.toUInt();
	ui.sliderDB->setPageStep(value);
}