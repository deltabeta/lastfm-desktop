TEMPLATE = app
TARGET = AudioScrobbler
CONFIG += unicorn moose 
QT += xml network

include( $$SRC_DIR/include.pro )

SOURCES += $$system( sh $$TOOLS_DIR/findsources cpp )
HEADERS += $$system( sh $$TOOLS_DIR/findsources h ) qmake.pro
FORMS += $$system( sh $$TOOLS_DIR/findsources ui )
RESOURCES += $$system( sh $$TOOLS_DIR/findsources qrc )
RESOURCES += $$SRC_DIR/common/qrc/common.qrc

INCLUDEPATH += .
