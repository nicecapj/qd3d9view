/********************************************************************************
** Form generated from reading UI file 'mapeditord3d.ui'
**
** Created: Sat Feb 4 15:37:38 2012
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
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditorD3DClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MapEditorD3DClass)
    {
        if (MapEditorD3DClass->objectName().isEmpty())
            MapEditorD3DClass->setObjectName(QString::fromUtf8("MapEditorD3DClass"));
        MapEditorD3DClass->resize(600, 400);
        menuBar = new QMenuBar(MapEditorD3DClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MapEditorD3DClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MapEditorD3DClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MapEditorD3DClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MapEditorD3DClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MapEditorD3DClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MapEditorD3DClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MapEditorD3DClass->setStatusBar(statusBar);

        retranslateUi(MapEditorD3DClass);

        QMetaObject::connectSlotsByName(MapEditorD3DClass);
    } // setupUi

    void retranslateUi(QMainWindow *MapEditorD3DClass)
    {
        MapEditorD3DClass->setWindowTitle(QApplication::translate("MapEditorD3DClass", "MapEditorD3D", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapEditorD3DClass: public Ui_MapEditorD3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITORD3D_H
