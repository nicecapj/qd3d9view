/********************************************************************************
** Form generated from reading UI file 'mapeditord3d.ui'
**
** Created: Thu Feb 16 02:10:40 2012
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITORD3D_H
#define UI_MAPEDITORD3D_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditorD3DClass
{
public:
    QAction *actionSolid;
    QAction *actionWire;
    QAction *actionOepn;
    QAction *actionImportHeightmap;
    QAction *actionLight;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuRender;
    QMenu *menuRenderMode;
    QMenu *menuFile;
    QMenu *menuImport;
    QMenu *menuSetting;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MapEditorD3DClass)
    {
        if (MapEditorD3DClass->objectName().isEmpty())
            MapEditorD3DClass->setObjectName(QString::fromUtf8("MapEditorD3DClass"));
        MapEditorD3DClass->resize(934, 740);
        actionSolid = new QAction(MapEditorD3DClass);
        actionSolid->setObjectName(QString::fromUtf8("actionSolid"));
        actionWire = new QAction(MapEditorD3DClass);
        actionWire->setObjectName(QString::fromUtf8("actionWire"));
        actionOepn = new QAction(MapEditorD3DClass);
        actionOepn->setObjectName(QString::fromUtf8("actionOepn"));
        actionImportHeightmap = new QAction(MapEditorD3DClass);
        actionImportHeightmap->setObjectName(QString::fromUtf8("actionImportHeightmap"));
        actionLight = new QAction(MapEditorD3DClass);
        actionLight->setObjectName(QString::fromUtf8("actionLight"));
        centralWidget = new QWidget(MapEditorD3DClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MapEditorD3DClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MapEditorD3DClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 934, 17));
        menuRender = new QMenu(menuBar);
        menuRender->setObjectName(QString::fromUtf8("menuRender"));
        menuRenderMode = new QMenu(menuRender);
        menuRenderMode->setObjectName(QString::fromUtf8("menuRenderMode"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuImport = new QMenu(menuFile);
        menuImport->setObjectName(QString::fromUtf8("menuImport"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        MapEditorD3DClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MapEditorD3DClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MapEditorD3DClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MapEditorD3DClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MapEditorD3DClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuRender->menuAction());
        menuBar->addAction(menuSetting->menuAction());
        menuRender->addAction(menuRenderMode->menuAction());
        menuRenderMode->addAction(actionSolid);
        menuRenderMode->addAction(actionWire);
        menuFile->addAction(menuImport->menuAction());
        menuImport->addAction(actionImportHeightmap);
        menuSetting->addAction(actionLight);

        retranslateUi(MapEditorD3DClass);

        QMetaObject::connectSlotsByName(MapEditorD3DClass);
    } // setupUi

    void retranslateUi(QMainWindow *MapEditorD3DClass)
    {
        MapEditorD3DClass->setWindowTitle(QApplication::translate("MapEditorD3DClass", "MapEditorD3D", 0, QApplication::UnicodeUTF8));
        actionSolid->setText(QApplication::translate("MapEditorD3DClass", "Solid", 0, QApplication::UnicodeUTF8));
        actionWire->setText(QApplication::translate("MapEditorD3DClass", "Wire", 0, QApplication::UnicodeUTF8));
        actionOepn->setText(QApplication::translate("MapEditorD3DClass", "Oepn", 0, QApplication::UnicodeUTF8));
        actionImportHeightmap->setText(QApplication::translate("MapEditorD3DClass", "Heightmap", 0, QApplication::UnicodeUTF8));
        actionLight->setText(QApplication::translate("MapEditorD3DClass", "Light", 0, QApplication::UnicodeUTF8));
        menuRender->setTitle(QApplication::translate("MapEditorD3DClass", "Render", 0, QApplication::UnicodeUTF8));
        menuRenderMode->setTitle(QApplication::translate("MapEditorD3DClass", "Render Mode", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MapEditorD3DClass", "File", 0, QApplication::UnicodeUTF8));
        menuImport->setTitle(QApplication::translate("MapEditorD3DClass", "Import", 0, QApplication::UnicodeUTF8));
        menuSetting->setTitle(QApplication::translate("MapEditorD3DClass", "Setting", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapEditorD3DClass: public Ui_MapEditorD3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORD3D_H
