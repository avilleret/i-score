TEMPLATE = app
CONFIG += debug
TARGET = i-score
DEPENDPATH += . \
include \
#lib \
headers/data \
headers/GUI \
src/data \
src/GUI \
lib/Editor/CSP

linux-g++ {
INCLUDEPATH += . headers/GUI headers/data /usr/local/include/IScore /usr/local/include/libxml2
}
linux-g++-64 {
INCLUDEPATH += . headers/GUI headers/data /usr/local/include/IScore /usr/local/include/libxml2
}
macx-g++ {
INCLUDEPATH += . headers/GUI headers/data /usr/local/include/IScore /Library/Frameworks/ /usr/local/include/libxml2
}

QT += network xml svg

linux-g++ {
QMAKE_LFLAGS += -L/usr/local/lib/
}
linux-g++-64 {
QMAKE_LFLAGS += -L/usr/local/lib/
}
macx-g++ {
QMAKE_LFLAGS += -L/usr/local/lib/ -L/System/Library/Frameworks/ -L/Library/Frameworks/
}

# Dossier des sources temporaires de Qt
MOC_DIR = moc 
# Dossier des binaires
OBJETCS_DIR = bin

linux-g++ {
LIBS += -lIscore -lDeviceManager -lxml2 -lgecodeint -lgecodesearch -lgecodedriver -lgecodeflatzinc -lgecodekernel -lgecodeminimodel -lgecodescheduling -lgecodeset -lgecodesupport -lgecodegraph
}
linux-g++-64 {
LIBS += -lIscore -lDeviceManager -lxml2 -lgecodeint -lgecodesearch -lgecodedriver -lgecodeflatzinc -lgecodekernel -lgecodeminimodel -lgecodescheduling -lgecodeset -lgecodesupport -lgecodegraph
}
macx-g++ {
LIBS += -lIscore -lDeviceManager -framework gecode -lxml2
}
# Input
HEADERS += /usr/local/include/IScore/Engines.hpp \
/usr/local/include/IScore/CSPTypes.hpp \
headers/data/Abstract.hpp \
headers/data/AbstractBox.hpp \
headers/data/AbstractComment.hpp \
headers/data/AbstractCurve.hpp \
headers/data/AbstractRelation.hpp \
headers/data/AbstractSoundBox.hpp \
headers/data/AbstractControlBox.hpp \
headers/data/AbstractParentBox.hpp \
headers/data/AbstractTriggerPoint.hpp \
headers/data/EnumPalette.hpp \
headers/data/Maquette.hpp \
headers/data/Palette.hpp \
headers/GUI/AttributesEditor.hpp \
headers/GUI/BasicBox.hpp \
headers/GUI/BoxContextMenu.hpp \
headers/GUI/ChooseTemporalRelation.hpp \
headers/GUI/Comment.hpp \
headers/GUI/ControlBox.hpp \
headers/GUI/ControlBoxContextMenu.hpp \
headers/GUI/CurveWidget.hpp \
headers/GUI/CurvesWidget.hpp \
headers/GUI/Help.hpp \
headers/GUI/Interpolation.hpp \
headers/GUI/LogarithmicSlider.hpp \
headers/GUI/MainWindow.hpp \
headers/GUI/MaquetteScene.hpp \
headers/GUI/MaquetteView.hpp \
headers/GUI/NetworkConfig.hpp \
headers/GUI/NetworkMessagesEditor.hpp \
headers/GUI/NetworkTree.hpp \
headers/GUI/ParentBox.hpp \
headers/GUI/ParentBoxContextMenu.hpp \
headers/GUI/PlayingThread.hpp \
headers/GUI/PreviewArea.hpp \
headers/GUI/Relation.hpp \
headers/GUI/RelationEdit.hpp \
headers/GUI/SoundBox.hpp \
headers/GUI/SoundBoxContextMenu.hpp \
headers/GUI/TextEdit.hpp \
headers/GUI/TriggerPoint.hpp \
headers/GUI/TreeMap.hpp \
headers/GUI/TreeMapElement.hpp \
headers/GUI/ViewRelations.hpp \
headers/data/NetworkMessages.hpp \
headers/GUI/BoxWidget.hpp \
headers/GUI/BoxCurveEdit.hpp

SOURCES += main.cpp \
src/data/Abstract.cpp \
src/data/AbstractBox.cpp \
src/data/AbstractComment.cpp \
src/data/AbstractControlBox.cpp \
src/data/AbstractCurve.cpp \
src/data/AbstractParentBox.cpp \
src/data/AbstractRelation.cpp \
src/data/AbstractSoundBox.cpp \
src/data/AbstractTriggerPoint.cpp \
src/data/Maquette.cpp \
src/data/Palette.cpp \
src/GUI/AttributesEditor.cpp \
src/GUI/BasicBox.cpp \
src/GUI/BoxContextMenu.cpp \
src/GUI/ChooseTemporalRelation.cpp \
src/GUI/Comment.cpp \
src/GUI/ControlBox.cpp \
src/GUI/ControlBoxContextMenu.cpp \
src/GUI/CurveWidget.cpp \
src/GUI/CurvesWidget.cpp \
src/GUI/Help.cpp \
src/GUI/Interpolation.cpp \
src/GUI/LogarithmicSlider.cpp \
src/GUI/MainWindow.cpp \
src/GUI/MaquetteScene.cpp \
src/GUI/MaquetteView.cpp \
src/GUI/NetworkConfig.cpp \
src/GUI/NetworkMessagesEditor.cpp \
src/GUI/NetworkTree.cpp \
src/GUI/ParentBox.cpp \
src/GUI/ParentBoxContextMenu.cpp \
src/GUI/PlayingThread.cpp \
src/GUI/PreviewArea.cpp \
src/GUI/Relation.cpp \
src/GUI/RelationEdit.cpp \
src/GUI/SoundBox.cpp \
src/GUI/SoundBoxContextMenu.cpp \
src/GUI/TextEdit.cpp \
src/GUI/TriggerPoint.cpp \
src/GUI/TreeMap.cpp \
src/GUI/TreeMapElement.cpp \
src/GUI/ViewRelations.cpp \
src/data/NetworkMessages.cpp \
src/GUI/BoxWidget.cpp \
src/GUI/BoxCurveEdit.cpp

RESOURCES += i-score.qrc

DEFINES += __Types__

ICON = images/acousmoscribe.icns

TRANSLATIONS = acousmoscribe_en.ts \
               acousmoscribe_fr.ts