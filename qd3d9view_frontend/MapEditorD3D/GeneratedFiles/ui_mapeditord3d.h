/********************************************************************************
** Form generated from reading UI file 'mapeditord3d.ui'
**
** Created: Tue Feb 7 08:25:58 2012
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
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuRender;
    QMenu *menuRenderMode;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MapEditorD3DClass)
    {
        if (MapEditorD3DClass->objectName().isEmpty())
            MapEditorD3DClass->setObjectName(QString::fromUtf8("MapEditorD3DClass"));
        MapEditorD3DClass->resize(600, 400);
        actionSolid = new QAction(MapEditorD3DClass);
        actionSolid->setObjectName(QString::fromUtf8("actionSolid"));
        actionWire = new QAction(MapEditorD3DClass);
        actionWire->setObjectName(QString::fromUtf8("actionWire"));
        centralWidget = new QWidget(MapEditorD3DClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MapEditorD3DClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MapEditorD3DClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 17));
        menuRender = new QMenu(menuBar);
        menuRender->setObjectName(QString::fromUtf8("menuRender"));
        menuRenderMode = new QMenu(menuRender);
        menuRenderMode->setObjectName(QString::fromUtf8("menuRenderMode"));
        MapEditorD3DClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MapEditorD3DClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MapEditorD3DClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MapEditorD3DClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MapEditorD3DClass->setStatusBar(statusBar);

        menuBar->addAction(menuRender->menuAction());
        menuRender->addAction(menuRenderMode->menuAction());
        menuRenderMode->addAction(actionSolid);
        menuRenderMode->addAction(actionWire);

        retranslateUi(MapEditorD3DClass);

        QMetaObject::connectSlotsByName(MapEditorD3DClass);
    } // setupUi

    void retranslateUi(QMainWindow *MapEditorD3DClass)
    {
        MapEditorD3DClass->setWindowTitle(QApplication::translate("MapEditorD3DClass", "MapEditorD3D", 0, QApplication::UnicodeUTF8));
        actionSolid->setText(QApplication::translate("MapEditorD3DClass", "Solid", 0, QApplication::UnicodeUTF8));
        actionWire->setText(QApplication::translate("MapEditorD3DClass", "Wire", 0, QApplication::UnicodeUTF8));
        menuRender->setTitle(QApplication::translate("MapEditorD3DClass", "Render", 0, QApplication::UnicodeUTF8));
        menuRenderMode->setTitle(QApplication::translate("MapEditorD3DClass", "Render Mode", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapEditorD3DClass: public Ui_MapEditorD3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORD3D_H