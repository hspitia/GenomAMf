/********************************************************************************
** Form generated from reading ui file 'MfaParametersForm.ui'
**
** Created: Sat Sep 26 16:25:51 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MFAPARAMETERSFORM_H
#define UI_MFAPARAMETERSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MfaParametersForm
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *cgrlabel;
    QListView *cgrListView;
    QGroupBox *qValuesGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *qMinLabel;
    QSpinBox *qMinSpinBox;
    QHBoxLayout *horizontalLayout;
    QLabel *qMaxLabel;
    QSpinBox *qMaxSpinBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;
    QLabel *instructionsLabel;

    void setupUi(QDialog *MfaParametersForm)
    {
        if (MfaParametersForm->objectName().isEmpty())
            MfaParametersForm->setObjectName(QString::fromUtf8("MfaParametersForm"));
        MfaParametersForm->resize(520, 460);
        gridLayout_2 = new QGridLayout(MfaParametersForm);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setMargin(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(9);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cgrlabel = new QLabel(MfaParametersForm);
        cgrlabel->setObjectName(QString::fromUtf8("cgrlabel"));

        verticalLayout->addWidget(cgrlabel);

        cgrListView = new QListView(MfaParametersForm);
        cgrListView->setObjectName(QString::fromUtf8("cgrListView"));

        verticalLayout->addWidget(cgrListView);


        verticalLayout_2->addLayout(verticalLayout);

        qValuesGroupBox = new QGroupBox(MfaParametersForm);
        qValuesGroupBox->setObjectName(QString::fromUtf8("qValuesGroupBox"));
        qValuesGroupBox->setFlat(false);
        qValuesGroupBox->setCheckable(false);
        horizontalLayout_5 = new QHBoxLayout(qValuesGroupBox);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setMargin(11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        qMinLabel = new QLabel(qValuesGroupBox);
        qMinLabel->setObjectName(QString::fromUtf8("qMinLabel"));

        horizontalLayout_2->addWidget(qMinLabel);

        qMinSpinBox = new QSpinBox(qValuesGroupBox);
        qMinSpinBox->setObjectName(QString::fromUtf8("qMinSpinBox"));
        qMinSpinBox->setMinimum(-20);
        qMinSpinBox->setMaximum(-1);
        qMinSpinBox->setValue(-10);

        horizontalLayout_2->addWidget(qMinSpinBox);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        qMaxLabel = new QLabel(qValuesGroupBox);
        qMaxLabel->setObjectName(QString::fromUtf8("qMaxLabel"));

        horizontalLayout->addWidget(qMaxLabel);

        qMaxSpinBox = new QSpinBox(qValuesGroupBox);
        qMaxSpinBox->setObjectName(QString::fromUtf8("qMaxSpinBox"));
        qMaxSpinBox->setMinimum(2);
        qMaxSpinBox->setMaximum(20);
        qMaxSpinBox->setValue(10);

        horizontalLayout->addWidget(qMaxSpinBox);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        horizontalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(qValuesGroupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 9, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(MfaParametersForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_4->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        instructionsLabel = new QLabel(MfaParametersForm);
        instructionsLabel->setObjectName(QString::fromUtf8("instructionsLabel"));
        instructionsLabel->setStyleSheet(QString::fromUtf8("QLabel{background-color: rgb(255, 255, 255);}\n"
""));
        instructionsLabel->setTextFormat(Qt::RichText);
        instructionsLabel->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        instructionsLabel->setWordWrap(true);
        instructionsLabel->setMargin(9);

        gridLayout->addWidget(instructionsLabel, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(MfaParametersForm);
        QObject::connect(buttonBox, SIGNAL(rejected()), MfaParametersForm, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), MfaParametersForm, SLOT(accept()));

        QMetaObject::connectSlotsByName(MfaParametersForm);
    } // setupUi

    void retranslateUi(QDialog *MfaParametersForm)
    {
        MfaParametersForm->setWindowTitle(QApplication::translate("MfaParametersForm", "An\303\241lisis Multifractal", 0, QApplication::UnicodeUTF8));
        cgrlabel->setText(QApplication::translate("MfaParametersForm", "Representaci\303\263n del Juego del Caos:", 0, QApplication::UnicodeUTF8));
        qValuesGroupBox->setTitle(QApplication::translate("MfaParametersForm", "Valores para rango q:", 0, QApplication::UnicodeUTF8));
        qMinLabel->setText(QApplication::translate("MfaParametersForm", "q m\303\255nimo:", 0, QApplication::UnicodeUTF8));
        qMaxLabel->setText(QApplication::translate("MfaParametersForm", "q m\303\241ximo:", 0, QApplication::UnicodeUTF8));
        instructionsLabel->setText(QApplication::translate("MfaParametersForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Par\303\241metros de Entrada</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Seleccione la representaci\303\263n del Juego del Caos sobre la cual realizar\303\241 el an\303\241lisis multifractal y especifique los valores <span style=\" font-style:italic;\">q</span> m\303\255nimo y <span style=\" font-style:italic;\">q</span> m\303\241ximo.</p></body></html>", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MfaParametersForm);
    } // retranslateUi

};

namespace Ui {
    class MfaParametersForm: public Ui_MfaParametersForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MFAPARAMETERSFORM_H
