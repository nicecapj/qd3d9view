#include "mapeditord3d.h"
#include "QD3D9View.h"
#include <QMessageBox>
#include "define.h"

MapEditorD3D::MapEditorD3D(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	pD3DWidget_ = new QD3DWiew(this);
	if(pD3DWidget_)
	{
		HRESULT hr;
		if(FAILED(hr = pD3DWidget_->Initialize()))
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle(QObject::tr("Failed to initialize DirectX"));
			QString msg(DXGetErrorDescriptionA(hr));
			msgBox.setText(msg);
			msgBox.setIcon(QMessageBox::Critical);
			msgBox.exec();

			SAFE_DELETE(pD3DWidget_);
		}

		pD3DWidget_->show();
	}
}

MapEditorD3D::~MapEditorD3D()
{
	delete pD3DWidget_;
}
