/****************************************************************************
** Meta object code from reading C++ file 'mapeditord3d.h'
**
** Created: Thu Feb 16 02:35:42 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mapeditord3d.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapeditord3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapEditorD3D[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      34,   13,   13,   13, 0x0a,
      60,   13,   55,   13, 0x0a,
      78,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapEditorD3D[] = {
    "MapEditorD3D\0\0SetRenderModeWire()\0"
    "SetRenderModeSolid()\0bool\0ImportHeightmap()\0"
    "ShowLightDlg()\0"
};

const QMetaObject MapEditorD3D::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MapEditorD3D,
      qt_meta_data_MapEditorD3D, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapEditorD3D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapEditorD3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapEditorD3D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapEditorD3D))
        return static_cast<void*>(const_cast< MapEditorD3D*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MapEditorD3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetRenderModeWire(); break;
        case 1: SetRenderModeSolid(); break;
        case 2: { bool _r = ImportHeightmap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: ShowLightDlg(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
