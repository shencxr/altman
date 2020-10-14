TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    test_driver.cpp \
    test.cpp \
    test_avl.cpp \
    singleton.cpp \
    uniqueptr.cpp \
    thread_test.cpp \
    sharedptr.cpp \
    display_it_cate.cpp \
    fstest.cpp

HEADERS += \
    test_driver.h \
    binary_search_tree.h \
    avl.h \
    myiterator.h
