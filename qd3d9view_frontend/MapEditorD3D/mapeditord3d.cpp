#include "mapeditord3d.h"
#include "cQD3D9View.h"
#include <QMessageBox>
#include <qfiledialog.h>
#include "define.h"
#include "cTextureManager.h"

MapEditorD3D::MapEditorD3D(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	pD3DWidget_ = new cQD3DView(this);
	if(pD3DWidget_)
	{
		setCentralWidget(pD3DWidget_);	//안해주면 엄한 위치에 붙어있다.

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
		else
		{
			QObject::connect(ui.actionWire, SIGNAL(triggered()), this, SLOT(SetRenderModeWire()));    
			QObject::connect(ui.actionSolid, SIGNAL(triggered()), this, SLOT(SetRenderModeSolid()));    
			QObject::connect(ui.actionImportHeightmap, SIGNAL(triggered()), this, SLOT(ImportHeightmap()));    
			QObject::connect(ui.actionLight, SIGNAL(triggered()), this, SLOT(ShowLightDlg()));
		}

		//pD3DWidget_->show();
	}
}

MapEditorD3D::~MapEditorD3D()
{
	delete pD3DWidget_;
}


void MapEditorD3D::SetRenderModeWire()
{
	if(pD3DWidget_)
		pD3DWidget_->SetRenderMode(cQD3DView::rdWire);
}

void MapEditorD3D::SetRenderModeSolid()
{
	if(pD3DWidget_)
		pD3DWidget_->SetRenderMode(cQD3DView::rdSolid);
}

bool MapEditorD3D::ImportHeightmap()
{
	QString fileFilters = tr("HeightMap(*.bmp)");
	QString caption = tr("Select Heightmap image");
	QDir dir;
	QString dirStr = dir.currentPath();
	QString selectName = QFileDialog::getOpenFileName(this, caption, dirStr, fileFilters);
	if(selectName.isEmpty())
		return false;

	return pD3DWidget_->ImportHeightmap(selectName);	
}

void MapEditorD3D::ShowLightDlg()
{
	return pD3DWidget_->ShowLightDlg();
}