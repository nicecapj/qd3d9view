#ifndef MAPEDITORD3D_H
#define MAPEDITORD3D_H

#include <QtGui/QMainWindow>
#include "ui_mapeditord3d.h"

class QD3DWiew;
class MapEditorD3D : public QMainWindow
{
	Q_OBJECT

public:
	MapEditorD3D(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MapEditorD3D();
	
public slots:
	void SetRenderModeWire();
	void SetRenderModeSolid();

private:
	Ui::MapEditorD3DClass ui;
	QD3DWiew* pD3DWidget_;
};

#endif // MAPEDITORD3D_H
