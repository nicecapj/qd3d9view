#include "mapeditord3d.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MapEditorD3D w;
	w.show();
	return a.exec();
}
