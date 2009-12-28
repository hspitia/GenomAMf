SOURCES = MatrixOperationsTest.cpp
CONFIG += qtestlib

# install
TARGET = test
target.path = .
sources.files = $$SOURCES \
    *.pro
sources.path = .
INSTALLS += target \
    sources
INCLUDEPATH += ../../src
