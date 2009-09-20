/********************************************************************************
** Form generated from reading ui file 'MfaResultsForm.ui'
**
** Created: Sat Sep 19 22:32:15 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MFARESULTSFORM_H
#define UI_MFARESULTSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MfaResultsForm
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *sequenceNameLabel;
    QLineEdit *SequenceNameLineEdit;
    QLabel *sequenceTypeLabel;
    QLineEdit *SequenceTypeLineEdit;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGraphicsView *graphicsView;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *MfaResultsForm)
    {
        if (MfaResultsForm->objectName().isEmpty())
            MfaResultsForm->setObjectName(QString::fromUtf8("MfaResultsForm"));
        MfaResultsForm->resize(680, 590);
        MfaResultsForm->setMinimumSize(QSize(680, 590));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/mfa.png"), QSize(), QIcon::Normal, QIcon::Off);
        MfaResultsForm->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(MfaResultsForm);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setMargin(11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(MfaResultsForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setMargin(11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sequenceNameLabel = new QLabel(groupBox);
        sequenceNameLabel->setObjectName(QString::fromUtf8("sequenceNameLabel"));

        gridLayout->addWidget(sequenceNameLabel, 0, 0, 1, 1);

        SequenceNameLineEdit = new QLineEdit(groupBox);
        SequenceNameLineEdit->setObjectName(QString::fromUtf8("SequenceNameLineEdit"));

        gridLayout->addWidget(SequenceNameLineEdit, 0, 1, 1, 1);

        sequenceTypeLabel = new QLabel(groupBox);
        sequenceTypeLabel->setObjectName(QString::fromUtf8("sequenceTypeLabel"));

        gridLayout->addWidget(sequenceTypeLabel, 1, 0, 1, 1);

        SequenceTypeLineEdit = new QLineEdit(groupBox);
        SequenceTypeLineEdit->setObjectName(QString::fromUtf8("SequenceTypeLineEdit"));

        gridLayout->addWidget(SequenceTypeLineEdit, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(MfaResultsForm);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tabWidget = new QTabWidget(MfaResultsForm);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setPointSize(8);
        tabWidget->setFont(font);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 350, 350));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/cgr.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/graph_linear_regression.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_2, icon2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/graph_Dq.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_3, icon3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/graph_Cq.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_4, icon4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_5, icon5, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout_3->addLayout(verticalLayout, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 9, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(MfaResultsForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        horizontalLayout->addWidget(buttonBox);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(MfaResultsForm);
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), MfaResultsForm, SLOT(hide()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MfaResultsForm);
    } // setupUi

    void retranslateUi(QWidget *MfaResultsForm)
    {
        MfaResultsForm->setWindowTitle(QApplication::translate("MfaResultsForm", "MfaResultsForm", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MfaResultsForm", "Informaci\303\263n de la secuencia:", 0, QApplication::UnicodeUTF8));
        sequenceNameLabel->setText(QApplication::translate("MfaResultsForm", "Nombre:", 0, QApplication::UnicodeUTF8));
        sequenceTypeLabel->setText(QApplication::translate("MfaResultsForm", "Tipo:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MfaResultsForm", "Resultados del an\303\241lisis:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MfaResultsForm", "Juego del Caos", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MfaResultsForm", "Regresi\303\263n Lineal", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MfaResultsForm", "Espectro Dq", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MfaResultsForm", "Calor Espec\303\255fico An\303\241logo", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MfaResultsForm", "Tabla de Resultados", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MfaResultsForm);
    } // retranslateUi

};

namespace Ui {
    class MfaResultsForm: public Ui_MfaResultsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MFARESULTSFORM_H
