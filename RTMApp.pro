# Add more folders to ship with the application, here
folder_01.source = qml/RTMApp
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE429150B

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# Define QMLJSDEBUGGER to allow debugging of QML in debug builds
# (This might significantly increase build time)
DEFINES += QMLJSDEBUGGER

maemo5 {
DEFINES += ON_MAEMO_5
}

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

QT += xmlpatterns network xml

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    settings.cpp \
    rtminterface.cpp \
    tasksmodel.cpp \
    xmltaskfactory.cpp \
    task.cpp \
    dummyapi.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    settings.h \
    rtminterface.h \
    tasksmodel.h \
    tasksmodel_p.h \
    xmltaskfactory.h \
    task.h \
    xmltaskfactory_p.h \
    rtminterface_p.h \
    dummyapi.h

OTHER_FILES += \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog
