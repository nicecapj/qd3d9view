/********************************************************************
	created:	2012/02/16
	created:	2012:16:2   2:06
	filename: 	cLightDlg.h		
	author:		DRAGONKING(gmail.com)
	
	purpose:	�� ������ ���̾�α�
*********************************************************************/
#ifndef __LIGHT_DLG_H__
#define __LIGHT_DLG_H__

#include <QtGui/qdialog.h>
#include "ui_cLightDlg.h"

class cLightDlg : public QDialog
{
	Q_OBJECT

public:
	cLightDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~cLightDlg();

protected:

private:
	void Initialize();
	void Finalize();

	void OnTextChangeDR(const QString& text );
	void OnTextChangeDG(const QString& text );
	void OnTextChangeDB(const QString& text );


	Ui::LightDialog ui;

};

#endif /*__LIGHT_DLG_H__*/