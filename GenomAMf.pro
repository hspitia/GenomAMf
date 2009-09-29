# #####################################################################
# Automatically generated by qmake (2.01a) mar sep 15 16:55:43 2009
# #####################################################################
TEMPLATE = app
TARGET = GenomAMf
QT += core \
    gui

# Input
HEADERS += src/cgr/ChaosGameRepresentation.h \
    src/utils/Definitions.h \
    src/utils/Message.h \
    src/utils/CustomSequencesContainer.h \
    src/gui/SequenceTreeItem.h \
    src/gui/TreeModel.h \
    src/gui/TreeItem.h \
    src/app/AppController.h \
    src/cgr/SeqLoader.h \
    src/gui/CgrParametersForm.h \
    src/gui/MainWindow.h \
    src/gui/MfaParametersForm.h \
    src/gui/MfaResultsForm.h \
    src/utils/Utils.h
SOURCES += src/cgr/ChaosGameRepresentation.cpp \
    src/utils/Message.cpp \
    src/utils/CustomSequencesContainer.cpp \
    src/gui/SequenceTreeItem.cpp \
    src/gui/TreeModel.cpp \
    src/gui/TreeItem.cpp \
    src/app/AppController.cpp \
    src/app/main.cpp \
    src/cgr/SeqLoader.cpp \
    src/gui/CgrParametersForm.cpp \
    src/gui/MainWindow.cpp \
    src/gui/MfaParametersForm.cpp \
    src/gui/MfaResultsForm.cpp
FORMS += src/gui/CgrParametersForm.ui \
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
INCLUDEPATH += /usr/include
LIBS += -L/usr/lib \
    -lbpp-utils \
    -lbpp-seq
RESOURCES += resources/resources.qrc
