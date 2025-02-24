﻿#include "Locator.h"

#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QGroupBox>

#include <osgViewer/View>

#include <osgEarth/SpatialReference>

#include <SettingsManager.h>
#include <AtlasMainWindow.h>
#include <NXDockWidget.h>

Locator::Locator()
{
	_pluginName     = tr("Locator");
	_pluginCategory = "Effect";
}

Locator::~Locator(void)
{
}

void  Locator::setupUi(QToolBar */*toolBar*/, QMenu */*menu*/)
{
	_action = new QAction(_mainWindow);
	_action->setObjectName(QStringLiteral("locateAction"));
	_action->setCheckable(true);

	connect(_action, SIGNAL(toggled(bool)), this, SLOT(toggle(bool)));

	registerMutexAction(_action);
	setDefaultAction(_action);

	_action->setChecked(true);

	setupQueryDock();
}

bool  Locator::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	if (!_activated)
	{
		return false;
	}

	osgViewer::View *view = dynamic_cast<osgViewer::View *>(&aa);

	switch (ea.getEventType())
	{
	case (osgGA::GUIEventAdapter::DOUBLECLICK):

		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			osgEarth::Viewpoint  vp;
			vp.focalPoint() = _currentGeoPos;
			emit  setViewPoint(vp);
		}

		return false;
	default:

		return false;
	}
}

void  Locator::flyToQueriedCoord()
{
	double              lon = _coordQueryX->text().toDouble();
	double              lat = _coordQueryY->text().toDouble();
    double range = _range->text().toDouble();
    double pitch = _pitch->text().toDouble();
	osgEarth::GeoPoint  point(osgEarth::SpatialReference::get("wgs84"), lon, lat, 0);

	if (point.isValid())
	{
		osgEarth::Viewpoint  vp;
		vp.focalPoint() = point;
        vp.setPitch(pitch);
        vp.setRange(range);
		emit  setViewPoint(vp);
	}
}

void  Locator::setupQueryDock()
{
	auto  queryDockWidget = new NXDockWidget(tr("Spatial Query"), _mainWindow);

	queryDockWidget->setObjectName(QStringLiteral("queryDockWidget"));

	QSizePolicy  sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(queryDockWidget->sizePolicy().hasHeightForWidth());
	queryDockWidget->setSizePolicy(sizePolicy1);
    queryDockWidget->setMaximumHeight(250);

	auto  dockWidgetContents = new QWidget();
	dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
	dockWidgetContents->setSizePolicy(sizePolicy1);

	auto  verticalLayout = new QVBoxLayout(dockWidgetContents);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	auto  coordQueryGroupBox = new QGroupBox(dockWidgetContents);
	coordQueryGroupBox->setObjectName(QStringLiteral("coordQueryGroupBox"));
	coordQueryGroupBox->setTitle(tr("Coordinate"));
	sizePolicy1.setHeightForWidth(coordQueryGroupBox->sizePolicy().hasHeightForWidth());
	coordQueryGroupBox->setSizePolicy(sizePolicy1);
	coordQueryGroupBox->setMinimumSize(QSize(0, 0));

	auto  gridLayout_6 = new QGridLayout(coordQueryGroupBox);
	gridLayout_6->setSpacing(6);
	gridLayout_6->setContentsMargins(11, 11, 11, 11);
	gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
	auto  coordLabel_x = new QLabel(coordQueryGroupBox);
	coordLabel_x->setObjectName(QStringLiteral("coordLabel_x"));
	sizePolicy1.setHeightForWidth(coordLabel_x->sizePolicy().hasHeightForWidth());
	coordLabel_x->setSizePolicy(sizePolicy1);
	coordLabel_x->setText(tr("Lon"));

	gridLayout_6->addWidget(coordLabel_x, 0, 0, 1, 1);

	_coordQueryX = new QLineEdit(coordQueryGroupBox);
	_coordQueryX->setObjectName(QStringLiteral("_coordQueryX"));
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(_coordQueryX->sizePolicy().hasHeightForWidth());
	_coordQueryX->setSizePolicy(sizePolicy1);
	_coordQueryX->setMinimumSize(QSize(0, 0));
//	_coordQueryX->setPlaceholderText(tr("Input longitude here"));
    _coordQueryX->setText(tr("51.43"));

	gridLayout_6->addWidget(_coordQueryX, 0, 1, 1, 1);

	auto  coordLabel_y = new QLabel(coordQueryGroupBox);
	coordLabel_y->setObjectName(QStringLiteral("coordLabel_y"));
	sizePolicy1.setHeightForWidth(coordLabel_y->sizePolicy().hasHeightForWidth());
	coordLabel_y->setSizePolicy(sizePolicy1);
	coordLabel_y->setMaximumSize(QSize(16777215, 16777215));
	coordLabel_y->setText(tr("Lat"));

	gridLayout_6->addWidget(coordLabel_y, 1, 0, 1, 1);

	_coordQueryY = new QLineEdit(coordQueryGroupBox);
	_coordQueryY->setObjectName(QStringLiteral("_coordQueryY"));
	sizePolicy1.setHeightForWidth(_coordQueryY->sizePolicy().hasHeightForWidth());
	_coordQueryY->setSizePolicy(sizePolicy1);
	_coordQueryY->setMinimumSize(QSize(0, 0));
    //_coordQueryY->setPlaceholderText(tr("Input latitude here"));
    _coordQueryY->setText(tr("35.81"));

	gridLayout_6->addWidget(_coordQueryY, 1, 1, 1, 1);
    //-------------------------------------------------------------
    auto  pitchLabel = new QLabel(coordQueryGroupBox);
    pitchLabel->setObjectName(QStringLiteral("pitchLabel"));
    sizePolicy1.setHeightForWidth(pitchLabel->sizePolicy().hasHeightForWidth());
    pitchLabel->setSizePolicy(sizePolicy1);
    pitchLabel->setMaximumSize(QSize(16777215, 16777215));
    pitchLabel->setText(tr("Pitch(15-90"));

    gridLayout_6->addWidget(pitchLabel, 2, 0, 1, 1);

    _pitch = new QLineEdit(coordQueryGroupBox);
    _pitch->setObjectName(QStringLiteral("_pitch"));
    sizePolicy1.setHeightForWidth(_pitch->sizePolicy().hasHeightForWidth());
    _pitch->setSizePolicy(sizePolicy1);
    _pitch->setMinimumSize(QSize(0, 0));
    _pitch->setText(tr("25"));
    _pitch->setPlaceholderText(tr(""));

    gridLayout_6->addWidget(_pitch, 2, 1, 1, 1);

    auto  rangeLabel = new QLabel(coordQueryGroupBox);
    rangeLabel->setObjectName(QStringLiteral("rangeLabel"));
    sizePolicy1.setHeightForWidth(rangeLabel->sizePolicy().hasHeightForWidth());
    rangeLabel->setSizePolicy(sizePolicy1);
    rangeLabel->setMaximumSize(QSize(16777215, 16777215));
    rangeLabel->setText(tr("Range"));

    gridLayout_6->addWidget(rangeLabel, 3, 0, 1, 1);

    _range = new QLineEdit(coordQueryGroupBox);
    _range->setObjectName(QStringLiteral("_range"));
    sizePolicy1.setHeightForWidth(_range->sizePolicy().hasHeightForWidth());
    _range->setSizePolicy(sizePolicy1);
    _range->setMinimumSize(QSize(0, 0));
    _range->setText(tr("5000"));

    gridLayout_6->addWidget(_range, 3, 1, 1, 1);
    //-------------------------------------------------------------

	auto  coordQueryPushButton = new QPushButton(coordQueryGroupBox);
	coordQueryPushButton->setObjectName(QStringLiteral("coordQueryPushButton"));
	sizePolicy1.setHeightForWidth(coordQueryPushButton->sizePolicy().hasHeightForWidth());
	coordQueryPushButton->setSizePolicy(sizePolicy1);
	coordQueryPushButton->setText(tr("Go to Coord"));

    gridLayout_6->addWidget(coordQueryPushButton, 4, 0, 1, 2);

	auto  verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

	verticalLayout->addWidget(coordQueryGroupBox);

	verticalLayout->addItem(verticalSpacer);

	queryDockWidget->setWidget(dockWidgetContents);

	connect(coordQueryPushButton, &QPushButton::clicked, this, &Locator::flyToQueriedCoord);

	static_cast<AtlasMainWindow *>(_mainWindow)->addDockWidget(Qt::RightDockWidgetArea, queryDockWidget);
}
