TEMPLATE = app
TARGET   = genomAMf
DESTDIR  = bin
QT      += core \
           gui
           
WIN_USER_ENV_PATH = e:/programming

# Input
HEADERS +=    src/utils/LinearPlot.h \
              src/utils/NormalPlot.h \
              src/utils/Plot.h \
              src/mfa/MfaParametersSet.h \
              src/script/ScriptParametersSet.h \
              src/mfa/MfaResultsController.h \
              src/cra/DistancesModel.h \
              src/cra/CorrelationAnalysisResultsController.h \
              src/cra/CorrelationElement.h \
              src/utils/Trace.h \
              src/script/ScriptBuilder.h \
              src/gui/PreprocessingScriptParametersForm.h \
              src/mfa/MultifractalAnalysis.h \
              src/utils/MatrixOperations.h \
              src/cra/CorrelationAnalysis.h \
              src/gui/CorrelationAnalysisParametersForm.h \
              src/gui/CorrelationAnalysisResultsForm.h \
              src/mfa/Plotter.h \
              src/utils/Linear.h \
              src/mfa/SandBoxMethod.h \
              src/utils/SeqLoader.h \
              src/gui/CgrResultsForm.h \
              src/gui/ImageViewer.h \
              src/gui/SequenceListModel.h \
              src/utils/Matrix.h \
              src/cgr/ChaosGameRepresentation.h \
              src/utils/Definitions.h \
              src/utils/CustomSequencesContainer.h \
              src/gui/TreeModel.h \
              src/gui/TreeItem.h \
              src/app/AppController.h \
              src/gui/CgrParametersForm.h \
              src/gui/MainWindow.h \
              src/gui/MfaParametersForm.h \
              src/gui/MfaResultsForm.h \
              src/utils/Utils.h
              
SOURCES +=    src/utils/LinearPlot.cpp \
              src/utils/NormalPlot.cpp \
              src/utils/Plot.cpp \
              src/mfa/MfaParametersSet.cpp \
              src/script/ScriptParametersSet.cpp \
              src/mfa/MfaResultsController.cpp \
              src/cra/DistancesModel.cpp \
              src/gui/CorrelationAnalysisResultsForm.cpp \
              src/cra/CorrelationAnalysisResultsController.cpp \
              src/cra/CorrelationElement.cpp \
              src/script/ScriptBuilder.cpp \
              src/gui/PreprocessingScriptParametersForm.cpp \
              src/mfa/MultifractalAnalysis.cpp \
              src/cra/CorrelationAnalysis.cpp \
              src/gui/CorrelationAnalysisParametersForm.cpp \
              src/mfa/Plotter.cpp \
              src/mfa/SandBoxMethod.cpp \
              src/utils/SeqLoader.cpp \
              src/gui/CgrResultsForm.cpp \
              src/gui/ImageViewer.cpp \
              src/gui/SequenceListModel.cpp \
              src/cgr/ChaosGameRepresentation.cpp \
              src/utils/CustomSequencesContainer.cpp \
              src/gui/TreeModel.cpp \
              src/gui/TreeItem.cpp \
              src/app/AppController.cpp \
              src/app/main.cpp \
              src/gui/CgrParametersForm.cpp \
              src/gui/MainWindow.cpp \
              src/gui/MfaParametersForm.cpp \
              src/gui/MfaResultsForm.cpp
              
FORMS      += src/gui/PreprocessingScriptParametersForm.ui \
              src/gui/CorrelationAnalysisParametersForm.ui \
              src/gui/CorrelationAnalysisResultsForm.ui \
              src/gui/CgrResultsForm.ui \
              src/gui/ImageViewer.ui \
              src/gui/CgrParametersForm.ui \
              src/gui/MainWindow.ui \
              src/gui/MfaParametersForm.ui \
              src/gui/MfaResultsForm.ui
              
DEPENDPATH += . \
              src/ \
              src/app \
              src/cgr \
              src/gui \
              src/utils
              
INCLUDEPATH += . \
               src/ \
               src/app \
               src/cgr \
               src/utils \
               src/gui
               
unix { 
    INCLUDEPATH += /usr/include \
                   /usr/local/include \
                   /usr/local/qwt-5.2.0/include
    LIBS        += -L/usr/local/lib \
                   -lbpp-utils \
                   -lbpp-seq \
                   -lbpp-numcalc \
                   -lbpp-phyl \
                   -lbpp-qt \
                   -lbpp-raa
    LIBS        += -L/usr/lib \
                   -lmgl \
                   -lmgl-qt
    LIBS        += -L/usr/local/qwt-5.2.0/lib \
                   -lqwt
}

win32 { 
    INCLUDEPATH += $$WIN_USER_ENV_PATH/include \
                   $$WIN_USER_ENV_PATH/include/Qwt 
    LIBS        += -L$$WIN_USER_ENV_PATH/lib \
                   -lbpp-utils \
                   -lbpp-seq \
                   -lbpp-numcalc \
                   -lbpp-qt \
                   -lbpp-phyl \
                   -lmgl \
                   -lmgl-qt \
                   -lgsl \
                   -lqwt
    CONFIG      += console
}

RESOURCES    += resources/resources.qrc
TRANSLATIONS += translations/genomamf_es.ts \
                translations/genomamf_en.ts
UI_HEADERS_DIR += src/gui

unix {
    isEmpty(INSTALL_DIR) {
      INSTALL_DIR    = /usr/local/GenoAMf
    }
}

win32 {
    INSTALL_DIR    = C:/GenomAMf
}

#CONFIG += release

SUFFIX_STR = 
CONFIG(debug, debug|release) {
  SUFFIX_STR = $${DEBUG_SUFFIX}
}
else {
  SUFFIX_STR = $${RELEASE_SUFFIX}
}

#OBJECTS_DIR         = obj$$SUFFIX_STR
#MOC_DIR             = moc$$SUFFIX_STR
#RCC_DIR             = resources

target.path         = $$INSTALL_DIR/bin
#!exists(/usr/local/bin/$$TARGET) {
#  unix:target.extra = ln -s $$INSTALL_DIR/$$DESTDIR/$$TARGET /usr/local/bin/$$TARGET
#}

documentation.path  = $$INSTALL_DIR/doc
documentation.files = doc/*
source.path         = $$INSTALL_DIR/src
source.files        = src/*
templates.path      = $$INSTALL_DIR/templates
templates.files     = templates/*
tmp.path            = $$INSTALL_DIR/templates
tmp.files           = tmp/*

#unix {
#  !exists($$INSTALL_DIR/tmp) {
#    unix:tmp.extra      = mkdir $$INSTALL_DIR/tmp;
#  }
#}

INSTALLS += target \
            documentation \ 
            source \
            templates \
            tmp
