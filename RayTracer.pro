TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT *= opengl widgets gui

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

QMAKE_CC = /usr/local/Cellar/llvm/5.0.0/bin/clang
QMAKE_CXX = /usr/local/Cellar/llvm/5.0.0/bin/clang++
QMAKE_LINK = /usr/local/Cellar/llvm/5.0.0/bin/clang++

LIBS += -L/usr/local/lib

TARGET = render

SOURCES += \
    src/main.cpp \
    src/RenderAlg.cpp \
    src/Scene.cpp \
    src/Light.cpp \
    src/Object.cpp \
    src/MainWindow.cpp \
    src/DirectIllumination.cpp \
    src/GlobalIllumination.cpp

HEADERS += \
    src/Definitions.h \
    src/RenderAlg.h \
    src/Scene.h \
    src/Light.h \
    src/Object.h \
    src/MainWindow.h \
    src/MyGraphicsView.h \
    src/DirectIllumination.h \
    src/GlobalIllumination.h



#INCLUDEPATH += $$PWD/../ilmbase-2.2.0
#INCLUDEPATH += $$PWD/../ilmbase-2.2.0/config
#INCLUDEPATH += $$PWD/../ilmbase-2.2.0/Iex
#LIBS += -L$$PWD/../ilmbase-2.2.0/Build/Imath -lImath-2_2

## Linear Alebra
CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../ElasticFEM/build-LinearAlgebra-Desktop-Debug/ -lLinearAlgebra
    DEPENDPATH += $$PWD/../../ElasticFEM/build-LinearAlgebra-Desktop-Debug
    PRE_TARGETDEPS += $$PWD/../../ElasticFEM/build-LinearAlgebra-Desktop-Debug/libLinearAlgebra.a
}
else {
    LIBS += -L$$PWD/../../ElasticFEM/build-LinearAlgebra-Desktop-Release/ -lLinearAlgebra
    DEPENDPATH += $$PWD/../../ElasticFEM/build-LinearAlgebra-Desktop-Release
    PRE_TARGETDEPS += $$PWD/../../ElasticFEM/build-LinearAlgebra-Desktop-Release/libLinearAlgebra.a
}
INCLUDEPATH += $$PWD/../../ElasticFEM/LinearAlgebra/inc


## TriMesh
CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../ElasticFEM/build-TriMesh-Desktop-Debug/ -lTriMesh
    DEPENDPATH += $$PWD/../../ElasticFEM/build-TriMesh-Desktop-Debug
    PRE_TARGETDEPS += $$PWD/../../ElasticFEM/build-TriMesh-Desktop-Debug/libTriMesh.a
}
else {
    LIBS += -L$$PWD/../../ElasticFEM/build-TriMesh-Desktop-Release/ -lTriMesh
    DEPENDPATH += $$PWD/../../ElasticFEM/build-TriMesh-Desktop-Release
    PRE_TARGETDEPS += $$PWD/../../ElasticFEM/build-TriMesh-Desktop-Release/libTriMesh.a
}
INCLUDEPATH += $$PWD/../../ElasticFEM/TriMesh/inc


## CDQueries
CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../ElasticFEM/build-CDQueries-Desktop-Debug/ -lCDQueries
    DEPENDPATH += $$PWD/../../ElasticFEM/build-CDQueries-Desktop-Debug
    PRE_TARGETDEPS += $$PWD/../../ElasticFEM/build-CDQueries-Desktop-Debug/libCDQueries.a
}
else {
    LIBS += -L$$PWD/../../ElasticFEM/build-CDQueries-Desktop-Release/ -lCDQueries
    DEPENDPATH += $$PWD/../../ElasticFEM/build-CDQueries-Desktop-Release
    PRE_TARGETDEPS += $$PWD/../../ElasticFEM/build-CDQueries-Desktop-Release/libCDQueries.a
}
INCLUDEPATH += $$PWD/../../ElasticFEM/CDQueries/inc


## IMath
LIBS += -L$$PWD/../ilmbase-2.2.0/Install/lib -lImath
DEPENDPATH += $$PWD/../ilmbase-2.2.0/Install/lib
PRE_TARGETDEPS += $$PWD/../ilmbase-2.2.0/Install/lib/libImath.a
INCLUDEPATH += $$PWD/../ilmbase-2.2.0/Install/include

FORMS += \
    src/MainWindow.ui
