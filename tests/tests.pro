include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

HEADERS += \
        configurator_tests.h \
        ../app/configurator.h

SOURCES += \
        main.cpp \
        ../app/configurator.cpp
        
INCLUDEPATH += ../app
