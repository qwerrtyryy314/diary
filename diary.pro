SOURCES += \
    main.cpp \
    mainwindow.cpp \
    customdelegate.cpp \
    browser.cpp \
    sqlconnectiondialog.cpp \
    treeitem.cpp \
    treemodel.cpp \
    itemselectionmodel.cpp \
    textedit.cpp \
    odt/tools/kzip.cpp \
    odt/tools/docmargin.cpp \
    odt/docformat/ooo/styleparser.cpp \
    odt/docformat/ooo/styleinformation.cpp \
    odt/docformat/ooo/formatproperty.cpp \
    odt/docformat/ooo/document.cpp \
    odt/docformat/ooo/converter.cpp

HEADERS += \
    mainwindow.h \
    customdelegate.h \
    browser.h \
    sqlconnectiondialog.h \
    treeitem.h \
    treemodel.h \
    common.h \
    itemselectionmodel.h \
    textedit.h \
    odt/allconfig.h \
    odt/tools/kzip.h \
    odt/tools/docmargin.h \
    odt/docformat/ooo/styleparser.h \
    odt/docformat/ooo/styleinformation.h \
    odt/docformat/ooo/formatproperty.h \
    odt/docformat/ooo/document.h \
    odt/docformat/ooo/converter.h

QT += core gui network sql widgets
#qt5 widgets

RESOURCES += \
    textedit.qrc

!include(odt/config.pri ) {
message( "odt/config.pri not found" )
}
