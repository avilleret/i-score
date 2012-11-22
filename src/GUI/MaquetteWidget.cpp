
/*

Copyright: LaBRI / SCRIME

Authors: Luc Vercellin and Bruno Valeze (08/03/2010)

luc.vercellin@labri.fr

This software is a computer program whose purpose is to provide
notation/composition combining synthesized as well as recorded
sounds, providing answers to the problem of notation and, drawing,
from its very design, on benefits from state of the art research
in musicology and sound/music computing.

This software is governed by the CeCILL license under French law and
abiding by the rules of distribution of free software. You can use,
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty and the software's author, the holder of the
economic rights, and the successive licensors have only limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading, using, modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean that it is complicated to manipulate, and that also
therefore means that it is reserved for developers and experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and, more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include <iostream>
using std::string;

#include <QPainter>
#include <QGridLayout>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QString>
#include <QWidget>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>

#include "MaquetteWidget.hpp"
#include "MaquetteScene.hpp"
#include "MainWindow.hpp"

const float MaquetteWidget::HEADER_HEIGHT = 40;
const float MaquetteWidget::NAME_POINT_SIZE = 20;

MaquetteWidget::MaquetteWidget(QWidget *parent, MaquetteView *view, MaquetteScene *scene)
    : QWidget(parent){

    _view = view;
    _scene = scene;
    _color = QColor(Qt::white);
    _maquetteLayout = new QGridLayout();
    _nameLabel = new QLabel;
    _toolBar = new QToolBar;
    _header = new QWidget(NULL);
    _readingSpeedWidget = new QWidget;

    createReadingSpeedWidget();
    createActions();
    createToolBar();
    createNameLabel();
    createHeader();

    _maquetteLayout->addWidget(_header);
    _maquetteLayout->addWidget(_view);
    _maquetteLayout->setContentsMargins(0,0,0,0);
    _maquetteLayout->setVerticalSpacing(0);
    setLayout(_maquetteLayout);

    connect(_scene,SIGNAL(stopPlaying()),this,SLOT(stop()));
}

void
MaquetteWidget::init(){

}

MaquetteWidget::~MaquetteWidget(){

}

void
MaquetteWidget::createNameLabel(){
    QFont *font = new QFont();
    font->setPointSize(NAME_POINT_SIZE);
    _nameLabel->setFont(*font);
    _nameLabel->setText("Scenario");
}

void
MaquetteWidget::createReadingSpeedWidget(){
    QHBoxLayout *layout = new QHBoxLayout;

    _accelerationSlider = new LogarithmicSlider(Qt::Horizontal,this);
    _accelerationSlider->setStatusTip(tr("Acceleration"));
    _accelerationSlider->setFixedWidth(200);
    _accelerationSlider->setSliderPosition(50);

    _accelerationDisplay = new QDoubleSpinBox(this);
    _accelerationDisplay->setStatusTip(tr("Acceleration"));
    _accelerationDisplay->setRange(0.,5);
    _accelerationDisplay->setDecimals(1);
    _accelerationDisplay->setValue(_accelerationSlider->accelerationValue(_accelerationSlider->value()));
    _accelerationDisplay->setKeyboardTracking(false);

    layout->addWidget(_accelerationSlider);
    layout->addWidget(_accelerationDisplay);

    _readingSpeedWidget->setLayout(layout);

    connect(_accelerationDisplay, SIGNAL(valueChanged(double)), this, SLOT(accelerationValueEntered(double)));
    connect(_accelerationSlider,SIGNAL(valueChanged(int)),this,SLOT(accelerationValueModified(int)));
}

void
MaquetteWidget::createActions(){
    _playAction = new QAction(QIcon(":/images/play.svg"), tr("Play"), this);
    _playAction->setShortcut(QString("Space"));
    _playAction->setStatusTip(tr("Play composition"));
    _playAction->setCheckable(true);

    _stopAction = new QAction(QIcon(":/images/stop.svg"), tr("Stop"), this);
    _stopAction->setShortcut(QString("Enter"));
    _stopAction->setStatusTip(tr("Stop composition audio preview"));
    _stopAction->setCheckable(true);

    connect(_playAction,SIGNAL(triggered()), this, SLOT(play()));
    connect(_stopAction,SIGNAL(triggered()), this, SLOT(stop()));
}

void
MaquetteWidget::createToolBar(){
    _toolBar->addAction(_playAction);
}

void
MaquetteWidget::createHeader(){
    _header->setGeometry(0,0,width(),HEADER_HEIGHT);
    _header->setPalette(QPalette(_color));
    _header->setAutoFillBackground(true);

    _headerLayout= new QBoxLayout(QBoxLayout::LeftToRight);
    _headerLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    _headerLayout->addWidget(_toolBar);
    _headerLayout->addWidget(_nameLabel);
    _headerLayout->addWidget(_readingSpeedWidget);

    _headerLayout->insertSpacing(5,20);

    _headerLayout->insertStretch(2,_scene->width()/2);
    _headerLayout->setAlignment(_accelerationSlider,Qt::AlignRight);
    _headerLayout->setContentsMargins(0,0,0,0);
    _header->setLayout(_headerLayout);
}

void
MaquetteWidget::accelerationValueModified(int value){
    emit(accelerationValueChanged(value));

    double newValue = _accelerationSlider->accelerationValue(value);

    if (_accelerationDisplay->value() != newValue)
        _accelerationDisplay->setValue(newValue);
}

void
MaquetteWidget::play(){
    _scene->play();
    updateHeader();
}

void
MaquetteWidget::stop(){
    _scene->stop();
    updateHeader();
}

void
MaquetteWidget::updateHeader(){
    setAvailableAction(_scene->playing() ? _stopAction : _playAction);
}

void
MaquetteWidget::setName(QString name){
    _nameLabel->setText(name);
}

void
MaquetteWidget::setAvailableMenu(QWidget *widget){
    //TODO
}

void
MaquetteWidget::setAvailableAction(QAction *action){
    if(!_toolBar->actions().empty()){
        _toolBar->removeAction(_toolBar->actions().first());
        _toolBar->addAction(action);
    }
}

void
MaquetteWidget::accelerationValueEntered(double value){
    int newValue = _accelerationSlider->valueForAcceleration(value);
    Maquette::getInstance()->setAccelerationFactor(value);
    _accelerationSlider->setValue(newValue);
}
