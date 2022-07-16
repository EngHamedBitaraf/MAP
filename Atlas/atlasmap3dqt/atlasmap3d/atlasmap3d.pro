
QT += core
QT -= gui
QT += widgets
QT += opengl
TEMPLATE = lib
DEFINES += ATLASMAP3D_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AtlasMainWindow.cpp \
    NXDockWidget.cpp \
    NXDockWidgetTabBar.cpp \
    NXDockWidgetTabButton.cpp \
    NXDockWidgetTitle.cpp \
    DataManager.cpp \
    DataRecord.cpp \
    DataTree.cpp \
    FeatureStyleSettingDlg.cpp \
    FontVisitor.cpp \
    MapController.cpp \
    MousePicker.cpp \
    PluginInterface.cpp \
    PluginManager.cpp \
    SettingsManager.cpp \
    Compass.cpp \
    ViewerWidget.cpp

HEADERS += \
    NameSpace.h \
    AtlasMainWindow.h \
    NXDockWidget.h \
    NXDockWidgetTabBar.h \
    NXDockWidgetTabButton.h \
    NXDockWidgetTitle.h \
    atlasmainwindow_global.h \
    DataFormats.h \
    DataManager.h \
    DataRecord.h \
    DataTree.h \
    FeatureStyleSettingDlg.h \
    FindNode.hpp \
    FontVisitor.h \
    MapController.h \
    MousePicker.h \
    PluginInterface.h \
    PluginManager.h \
    SettingsManager.h \
    Compass.h \
    ViewerWidget.h \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    AtlasMainWindow.ui \
    FeatureStyleSettingDlg.ui \
    StyleTab.ui

DISTFILES +=

#LIBS  = -L$$PWD/../plugins
#unix:!macx: LIBS += -L/home/client110/build-atlas/plugins

unix:!macx: LIBS += -L$$PWD/../../osgQt/build-topic-Qt4/lib/ -losgQt5

INCLUDEPATH += $$PWD/../../osgQt/osgQt-topic-Qt4/include
DEPENDPATH += $$PWD/../../osgQt/osgQt-topic-Qt4/include

