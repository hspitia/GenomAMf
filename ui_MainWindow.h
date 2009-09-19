/********************************************************************************
** Form generated from reading ui file 'MainWindow.ui'
**
** Created: Fri Sep 18 22:18:53 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *loadSequencesAction;
    QAction *exitAction;
    QAction *makeCgrAction;
    QAction *makeMultifractalAnalisysAction;
    QAction *actionCorrelaci_n;
    QAction *testAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menu_Archivo;
    QMenu *menuA_n_lisis;
    QMenu *menu_Herramientas;
    QMenu *menuJuego_del_Caos;
    QMenu *menuTest;
    QMenu *menu_Ventana;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(800, 600);
        MainWindowClass->setStyleSheet(QString::fromUtf8("/* QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 3px;\n"
"    margin-top: 1ex; \n"
"	padding: 9px;\n"
" }\n"
"\n"
" QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 0 3px;\n"
" }*/\n"
"\n"
"QDockWidget::title {\n"
"    text-align: left; /* align the text to the left */\n"
"    padding-left: 6px;\n"
"    padding-top: 4px;\n"
" }"));
        loadSequencesAction = new QAction(MainWindowClass);
        loadSequencesAction->setObjectName(QString::fromUtf8("loadSequencesAction"));
        exitAction = new QAction(MainWindowClass);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        makeCgrAction = new QAction(MainWindowClass);
        makeCgrAction->setObjectName(QString::fromUtf8("makeCgrAction"));
        makeMultifractalAnalisysAction = new QAction(MainWindowClass);
        makeMultifractalAnalisysAction->setObjectName(QString::fromUtf8("makeMultifractalAnalisysAction"));
        actionCorrelaci_n = new QAction(MainWindowClass);
        actionCorrelaci_n->setObjectName(QString::fromUtf8("actionCorrelaci_n"));
        testAction = new QAction(MainWindowClass);
        testAction->setObjectName(QString::fromUtf8("testAction"));
        centralwidget = new QWidget(MainWindowClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(4, 0, 0, 0);
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menu_Archivo = new QMenu(menubar);
        menu_Archivo->setObjectName(QString::fromUtf8("menu_Archivo"));
        menuA_n_lisis = new QMenu(menubar);
        menuA_n_lisis->setObjectName(QString::fromUtf8("menuA_n_lisis"));
        menu_Herramientas = new QMenu(menubar);
        menu_Herramientas->setObjectName(QString::fromUtf8("menu_Herramientas"));
        menuJuego_del_Caos = new QMenu(menubar);
        menuJuego_del_Caos->setObjectName(QString::fromUtf8("menuJuego_del_Caos"));
        menuTest = new QMenu(menubar);
        menuTest->setObjectName(QString::fromUtf8("menuTest"));
        menu_Ventana = new QMenu(menubar);
        menu_Ventana->setObjectName(QString::fromUtf8("menu_Ventana"));
        MainWindowClass->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowClass->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindowClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget = new QDockWidget(MainWindowClass);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayoutWidget_2 = new QWidget(dockWidgetContents);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(40, 30, 160, 80));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_3->setMargin(4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);


        verticalLayout_3->addLayout(verticalLayout);

        dockWidget->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menubar->addAction(menu_Archivo->menuAction());
        menubar->addAction(menuJuego_del_Caos->menuAction());
        menubar->addAction(menuA_n_lisis->menuAction());
        menubar->addAction(menu_Herramientas->menuAction());
        menubar->addAction(menu_Ventana->menuAction());
        menubar->addAction(menuTest->menuAction());
        menu_Archivo->addAction(loadSequencesAction);
        menu_Archivo->addAction(exitAction);
        menuA_n_lisis->addAction(makeMultifractalAnalisysAction);
        menuA_n_lisis->addAction(actionCorrelaci_n);
        menuJuego_del_Caos->addAction(makeCgrAction);
        menuTest->addAction(testAction);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "GenomAMf", 0, QApplication::UnicodeUTF8));
        loadSequencesAction->setText(QApplication::translate("MainWindowClass", "&Adicionar Secuencias", 0, QApplication::UnicodeUTF8));
        exitAction->setText(QApplication::translate("MainWindowClass", "&Salir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        exitAction->setToolTip(QApplication::translate("MainWindowClass", "Salir de la aplicaci\303\263n", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        makeCgrAction->setText(QApplication::translate("MainWindowClass", "Realizar &Representaci\303\263n ...", 0, QApplication::UnicodeUTF8));
        makeMultifractalAnalisysAction->setText(QApplication::translate("MainWindowClass", "&Multifractal ...", 0, QApplication::UnicodeUTF8));
        actionCorrelaci_n->setText(QApplication::translate("MainWindowClass", "&Correlaci\303\263n ...", 0, QApplication::UnicodeUTF8));
        testAction->setText(QApplication::translate("MainWindowClass", "&Test Action", 0, QApplication::UnicodeUTF8));
        menu_Archivo->setTitle(QApplication::translate("MainWindowClass", "&Archivo", 0, QApplication::UnicodeUTF8));
        menuA_n_lisis->setTitle(QApplication::translate("MainWindowClass", "A&n\303\241lisis", 0, QApplication::UnicodeUTF8));
        menu_Herramientas->setTitle(QApplication::translate("MainWindowClass", "&Herramientas", 0, QApplication::UnicodeUTF8));
        menuJuego_del_Caos->setTitle(QApplication::translate("MainWindowClass", "&Juego del Caos", 0, QApplication::UnicodeUTF8));
        menuTest->setTitle(QApplication::translate("MainWindowClass", "&Test", 0, QApplication::UnicodeUTF8));
        menu_Ventana->setTitle(QApplication::translate("MainWindowClass", "&Ventana", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindowClass", "toolBar", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("MainWindowClass", "Explorador de Objetos", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
