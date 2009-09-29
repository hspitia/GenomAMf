/********************************************************************************
** Form generated from reading ui file 'CgrParametersForm.ui'
**
** Created: Tue Sep 29 16:34:19 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CGRPARAMETERSFORM_H
#define UI_CGRPARAMETERSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CgrParametersForm
{
public:
    QGridLayout *gridLayout_2;
    QLabel *instructionsLabel;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *sequenceLabel;
    QListView *sequenceListView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CgrParametersForm)
    {
        if (CgrParametersForm->objectName().isEmpty())
            CgrParametersForm->setObjectName(QString::fromUtf8("CgrParametersForm"));
        CgrParametersForm->resize(520, 350);
        gridLayout_2 = new QGridLayout(CgrParametersForm);
        gridLayout_2->setMargin(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        instructionsLabel = new QLabel(CgrParametersForm);
        instructionsLabel->setObjectName(QString::fromUtf8("instructionsLabel"));
        instructionsLabel->setStyleSheet(QString::fromUtf8("QFrame {background-color: white;}"));
        instructionsLabel->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        instructionsLabel->setWordWrap(true);
        instructionsLabel->setMargin(9);

        gridLayout_2->addWidget(instructionsLabel, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout->setMargin(9);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        sequenceLabel = new QLabel(CgrParametersForm);
        sequenceLabel->setObjectName(QString::fromUtf8("sequenceLabel"));

        verticalLayout->addWidget(sequenceLabel);

        sequenceListView = new QListView(CgrParametersForm);
        sequenceListView->setObjectName(QString::fromUtf8("sequenceListView"));

        verticalLayout->addWidget(sequenceListView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 9, -1, -1);
        horizontalSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(CgrParametersForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(CgrParametersForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), CgrParametersForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CgrParametersForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(CgrParametersForm);
    } // setupUi

    void retranslateUi(QDialog *CgrParametersForm)
    {
        CgrParametersForm->setWindowTitle(QApplication::translate("CgrParametersForm", "Representaci\303\263n del Juego del Caos", 0, QApplication::UnicodeUTF8));
        instructionsLabel->setText(QApplication::translate("CgrParametersForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Par\303\241metros de Entrada</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Seleccione la secuencia para la cual desea generar la Representaci\303\263n del Juego del Caos.</p></body></html>", 0, QApplication::UnicodeUTF8));
        sequenceLabel->setText(QApplication::translate("CgrParametersForm", "Secuencia:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CgrParametersForm);
    } // retranslateUi

};

namespace Ui {
    class CgrParametersForm: public Ui_CgrParametersForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CGRPARAMETERSFORM_H
