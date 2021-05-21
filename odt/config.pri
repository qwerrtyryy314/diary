#Require at least Qt 4.4.5
QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0) 
QT_VER_MIN = $$member(QT_VERSION, 1) 
QT_VER_PAT = $$member(QT_VERSION, 2) 

#message(version asplit $$QT_VERSION )
#message(version bsplit $$QT_VER_MAJ )
#message(version csplit $$QT_VER_MIN )
#message(version dsplit $$QT_VER_PAT )


##### discovery qt5 or qt4
#equals(QT_VER_MAJ,5) {
##### qt5 fix  /Users/pro/qt/qt5lang/5.1.1/clang_64/include
##### cache()
#LOCALQTDIR = /Users/pro/qt/qt51/qtbase/include
#LOCALQTDIR55555555 = /Users/pro/qt/qt5lang/5.1.1/clang_64/include
#DEPENDPATH +=  $$LOCALQTDIR
#INCLUDEPATH += $$LOCALQTDIR
##### if need!!!
#DEFINES += _HAVING_NEW_TEXTDOCUMENT_
#QT += printsupport
#DEFINES += _HAVEPRINTSUPPORTFLAG_
#message(Use qt5 from $$LOCALQTDIR config.pri setting )
#}

#equals(QT_VER_MAJ,4) {
##### http://www.qtcentre.org/wiki/index.php?title=Undocumented_qmake
##### qt4 fix  lessThan << minore
#message(Use qt4 setting edit config.pri )
#DEFINES += _QT4PRINTERSUPPORT_
#}


win32 {
    ########## window no pwd  #############
    BUILD_TREE_PATH = $$PWD
    message(Window path  $$BUILD_TREE_PATH)
}


unix {
    BUILD_TREE_PATH = $$PWD
    message(Unix path  $$BUILD_TREE_PATH)
}

macx {
    BUILD_TREE_PATH = $$PWD
    message(Mac path $$BUILD_TREE_PATH)
}

#message(git@95.215.44.40)
##src.pro
QT += printsupport xml

LIBS   += -lz
win32:LIBS	+= -luser32

macx {
RC_FILE = ODTicon.icns
QMAKE_INFO_PLIST = Info.plist
# QTPLUGIN     += qjpeg qgif qtiff
}



win32:RC_FILE = win.rc

### compiler default
LIB_EXTENSION = a

win32-msvc*{
LIB_EXTENSION = lib
DEFINES += VISUALSTUDIOCC_
CONFIG += embed_manifest_exe
message(win32 Visual Studio 2005 Compiler setting .......)
}

win32-g++{
DEFINES += MINGWCC_
message(win32 MINGW Compiler setting ....................)
}


contains(CONFIG, static): {

       ######### on main.cpp use defined ########

       DEFINES += _COMPOSE_STATIC_
        exists($$[QT_INSTALL_PLUGINS]/imageformats/libqjpeg.$$LIB_EXTENSION) {
            QTPLUGIN += qjpeg
            DEFINES += _USE_qjpeg
        }
        exists($$[QT_INSTALL_PLUGINS]/imageformats/libqgif.$$LIB_EXTENSION) {
            QTPLUGIN += qgif
            DEFINES += _USE_qgif
        }
        exists($$[QT_INSTALL_PLUGINS]/imageformats/libqmng.$$LIB_EXTENSION) {
            QTPLUGIN += qmng
            DEFINES += _USE_qmng
        }
        exists($$[QT_INSTALL_PLUGINS]/imageformats/libqtiff.$$LIB_EXTENSION) {
            QTPLUGIN += qtiff
            DEFINES += _USE_qtiff
        }
}
