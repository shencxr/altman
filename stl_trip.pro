TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    test_driver.cpp \
    test.cpp \
    test_avl.cpp \
    singleton.cpp

HEADERS += \
    test_driver.h \
    binary_search_tree.h \
    avl.h \
    myiterator.h
