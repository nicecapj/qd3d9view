#ifndef MAPEDITORD3D_H
#define MAPEDITORD3D_H

#include <QtGui/QMainWindow>
#include "ui_mapeditord3d.h"

class cQD3DView;
class MapEditorD3D : public QMainWindow
{
	Q_OBJECT

public:
	MapEditorD3D(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MapEditorD3D();
	
public slots:
	void SetRenderModeWire();
	void SetRenderModeSolid();
	bool ImportHeightmap();

private:
	Ui::MapEditorD3DClass ui;
	cQD3DView* pD3DWidget_;
};

#endif // MAPEDITORD3D_H
