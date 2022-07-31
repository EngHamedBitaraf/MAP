﻿#pragma once
#include "DrawLine_global.h"
#include <QtPlugin>
#include <PluginInterface.h>

QT_BEGIN_NAMESPACE
class QToolBar;
class QAction;
class QMenu;
QT_END_NAMESPACE

class DRAWLINE_EXPORT DrawLine : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "io.tqjxlm.Atlas.PluginInterface" FILE "DrawLine.json")
    Q_INTERFACES(PluginInterface)

public:
    DrawLine();
    ~DrawLine() override;
    virtual void setupUi(QToolBar *toolBar, QMenu *menu) override;

    virtual void onLeftButton() override;
    virtual void onMouseMove() override;
    virtual void onRightButton() override;
    virtual void onDoubleClick() override;

protected:
    void newLine();

protected:
    osg::ref_ptr<osg::Geometry> _lineGeometry;
    osg::ref_ptr<osg::Vec3Array> _verticsLine;
    QAction* _action;
};
